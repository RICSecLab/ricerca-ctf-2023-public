from ptrlib import *

sock = Process("../distfiles/crackme")

sock.sendline("N1pp0n-Ich!_s3cuR3_p45$w0rD")
sock.recvline()
print(sock.recvline())

sock.close()
