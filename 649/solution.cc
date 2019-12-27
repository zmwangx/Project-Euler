#include <array>
#include <cassert>
#include <iostream>
#include <vector>

#include <gmpxx.h>

const long N = 10'000'019;
const int C = 100;
// const long N = 9;
// const int C = 3;
const int HEAPS = C * 2;
const long MOD = 1'000'000'000;

std::vector<mpz_class> factorial;

void calculate_factorial()
{
    mpz_class prod(1);
    factorial.push_back(prod);
    for (int i = 1; i <= HEAPS; ++i) {
        prod *= i;
        factorial.push_back(prod);
    }
}

inline mpz_class multinomial(int n0, int n1, int n2, int n3, int n4)
{
    return factorial[HEAPS] / factorial[n0] / factorial[n1] / factorial[n2] / factorial[n3] / factorial[n4];
}

inline int ipow(int x, int n)
{
    int result = 1;
    for (int i = 0; i < n; ++i) {
        result *= x;
    }
    return result;
}

int main()
{
    calculate_factorial();

    mpz_class mod(MOD);

    long q = N / 9, r = N % 9;
    long k[5];
    k[0] = 2 * q;
    k[1] = 2 * q;
    k[2] = 2 * q;
    k[3] = 2 * q;
    k[4] = q;
    for (int i = 0; i < r; ++i) {
        switch (i) {
        case 0:
        case 1:
            k[0]++;
            break;
        case 2:
        case 3:
            k[1]++;
            break;
        case 4:
        case 5:
            k[2]++;
            break;
        case 6:
        case 7:
            k[3]++;
            break;
        case 8:
            k[4]++;
            break;
        }
    }
    assert(k[0] + k[1] + k[2] + k[3] + k[4] == N);
    std::array<std::array<mpz_class, HEAPS + 1>, 5> pow;
    for (int i = 0; i < 5; ++i) {
        pow[i][0] = 1;
        for (int j = 1; j <= HEAPS; ++j) {
            pow[i][j] = pow[i][j - 1] * k[i] % mod;
        }
    }

    mpz_class count(0);
    for (int n0 = 0; n0 <= HEAPS; ++n0) {
        int m1 = HEAPS - n0;
        for (int n1 = 0; n1 <= m1; ++n1) {
            int m2 = m1 - n1;
            for (int n2 = 0; n2 <= m2; ++n2) {
                int m3 = m2 - n2;
                for (int n3 = 0; n3 <= m3; ++n3) {
                    int n4 = m3 - n3;
                    int mask = (n1 & 1) + ((n2 & 1) << 1) + ((n3 & 1) << 2) + ((n4 & 1) << 3);
                    if (mask == 0 || mask == 0b111) {
                        (count += multinomial(n0, n1, n2, n3, n4) % mod
                                * pow[0][n0] * pow[1][n1] * pow[2][n2] * pow[3][n3] * pow[4][n4])
                            %= mod;
                    }
                }
            }
        }
    }
    mpz_class total;
    mpz_powm_ui(total.get_mpz_t(), mpz_class(N).get_mpz_t(), HEAPS, mod.get_mpz_t());
    std::cout << (total - count + mod) % mod << std::endl;
}
