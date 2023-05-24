def F(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return F(n - 1) + F(n - 2)

flag = "RicSec{1gn1t10n_bytec0de_1s_s0_r1ch}"

encoded = [ord(c) ^ (F(i) & 0xff) for i, c in enumerate(flag[7:-1])]
print(encoded) 
