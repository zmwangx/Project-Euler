#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <primesieve.hpp>

const int N = 100'000'000;
const int M = N * 1.5;
const int PRIME_LIMIT = M > 170 ? M / 10 : 17;

inline int first_fibo_divisible_by_p(int p)
{
    int a = 1, b = 1, i = 2;
    int max_index = M / p;
    while (i < max_index) {
        i++;
        int c = b;
        b += a;
        if (b >= p) {
            b -= p;
        }
        if (b == 0) {
            return i;
        }
        a = c;
    }
    return 0;
}

int main()
{
    std::vector<int> primes;
    primesieve::generate_primes(PRIME_LIMIT, &primes);
    std::vector<bool> squarefree(M + 1, true);
    for (auto p : primes) {
        int i = first_fibo_divisible_by_p(p);
        if (i == 0) {
            continue;
        }
        i *= p;
        for (int j = i; j <= M; j += i) {
            squarefree[j] = false;
        }
    }
    int count = 0;
    for (int i = 1; i <= M; ++i) {
        if (squarefree[i]) {
            count++;
            if (count == N) {
                std::cout << i << std::endl;
                // Call WolframScript to calculate the Fibonacci number at index i.
                char cmd[256];
                std::sprintf(cmd, "./solution.m %d", i);
                std::system(cmd);
                break;
            }
        }
    }
    return 0;
}
