import sys
import math

def findb(k, a):
    delta = k * k * (a + 1) * (a + 1) - 4 * (a * a - k * a)
    return int((k * (a + 1) + math.sqrt(delta)) / 2)

def findc(k, a, b):
    return k * (a + b) - 1

def check(a, b, c, k):
    return a * a + b * b + c * c == k * (a * b + b * c + c * a) + 1

def _lim(a=100):
    if a == 1:
        return 10
    return 10 * _lim(a-1)

if __name__ == "__main__":
    k, n = map(int, sys.stdin.readline().strip().split(' '))
    used = set()
    lim = _lim()
    a = k
    while n > 0:
        b = findb(k, a)
        c = findc(k, a, b)
        if check(a, b, c, k) and a not in used and b not in used and c not in used:
            print(a, b, c)
            n -= 1
            used.add(a)
            used.add(b)
            used.add(c)
        a += k





