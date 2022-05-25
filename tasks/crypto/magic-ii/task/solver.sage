#!/usr/bin/env sage

import re

from ast import literal_eval
from random import randint


def load_data():
    with open('output.txt', 'r') as file:
        data = file.read()
    lists = re.findall(r'(\[.*?\])', data)
    values = re.findall(r'has (\d+) value', data)
    return list(map(literal_eval, lists)), values


def Babai_closest_vector(M, G, target):
    small = target
    for i in reversed(range(M.nrows())):
        c = ((small * G[i]) / (G[i] * G[i])).round()
        small -=  M[i] * c
    return target - small


def find_secret(lists, values):
    limit = 50
    lists, values = lists[:limit], values[:limit]

    q = 1046961993706256953070441
    p = 2 ** 64
    n = len(lists[0])
    m = len(lists)

    A = matrix(ZZ, lists)
    B = vector(ZZ, values)
    M = (matrix.identity(m) * q).augment(matrix(m, n)).stack(A.T.augment(matrix.identity(n)))
    target = vector(ZZ, list(B) + [0] * n)

    for i in range(20):
        # randomize lattice
        for i in range(n):
            ia = randint(0, m)
            ib = randint(0, m)
            if ib == ia:
                ib = (ib + 1) % m
            val = randint(-100000, 100000)
            M[ia] += val * M[ib]
    
        L = M.LLL()
        G = L.gram_schmidt()[0]
    
        result = Babai_closest_vector(L, G, target)
        
        secret = result[-n:]
        error = (target - result)[:n]

        if all((A[i] * secret + error[i]) % q == B[i] for i in range(n)):
            return secret


if __name__ == '__main__':
    print(find_secret(*load_data()))
