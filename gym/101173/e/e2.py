import sys
import math

def _lim(a=100):
    if a == 1:
        return 10
    return 10 * _lim(a-1)


def sol(a, b, c, n):
    sys.stdout.write("{:d} {:d} {:d}\n".format(a, b, c))
    used.add(a)
    used.add(b)
    used.add(c)
    n -= 1
    if n == 0:
        sys.exit(0)
    return n

def find(k, a, b, c, used, lim, queue, n):
    if a <= 0 and b <= 0 and c <= 0:
        return n
    if a < lim and b < lim and c < lim and a > 0 and b > 0 and c > 0 and a not in used and b not in used and c not in used:
        n = sol(a, b, c, n)
    queue.append((a, b, k * (a + b) - c))
    queue.append((a, k * (a + c) - b, c))
    queue.append((k * (b + c) - a, b, c))
    return n

if __name__ == "__main__":
    used = set()
    queue = []
    lim = _lim()
    k, n = map(int, sys.stdin.readline().strip().split(' '))
    queue.append((0, 1, k))
    while True:
        a, b, c = queue.pop(0)
        n = find(k, a, b, c, used, lim, queue, n)




