#!/usr/bin/env python3.7

from task import Cipher
from random import randint


def main():
    with open('flag.txt', 'rb') as file:
        flag = file.read()
    size = 8 ** len(flag)
    size += randint(size, 2 * size)
    key = size * (size ** 2 - 1) // 2
    canary = key % (size ** 2)
    cipher = Cipher(key, canary)
    print(cipher.encrypt(flag).hex())
    print(cipher.canary)
    return


if __name__ == '__main__':
    main()
