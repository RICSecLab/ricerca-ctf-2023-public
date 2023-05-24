def pdivmod(u, v):
    """
    polynomial version of divmod
    """
    q = u // v
    r = u - q*v
    return (q, r)

def hgcd(u, v, min_degree=10):
    """
    Calculate Half-GCD of (u, v)
    f and g are univariate polynomial
    http://web.cs.iastate.edu/~cs577/handouts/polydivide.pdf
    """
    x = u.parent().gen()

    if u.degree() < v.degree():
        u, v = v, u

    if 2*v.degree() < u.degree() or u.degree() < min_degree:
        q = u // v
        return matrix([[1, -q], [0, 1]])

    m = u.degree() // 2
    b0, c0 = pdivmod(u, x^m)
    b1, c1 = pdivmod(v, x^m)

    R = hgcd(b0, b1)
    DE = R * matrix([[u], [v]])
    d, e = DE[0,0], DE[1,0]
    q, f = pdivmod(d, e)

    g0 = e // x^(m//2)
    g1 = f // x^(m//2)

    S = hgcd(g0, g1)
    return S * matrix([[0, 1], [1, -q]]) * R

def pgcd(u, v):
    """
    fast implementation of polynomial GCD
    using hgcd
    """
    if u.degree() < v.degree():
        u, v = v, u

    if v == 0:
        return u

    if u % v == 0:
        return v

    if u.degree() < 10:
        while v != 0:
            u, v = v, u % v
        return u

    R = hgcd(u, v)
    B = R * matrix([[u], [v]])
    b0, b1 = B[0,0], B[1,0]
    r = b0 % b1
    if r == 0:
        return b1

    return pgcd(b1, r)

with open("../distfiles/output.txt") as f:
    exec(f.readline())
    exec(f.readline())
    exec(f.readline())
    C1 = bytes.fromhex(f.readline())
    C2 = bytes.fromhex(f.readline())
    C3 = bytes.fromhex(f.readline())

# s1 = a*s + b mod n
# s2 = a^2*s + a*b + b mod n
# s3 = a^3*s + a^2*b + a*b + b mod n

# f1 = s1^e - c1 mod n
# f2 = s3^e - c2 mod n

M1 = b"The quick brown fox jumps over the lazy dog"
M3 = b"https://translate.google.com/?sl=it&tl=en&text=ricerca"
c1 = int.from_bytes(C1, 'big') ^^ int.from_bytes(M1, 'big')
c3 = int.from_bytes(C3, 'big') ^^ int.from_bytes(M3, 'big')

print("[+] Creating polynomial...")
F = Zmod(n)
PR.<x> = PolynomialRing(F)
e = 65537

f = (a*x + b)^e - c1
g = (a^3*x + a^2*b + a*b + b)^e - c3

print("[+] Calculating half-GCC...")
h = pgcd(f, g)
s0 = F(-h.monic()[0])

s1 = (a * s0 + b) % n
s2 = (a * s1 + b) % n
key = pow(s2, e, n)
m = int(key) ^^ int.from_bytes(C2, 'big')

print(int.to_bytes(m, 128, 'big').lstrip(b'\x00'))
