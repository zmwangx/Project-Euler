#!/usr/bin/env python3

import collections

import primesieve


N = 10 ** 8
MODULUS = 1_000_000_007


def main():
    primes = primesieve.primes(N)
    n_primes = len(primes)
    # pi_npcnt_seq keeps track of nonprime counts in a series of pi
    # sequences. e.g. for (10, 4), (10, 4, 2), (10, 4, 2, 1), the
    # sequence is (2, 2, 2).
    pi_npcnt_seq = ()
    # pi_npcnt_seqs[i] is pi_npcnt_seq for primes[i].
    pi_npcnt_seqs = []
    pi_nextprime_index = 0
    pi_nextprime = 2
    pi_currently_prime = False
    P_counts = collections.defaultdict(int)
    for i, p in enumerate(primes):
        pi = i + 1
        if pi == pi_nextprime:
            pi_currently_prime = True
            pi_npcnt_seq = pi_npcnt_seqs[pi_nextprime_index]
            pi_nextprime_index += 1
            pi_nextprime = primes[pi_nextprime_index]
        # The non-prime count sequence for p should be
        #
        #   (0, *pi_npcnt_seq)
        #
        # if pi_currently_prime, or
        #
        #   (1, *pi_npcnt_seq)
        #
        # if not.
        #
        # Then, for all p < n < next_prime, the non-prime count sequence
        # is one plus that of p.
        pi_npcnt_seqs.append(
            tuple([0 if pi_currently_prime else 1] + list(pi_npcnt_seq))
        )
        if pi < n_primes:
            n_composites = primes[pi] - p - 1
        else:
            n_composites = N - p
        for k in pi_npcnt_seqs[i]:
            P_counts[k] += 1
            P_counts[k + 1] += n_composites
        if pi_currently_prime:
            # Once we increment pi it will no longer be a prime, so the
            # non-prime count of the each pi-sequence should be
            # incremented.
            pi_npcnt_seq = tuple(k + 1 for k in pi_npcnt_seq)
            pi_currently_prime = False
    r = 1
    for count in P_counts.values():
        r = (r * count) % MODULUS
    print(r)


if __name__ == "__main__":
    main()
