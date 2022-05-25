#!/usr/bin/env python3.7

from task import Cipher


def isqrt(n: int) -> int:
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    return x


def recover_size(canary: int) -> int:
    # size * (size ** 2 - 1) // 2 == canary (mod size * size)
    # size ** 3 - size == canary * 2 (mod size * size)
    # -size == canary * 2 (mod size * size)
    # k * size * size - size - canary * 2 == 0
    # size == (1 + sqrt(1 + 8 * k * canary)) // (2 * k)
    for k in range(-16, 16):
        if k == 0:
            continue
        D = 1 + 8 * k * canary
        if D < 0:
            continue
        size = (1 + isqrt(D)) // (2 * k)
        if size < 0:
            continue
        if (size * (size ** 2 - 1) - canary * 2) % (size * size) == 0:
            return size


def recover_key(size: int) -> int:
    return size * (size ** 2 - 1) // 2


def main():
    ciphertext = bytes.fromhex(input())
    canary = int(input())
    size = recover_size(canary)
    key = recover_key(size)
    print(f'key = {key}')
    cipher = Cipher(key, canary)
    plaintext = cipher.encrypt(ciphertext)
    print(f'plaintext = {plaintext}')
    return


if __name__ == '__main__':
    main()
