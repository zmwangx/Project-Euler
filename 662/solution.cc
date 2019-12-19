#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

const int N = 10'000;
const long MOD = 1'000'000'007;

std::vector<std::pair<int, int>> steps;
long c[N + 1][N + 1];

void generate_steps()
{
    int x = 1, y = 2;
    steps.push_back(std::make_pair(0, 1));
    steps.push_back(std::make_pair(1, 0));
    steps.push_back(std::make_pair(0, 2));
    steps.push_back(std::make_pair(2, 0));
    while (1) {
        int z = x + y;
        if (z > std::sqrt(2.0) * N) {
            break;
        }
        if (z <= N) {
            steps.push_back(std::make_pair(0, z));
            steps.push_back(std::make_pair(z, 0));
        }
        int z2 = z * z;
        for (int i = 1; i < z && i <= N; ++i) {
            int i2 = i * i;
            if (2 * i2 > z2) {
                break;
            }
            int j = std::sqrt(z2 - i2);
            if (j <= N && z2 - i2 == j * j) {
                steps.push_back(std::make_pair(i, j));
                steps.push_back(std::make_pair(j, i));
            }
        }
        x = y;
        y = z;
    }
    std::sort(steps.begin(), steps.end());
}

void search()
{
    c[0][0] = 1;
    for (int x = 0; x <= N; ++x) {
        for (int y = 0; y < x; ++y) {
            c[x][y] = c[y][x];
        }
        for (int y = x; y <= N; ++y) {
            for (auto& step : steps) {
                int dx = step.first, dy = step.second;
                if (dx > x) {
                    break;
                }
                if (dy > y) {
                    continue;
                }
                (c[x][y] += c[x - dx][y - dy]) %= MOD;
            }
        }
    }
    std::cout << c[N][N] << std::endl;
}

int main()
{
    generate_steps();
    search();
    return 0;
}
