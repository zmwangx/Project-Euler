#!/usr/bin/env python3

import math
import random


guesses = [
    ("5616185650518293", 2),
    ("3847439647293047", 1),
    ("5855462940810587", 3),
    ("9742855507068353", 3),
    ("4296849643607543", 3),
    ("3174248439465858", 1),
    ("4513559094146117", 2),
    ("7890971548908067", 3),
    ("8157356344118483", 1),
    ("2615250744386899", 2),
    ("8690095851526254", 3),
    ("6375711915077050", 1),
    ("6913859173121360", 1),
    ("6442889055042768", 2),
    ("2321386104303845", 0),
    ("2326509471271448", 2),
    ("5251583379644322", 2),
    ("1748270476758276", 3),
    ("4895722652190306", 1),
    ("3041631117224635", 3),
    ("1841236454324589", 3),
    ("2659862637316867", 2),
]


def simulated_annealing():
    temp = 1
    state = guesses[2][0]
    length = len(state)
    hit_counts = [
        sum(1 if c1 == c2 else 0 for c1, c2 in zip(state, guess))
        for guess, _ in guesses
    ]
    correct_counts = [count for _, count in guesses]
    energy = sum(abs(c1 - c2) for c1, c2 in zip(hit_counts, correct_counts))
    time = 1
    while energy > 0:
        if time % 1000 == 0:
            print(f"{temp:.3f} {energy} {state}")
            temp -= 0.001
            if temp <= 0.2:
                break
        time += 1
        change_position = random.randrange(length)
        d = state[change_position]
        while (change_to := str(random.randrange(10))) == d:
            pass
        new_state = state[:change_position] + change_to + state[change_position + 1 :]
        new_hit_counts = [
            sum(1 if c1 == c2 else 0 for c1, c2 in zip(new_state, guess))
            for guess, _ in guesses
        ]
        new_energy = sum(abs(c1 - c2) for c1, c2 in zip(new_hit_counts, correct_counts))
        if new_energy == 0:
            print(new_state)
            return
        if new_energy < energy:
            state = new_state
            energy = new_energy
        else:
            prob = math.exp((energy - new_energy) / temp)
            if random.random() <= prob:
                state = new_state
                energy = new_energy
    print(state, energy)


def main():
    simulated_annealing()


if __name__ == "__main__":
    main()
