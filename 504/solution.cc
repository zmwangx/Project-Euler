#include <cmath>
#include <iostream>
#include <map>

const int M = 100;
int gcd[M + 1][M + 1];

void calc_gcd()
{
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= M; j++) {
            int a = i;
            int b = j;
            while (b != 0) {
                a %= b;
                a ^= b;
                b ^= a;
                a ^= b;
            }
            gcd[i][j] = a;
        }
    }
}

int is_square(int n)
{
    int root = int(sqrt(n));
    return root * root == n;
}

int search()
{
    int count = 0;
    // WLOG, a == max(a, b, c, d), and b >= d.
    for (int a = 1; a <= M; a++) {
        for (int b = 1; b <= a; b++) {
            for (int c = 1; c <= a; c++) {
                for (int d = 1; d <= b; d++) {
                    int points = (a * b + b * c + c * d + d * a - gcd[a][b] - gcd[b][c] - gcd[c][d] - gcd[d][a]) / 2 + 1;
                    if (is_square(points)) {
                        count += 1 << ((a != b) + (a != c) + (b != d));
                        // std::cout << "("
                        //           << a << ", " << b << ", " << c << ", " << d
                        //           << ") " << (1 << ((a != b) + (a != c) + (b != d))) << std::endl;
                    }
                }
            }
        }
    }
    return count;
}

int main()
{
    calc_gcd();
    std::cout << search() << std::endl;
    return 0;
}
