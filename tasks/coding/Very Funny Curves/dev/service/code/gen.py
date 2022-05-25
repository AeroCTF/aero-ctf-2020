from random import choice, randint


def Factor(n):
    if n == 0:
        return []

    Ans = []
    d = 2
    while d * d <= n:
        if n % d == 0:
            Ans.append(d)
            n //= d
        else:
            d += 1
    if n > 1:
        Ans.append(n)

    if len(Ans) == 0:
        Ans.append(n)
    Ans.append(1)
    return Ans


def delitel(fact: list, n: int) -> int:
    f = fact
    leng = len(f)
    r = 1

    if leng == 0:
        return randint(1, 99)
    c = 0.8*n
    for _ in range(randint(1, len(f))):
        i = randint(0, leng-1)
        if r*f[i] > c:
            return int(r)
        r *= f[i]
        f.remove(f[i])
        leng -= 1

    return int(r)


def _add(a: str, r: int, s: bool):
    b = randint(1, 99)
    if choice([True, False]):
        return f"{a}+{b}", r+b, True
    else:
        return f"{b}+{a}", r+b, True


def _sub(a: str, r: int, s: bool):
    b = randint(1, 99)
    return f"{a}-{b}", r-b, True


def _mul(a: str, r: int, s: bool):
    b = randint(2, 99)
    if s:
        if choice([True, False]):
            return f"({a})*{b}", r*b, False
        else:
            return f"{b}*({a})", r*b, False
    else:
        if choice([True, False]):
            return f"{a}*{b}", r*b, False
        else:
            return f"{b}*{a}", r*b, False


def _div(a: str, r: int, s: bool):
    b = delitel(Factor(abs(r)), abs(r))
    if b == 1:
        return arifmetic[choice("+-*")](a, r, s)
    if s:
        return f"({a})/{b}", r/b, False
    else:
        return f"{a}/{b}", r/b, False


def _pow(a: str, r: int, s: bool):
    b = randint(2, 3)
    return f"({a})^{b}", r**b, False


arifmetic = {
    '+': _add,
    '-': _sub,
    '*': _mul,
    '/': _div,
    '^': _pow
}


def genPrimer(colZN=4):
    alf = "+-/*"

    r = randint(1, 99)
    f = str(r)
    s = False
    for _ in range(colZN):
        (f, r, s) = arifmetic[choice(alf)](f, r, s)  # формула, сумма, скобки

    if int(eval(f.replace("^", "**"))) != int(r):
        f, r = genPrimer(colZN)
    return f, int(r)


if __name__ == '__main__':

    maxx = 0
    i = 0
    for _ in range(1000000):
        (f, res) = genPrimer(6)
        maxx = max(len(f), maxx)
        f = f.replace("^", "**")
        if int(eval(f)) != res:
            print(f"{f}={res}!={int(eval(f))}")
        i += 1
    print(maxx)
    print(i)
    #f = f.replace("^", "**")
    # print(res)
    # print(eval(f))
