from ptrlib import *
import os
from tqdm import tqdm

HOST = os.getenv("HOST", "localhost")
PORT = int(os.getenv("PORT", 5963))

# sock = Process(["sage", "../distfiles/server.sage"])
sock = Socket(HOST, PORT)

for round in tqdm(range(77)):
    Gx = int(sock.recvlineafter("x: "))
    a = -15*Gx**2
    b = -22*Gx**3
    sock.sendlineafter("a: ", a)
    sock.sendlineafter("b: ", b)

    commitment = sock.recvregex("\((\d+), (\d+)\)")
    Gy, Qy = int(commitment[0]), int(commitment[1])
    print(f'{round=} {Gy=}, {Qy=}')
    k1p = Gy**2 - Gx**3 - a*Gx - b

    if Qy == 0: # 3*G
        kymn_dice = 4

    elif Qy == 1: # 6*G
        kymn_dice = 1

    elif Qy == Gy: # 1*G
        kymn_dice = 2

    else:
        k2p = Qy * (-288*Gy) + 3456*Gx**3
        p = gcd(k1p, k2p)
        if p > 1<<200: # 2*G
            kymn_dice = 3

        else:
            k2p = Qy * 3 - Gy
            p = gcd(k1p, k2p)
            if p > 1<<200: # 4*G
                kymn_dice = 5

            else:
                kymn_dice = 6

    sock.sendlineafter("Your dice: ", 7 - kymn_dice)

    l = sock.recvline()
    if b'You lucky bastard' not in l:
        logger.error("Bad luck!")
        sock.close()
        break

print(sock.recvuntil(b'}'))
