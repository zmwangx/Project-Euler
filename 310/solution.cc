#include <cmath>
#include <iostream>
#include <vector>

const int LIMIT = 100'000;

inline bool nimmer_sum_is_zero(int m1, int m2, int m3)
{
    while (m1 || m2 || m3) {
        if (((m1 & 1) + (m2 & 1) + (m3 & 1)) & 1) {
            return false;
        }
        m1 >>= 1;
        m2 >>= 1;
        m3 >>= 1;
    }
    return true;
}

inline long long combo_with_repl(long long n, int k)
{
    switch (k) {
    case 1:
        return n;
    case 2:
        return (n + 1) * n / 2;
    case 3:
        return (n + 2) * (n + 1) * n / 6;
    default:
        // Unreachable.
        return 0;
    }
}

int main()
{
    std::vector<int> nimmers(LIMIT + 1);
    int nimmer_max = 0;
    for (int i = 1; i <= LIMIT; ++i) {
        std::vector<bool> seen(nimmer_max + 2, false);
        int root = std::sqrt(i);
        for (int j = 1; j <= root; ++j) {
            seen[nimmers[i - j * j]] = true;
        }
        int m = 0;
        while (seen[m]) {
            m++;
        }
        if (m > nimmer_max) {
            nimmer_max = m;
        }
        nimmers[i] = m;
    }
    std::vector<int> nimmer_count(nimmer_max + 1, 0);
    for (int i = 0; i <= LIMIT; ++i) {
        nimmer_count[nimmers[i]]++;
    }
    long long total_count = 0;
    for (int m1 = 0; m1 <= nimmer_max; ++m1) {
        for (int m2 = m1; m2 <= nimmer_max; ++m2) {
            for (int m3 = m2; m3 <= nimmer_max; ++m3) {
                if (!nimmer_sum_is_zero(m1, m2, m3)) {
                    continue;
                }
                int k1 = nimmer_count[m1];
                int k2 = nimmer_count[m2];
                int k3 = nimmer_count[m3];
                if (m1 != m2) {
                    if (m2 != m3) {
                        total_count += combo_with_repl(k1, 1) * combo_with_repl(k2, 1) * combo_with_repl(k3, 1);
                    } else {
                        total_count += combo_with_repl(k1, 1) * combo_with_repl(k2, 2);
                    }
                } else {
                    if (m2 != m3) {
                        total_count += combo_with_repl(k1, 2) * combo_with_repl(k3, 1);
                    } else {
                        total_count += combo_with_repl(k1, 3);
                    }
                }
            }
        }
    }
    std::cout << total_count << std::endl;
    return 0;
}
