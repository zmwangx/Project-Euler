#include <algorithm>
#include <iostream>

#define N 1'000'000

int mdrs[N];

inline int digital_root(int n)
{
    while (n >= 10) {
        int sum = 0;
        while (n >= 10) {
            sum += n % 10;
            n /= 10;
        }
        sum += n;
        n = sum;
    }
    return n;
}

long long calculate_mdrs()
{
    long long sum = 0;
    for (int n = 2; n < N; n++) {
        int dr = digital_root(n);
        if (dr > mdrs[n]) {
            mdrs[n] = dr;
        }
        int sn = mdrs[n];
        sum += sn;
        int limit = std::min(n, N / n);
        for (int m = 2; m <= limit; ++m) {
            int nm = n * m;
            int s = sn + mdrs[m];
            if (s > mdrs[nm]) {
                mdrs[nm] = s;
            }
        }
    }
    return sum;
}

int main()
{
    std::cout << calculate_mdrs() << std::endl;
    return 0;
}
