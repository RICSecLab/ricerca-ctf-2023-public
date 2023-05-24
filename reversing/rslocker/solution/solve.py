from ptrlib import *

k1 = 0xa205b064
k2 = 0xbb40e64d
desk = b"m0S0g0Y0"
cipher = bytearray.fromhex("36D78F01489BD33C25A32D0BBF7684BD86E95228F4AF1871E7DD3864CDEC53A8568C5F1865135EE039D98012CC19FDD97CB68BBCB5AB743AA31B749CBC3BBBB8")

key = flat([
    intel_crc32(k1, desk[4:]),
    intel_crc32(k1, desk[:4]),
    intel_crc32(k2, desk[4:]),
    intel_crc32(k2, desk[:4])
], map=p32)

flag = b""
for block in chunks(cipher, 16):
    flag += intel_aesenc_inv(block, key)
print(flag)
