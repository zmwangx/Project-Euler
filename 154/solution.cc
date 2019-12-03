#include <algorithm>
#include <iostream>

const int N = 200'000;
const int M = 12;
int v2[N + 1];
int v5[N + 1];

void calculate_orders()
{
    for (int i = 1; i <= N; i++) {
        int v2_i = 0;
        int v5_i = 0;
        int ii = i;
        while (ii % 2 == 0) {
            ii /= 2;
            v2_i++;
        }
        ii = i;
        while (ii % 5 == 0) {
            ii /= 5;
            v5_i++;
        }
        v2[i] = v2[i - 1] + v2_i;
        v5[i] = v5[i - 1] + v5_i;
    }
}

long long search()
{
    long long count = 0;
    int v2_n = v2[N];
    int v5_n = v5[N];
    for (int n1 = N; n1 * 3 >= N; n1--) {
        int remaining = N - n1;
        int v2_nmn1 = v2_n - v2[n1];
        int v5_nmn1 = v5_n - v5[n1];
        for (int n2 = std::min(remaining, n1); n2 * 2 >= remaining; n2--) {
            int n3 = remaining - n2;
            if (v2_nmn1 - v2[n2] - v2[n3] >= M && v5_nmn1 - v5[n2] - v5[n3] >= M) {
                if (n1 == n2) {
                    if (n2 == n3) {
                        count += 1;
                    } else {
                        count += 3;
                    }
                } else {
                    if (n2 == n3) {
                        count += 3;
                    } else {
                        count += 6;
                    }
                }
            }
        }
    }
    return count;
}

int main()
{
    calculate_orders();
    std::cout << search() << std::endl;
    return 0;
}
