#include <cmath>
#include <iomanip>
#include <iostream>

#define sqr(x) ((x) * (x))

typedef long double ld;

const ld N = 1E10;
const long M = 4000;
const long j_max = 12'000'000 * 2;

int main()
{
    ld N2 = sqr(N);
    ld Np1 = N + 1;
    ld minus = 2 * N - 1;
    ld sum = 0;
    for (long j = 2; j <= j_max; j += 2) {
        sum += std::powl((sqr(Np1 - j) - minus) / N2, M);
    }
    std::cout << std::fixed << std::setprecision(2) << N / 2 + sum << std::endl;
    return 0;
}
