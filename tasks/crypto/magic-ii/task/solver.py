#!/usr/bin/env python3.7

import z3

import re
import time
import random

from ast import literal_eval


def rule30(init):
    init = [init[-1]] + init + [init[0]]
    state = []
    for left, center, right in zip(init, init[1:], init[2:]):
        state.append(left ^ (center | right))
    return state


def rule30_z3(init):
    init = [init[-1]] + init + [init[0]]
    state = []
    for left, center, right in zip(init, init[1:], init[2:]):
        op = z3.Or(center, right)
        # part = z3.Xor(left, op)
        # part = z3.Or(z3.And(z3.Not(left), op), z3.And(left, z3.Not(op)))
        part = z3.And(z3.Or(z3.Not(left), z3.Not(op)), z3.Or(left, op))
        state.append(part)
    return state


def get_seed(formula, x):
    formula = z3.simplify(formula)
    goal = z3.Goal()
    goal.add(formula)
    tactic = z3.Tactic('snf')
    formula = z3.And(list(tactic(goal)[0]))
    solver = z3.Solver()
    print(solver.check(formula))
    model = solver.model()
    return [int(bool(model[xi])) for xi in x]


def recover_seed_from_randint(bits, number, length):
    x = [z3.Bool(f'x{i}') for i in range(length)]
    state_z3 = x
    randint_z3 = []
    for i in range(len(bits)):
        print(i)
        state_z3 = rule30_z3(state_z3)
        randint_z3.append(state_z3[number])
    formula = z3.And([var_z3 if bits[i] else z3.Not(var_z3) for i, var_z3 in enumerate(randint_z3)])
    return get_seed(formula, x)


def recover_seed_from_state(bits, steps, length):
    x = [z3.Bool(f'x{i}') for i in range(length)]
    state_z3 = x
    for i in range(steps):
        print(i)
        state_z3 = rule30_z3(state_z3)
    formula = z3.And([var_z3 if bits[i] else z3.Not(var_z3) for i, var_z3 in enumerate(state_z3)])
    return get_seed(formula, x)
    

def randstate(length):
    return [random.randint(0, 1) for _ in range(length)]


def generate_key(steps, number, length, init):
    state = init
    key = []
    for i in range(steps):
        state = rule30(state)
        key.append(state[number])
    return state, key


def test():
    steps = 128
    number, length = 0, steps // 2

    init = init = randstate(length)
    state, key = generate_key(steps, number, length, init)

    seed1 = recover_seed_from_randint(key, number, length)
    seed2 = recover_seed_from_state(state, steps, length)

    print(seed1)
    print(seed2)
    print(init)


def main():
    steps = 512
    length = 64
    number = 0
    numbers = literal_eval(input())
    bits = ''.join(bin(number)[2:].zfill(length)[::-1] for number in numbers)
    bits = list(map(int, bits))
    seed1 = recover_seed_from_randint(bits[:length*2], number, length)
    seed2 = recover_seed_from_state(seed1, steps, length)
    _, key = generate_key(steps, number, length, seed2)
    with open('output.txt', 'r') as file:
        secret = int(re.search(r'There are (\d+) famous potions', file.read()).group(1))
    flag = secret ^ int(''.join(map(str, reversed(key))), 2)
    print(flag.to_bytes(64, 'big'))
    return


if __name__ == '__main__':
    # test()
    main()
