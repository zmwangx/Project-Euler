#include <iostream>

#include <ulong_extras.h>

typedef long long int64;

const int64 N = 100'000'000'000'000;
const int64 MOD = 982451653;

int main()
{
    // 1! = 1
    // f(0) = 0
    // g(0) = 1
    int64 n = 1, factorial = 1, f = 0, g = 1, count = 1, sum = 1;
    while (1) {
        // (n+1)! = n! * (n+1).
        (factorial *= (n + 1)) %= MOD;
        if (N - count >= n + 2) {
            // g(n) = (n+2) g(n-1) + (n+1)!
            g = ((n + 2) * g + factorial) % MOD;
            // f(n) = n g(n) + n(n+3)/2 (n+1)!
            f = (n * g + n * (n + 3) / 2 % MOD * factorial) % MOD;
            count += n + 2;
            (sum += f) %= MOD;
            // std::cout << count << " " << n << " " << g << " " << f << std::endl;
        } else {
            int64_t k = N - count;
            // (n+2)! = (n+1)! * (n+2)
            (factorial *= (n + 2)) %= MOD;
            // Add n (n+2)! (1/(n+2) + 1/(n+1) + ... + 1/(n-k+3)).
            int64_t invsum = 0;
            for (int64_t i = n + 2; i >= n - k + 3; --i) {
                (invsum += n_invmod(i, MOD)) %= MOD;
            }
            (sum += n * factorial % MOD * invsum) %= MOD;
            break;
        }
        n++;
    }
    std::cout << sum << std::endl;
    return 0;
}
