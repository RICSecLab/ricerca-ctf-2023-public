from z3 import *

a = [16, 3, 0, 3, 6, 14, 12, 9, 9]

s = Solver()

cells = [BitVec(f"cell{i}", 8) for i in range(9)]
def cell_at(x, y):
    return cells[x * 3 + y]

s.add(cell_at(0, 0) + cell_at(1, 0) == 19)
s.add(cell_at(1, 0) - cell_at(2, 0) == 256-9)
s.add(cell_at(2, 0) / cell_at(0, 1) == 4)
s.add(cell_at(0, 1) + cell_at(1, 1) == 9)
s.add(cell_at(1, 1) * cell_at(2, 1) == 54)
s.add(cell_at(2, 1) * cell_at(0, 2) == 0)
s.add(cell_at(0, 2) - cell_at(1, 2) == 256-14)
s.add(cell_at(1, 2) - cell_at(2, 2) == 5)
s.add(cell_at(2, 2) / cell_at(0, 0) == 0)
s.add(cell_at(0, 0) - cell_at(2, 0) == 4)
s.add(cell_at(1, 0) * cell_at(0, 1) == 9)
s.add(cell_at(2, 0) + cell_at(1, 1) == 18)
s.add(cell_at(0, 1) + cell_at(2, 1) == 12)
s.add(cell_at(1, 1) - cell_at(0, 2) == 6)
s.add(cell_at(2, 1) / cell_at(1, 2) == 0)
s.add(cell_at(0, 2) * cell_at(2, 2) == 0)
s.add(cell_at(1, 2) + cell_at(0, 0) == 30)
s.add(cell_at(2, 2) - cell_at(1, 0) == 6)

if s.check() == unsat:
    exit('[1] x')

m = s.model()
if any([m[cells[i]].as_long() != a[i] for i in range(9)]):
    exit('[2] x')

for i in range(9):
    s.add(cells[i] != a[i])
if s.check() != unsat:
    exit('[3] x')

print("ok")
