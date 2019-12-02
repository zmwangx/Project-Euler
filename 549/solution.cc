#include <iostream>

const unsigned N = 100'000'000;
unsigned f[N + 1];
unsigned s[N + 1];

void sieve()
{
    for (unsigned n = 2; n <= N; n++) {
        if (!f[n]) {
            for (unsigned m = n * 2; m <= N; m += n) {
                unsigned mm = m;
                while (mm % n == 0) {
                    mm /= n;
                }
                f[m] = mm;
            }

            s[n] = n;
            unsigned nalpha = n;
            unsigned exponent = 1;
            unsigned m = n;
            unsigned vn = 1;
            while (nalpha <= N / n) {
                nalpha *= n;
                exponent++;
                if (vn < exponent) {
                    m += n;
                    unsigned mm = m;
                    while (mm % n == 0) {
                        vn++;
                        mm /= n;
                    }
                }
                s[nalpha] = m;
                // std::cout << "s(" << n << "^" << exponent << ") = " << m << std::endl;
            }
        }
    }
}

unsigned long long calc_S()
{
    unsigned long long sum = 0;
    for (unsigned n = 2; n <= N; n++) {
        if (!f[n]) {
            sum += s[n];
            continue;
        }
        unsigned sn = 0;
        unsigned m = n;
        while (f[m]) {
            unsigned palpha = m / f[m];
            if (s[palpha] > sn) {
                sn = s[palpha];
            }
            m = f[m];
        }
        sum += sn;
    }
    return sum;
}

int main()
{
    sieve();
    std::cout << calc_S() << std::endl;
    return 0;
}
