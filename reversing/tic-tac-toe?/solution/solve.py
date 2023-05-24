from pwn import *

p = process("../distfiles/challenge")

val = [16, 3, 12, 3, 6, 9, 0, 14, 9]
cells = ['a1', 'b1', 'c1', 'a2', 'b2', 'c2', 'a3', 'b3', 'c3']

turn = 0;
for i in range(9):
  v = 0
  while True:
    if v == val[i]:
      break
    p.sendlineafter(b": ", cells[i].encode())
    v = v + [1, 2][turn % 2]
    turn = turn + 1

p.interactive()
