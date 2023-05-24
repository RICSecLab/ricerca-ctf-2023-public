def bitrev(x):
    x = (x & 0xf0) >> 4 | (x & 0x0f) << 4
    x = (x & 0xcc) >> 2 | (x & 0x33) << 2
    x = (x & 0xaa) >> 1 | (x & 0x55) << 1
    return x

password = b"N1pp0n-Ich!_s3cuR3_p45$w0rD"
flag     = b"RicSec{U_R_h1y0k0_cr4ck3r!}"

enc = []
for a, b in zip(password, flag):
    enc.append(b ^ bitrev(a))

print(enc)
