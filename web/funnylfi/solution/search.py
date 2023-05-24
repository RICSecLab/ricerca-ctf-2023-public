print("FunnyLFI Query Searcher")

for i in range(0x3f):
    for j in range(0xffff):
        try:
            url = f"ﬁle:///var/www/flag⁇.{'a'*i}{chr(j)}".encode("idna").decode()
            if (" " in url) and ("r1" in url.split(" ")[1]):
                print(url)
                print(f"ﬁle:///var/www/flag⁇.{'a'*i}{chr(j)}")
        except Exception as e:
            #print(e)
            continue