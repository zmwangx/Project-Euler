#include <iostream>

const int N = 10'000'000;
int s[N + 1];

int main()
{
    long long sum = 0;
    for (int n = 2; n <= N; ++n) {
        if (n % 1000'000 == 0) {
            std::cerr << "progress: " << n << std::endl;
        }
        if (!s[n]) {
            // std::cout << n << " " << 1 << std::endl;
            sum += 1;
            for (int m = n * 2; m <= N; m += n) {
                int mm = m;
                while (mm % n == 0) {
                    mm /= n;
                }
                int pp = m / mm;
                if (!s[m] || s[m] < pp) {
                    // Record the largest prime power factor.
                    s[m] = pp;
                }
            }
        } else {
            int pp = s[n];
            for (long long m = n - pp; m >= 0; m -= pp) {
                long long a = m + 1;
                if (a * a % n == a) {
                    // std::cout << n << " " << a << std::endl;
                    sum += a;
                    break;
                }
                a = m;
                if (a * a % n == a) {
                    // std::cout << n << " " << a << std::endl;
                    sum += a;
                    break;
                }
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
