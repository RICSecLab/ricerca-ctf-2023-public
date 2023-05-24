def F(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return F(n - 1) + F(n - 2);

encoded = []
offset = 0x2ae
with open("../distfiles/challenge.jsc", "rb") as f:
  for i in range(28):
    f.seek(offset + i*8)
    encoded.append(f.read(1)[0])

flag = "".join([chr(c ^ (F(i) & 0xff)) for i, c in enumerate(encoded)])
print(f"RicSec{{{flag}}}")
