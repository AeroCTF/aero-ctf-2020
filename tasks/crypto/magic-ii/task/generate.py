#!/usr/bin/env python3.7

from task import Random, create_potion, getrandbits


def main():
    from secret import FLAG
    security_level = 64
    ingredients_count = 12
    random = Random.create(security_level)
    potions_count = int.from_bytes(FLAG, 'big') ^ random.randint(512)
    print(f'There are {potions_count} famous potions in the world. We are trying to create something new!')
    ingredients = [random.randint(security_level) for _ in range(ingredients_count)]
    for i in range(100):
        amounts = [getrandbits(41) for _ in range(len(ingredients))]
        effect = create_potion(ingredients, amounts)
        print(f'A potion with {amounts} amounts of ingregients has {effect} value of effect.')
        print(f'Would you like to create another potion? (y/n): {"y" if i < 99 else "n"}')
    return


if __name__ == '__main__':
    main()
