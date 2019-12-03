#include <iostream>

const unsigned N = 100'000'000;

inline unsigned gcd(unsigned a, unsigned b)
{
    while (b != 0) {
        a %= b;
        a ^= b;
        b ^= a;
        a ^= b;
    }
    return a;
}

int main()
{
    unsigned long long sum = 0;
    for (unsigned d = 1; d <= N; d++) {
        sum += d * (N / d);
    }
    for (unsigned a = 1; a * a <= N; a++) {
        for (unsigned b = 1, n = a * a + b * b; b <= a && n <= N; b++, n = a * a + b * b) {
            if (gcd(a, b) != 1) {
                continue;
            }
            unsigned contrib = ((a == b) ? 1 : 2) * (a + b);
            for (unsigned i = 1; i * n <= N; i++) {
                sum += contrib * i * (N / (i * n));
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
