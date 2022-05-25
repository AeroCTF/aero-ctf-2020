#!/usr/bin/env python3

import sys
import signal
from random import uniform, choice, randint

import bz2
import base64

from classes import Gen_formul

flag = "Aero{e5767426d10e0f4bc4e131e0bb6d509ccad5a8decdf81a70b4f5ddb202441a09}"


def randStr(alph: str, stringLength: int = 8) -> str:
    return ''.join(choice(alph) for _ in range(stringLength))


def compres(txt: str) -> str:
    return base64.b85encode(bz2.compress(txt.encode())).decode("UTF-8")


def main():
    A = Gen_formul()

    A.set_rpos(0.4, 1)
    alph = A.alph

    print("Prove that you are a robot, build all the curves and send me an answer!")

    signal.alarm(3)

    r = input("Ready? <Y/n>")

    if r != "Y":
        print("Bye man!")
        sys.exit(-1)

    for i in range(0, 100):

        A.set_dpos(randint(-1000, 1000), randint(-1000, 1000))

        text: str = randStr(alph, randint(6, 10))

        ret = "t=>[0;1]\n"
        for x in A.txt_to_form(text):
            ret += (f"f(t) = ({x[0]}; {x[1]})\n")

        print(compres(ret))

        signal.alarm(3)

        buf = input("Result: ")

        if buf != text:
            print("Incorrect!")
            sys.exit(-1)
        else:
            continue

    print("Flag: %s" % flag)


if __name__ == '__main__':
    try:
        main()
    except:
        sys.exit(-1)
