from Crypto.Util.number import long_to_bytes
from math import isqrt

exec(open("../distfiles/output.txt").read())

P_BITS = 1024
A_BITS = P_BITS // 2

ab_upper = int(bin(n)[2:][:-A_BITS*3], 2)
ab_lower = int(bin(n)[2:][-A_BITS:], 2)

a, b = None, None
for i in [0, 1, 2]:
  ab = ((ab_upper - i) << A_BITS) + ab_lower
  # a^2+b^2
  a2pb2 = (n - (ab << P_BITS) - ab) >> A_BITS
  # (a+b)^2
  apb2 = a2pb2 + 2 * ab
  if apb2 < 0 or isqrt(apb2) ** 2 != apb2: continue

  apb = isqrt(a2pb2 + 2 * ab)
  d = apb**2 - 4*ab
  if d < 0 or isqrt(d) ** 2 != d: continue

  a = (apb + isqrt(d)) // 2
  b = (apb - isqrt(d)) // 2

  assert a * b == ab
  break

assert a is not None and b is not None

p = (a << A_BITS) + b
q = (b << A_BITS) + a

assert p * q == n

print(long_to_bytes(pow(c, pow(e, -1, (p - 1) * (q - 1)), n)).decode())
