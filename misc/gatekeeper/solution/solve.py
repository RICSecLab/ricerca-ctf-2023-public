import base64
from pwn import *
import os

HOST = os.getenv("HOST", "localhost")
PORT = int(os.getenv("PORT", 10005))

p = remote(HOST, PORT)

password = b'open sesame!'
p.sendline(base64.b64encode(password[0:1]) + base64.b64encode(password[1:]))
p.recvuntil(b'password: ')
print(p.recvuntil(b'\r', drop=True).decode())
