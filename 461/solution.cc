#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

typedef long double ld;

const ld PI = 3.141592653589793238462643383279502884L;
const ld N = 10000;

int main()
{
    // Single f values not exceeding PI.
    std::vector<ld> f;
    ld best_single_greater_approximation = PI * 2;
    int best_single_greater_approximator_square_sum = 0;
    int k = 0;
    while (1) {
        ld fnk = expl(k / N) - 1;
        if (fnk > PI) {
            if (fnk < best_single_greater_approximation) {
                best_single_greater_approximation = fnk;
                best_single_greater_approximator_square_sum = k * k;
            }
            break;
        }
        f.push_back(fnk);
        k++;
    }
    int max_k = k;

    // Sum of two f values not exceeding PI, and corresponding index square sums.
    std::vector<std::pair<ld, int>> ff;
    ld best_double_greater_approximation = PI * 2;
    int best_double_greater_approximator_square_sum = 0;
    for (int i = 0; i < max_k; ++i) {
        for (int j = i; j < max_k; ++j) {
            ld s = f[i] + f[j];
            int ss = i * i + j * j;
            if (s > PI) {
                if (s < best_double_greater_approximation) {
                    best_double_greater_approximation = s;
                    best_double_greater_approximator_square_sum = ss;
                }
                // f is strictly increasing, so further increasing j will only
                // lead us further away from PI.
                break;
            }
            ff.push_back(std::make_pair(s, ss));
        }
    }
    ff.push_back(std::make_pair(
        best_double_greater_approximation,
        best_double_greater_approximator_square_sum));
    ff.push_back(std::make_pair(
        best_double_greater_approximation,
        best_double_greater_approximator_square_sum));
    auto cmp = [](auto& a, auto& b) { return a.first < b.first; };
    std::sort(ff.begin(), ff.end(), cmp);

    ld best_error = PI;
    int best_approximator_square_sum;
    for (auto& pair : ff) {
        ld s1 = pair.first;
        int ss1 = pair.second;
        auto it = std::upper_bound(ff.begin(), ff.end(), std::make_pair(PI - s1, 0), cmp);
        if (it != ff.begin()) {
            ld s2 = (it - 1)->first;
            int ss2 = (it - 1)->second;
            ld error = std::abs(s1 + s2 - PI);
            if (error < best_error) {
                best_error = error;
                best_approximator_square_sum = ss1 + ss2;
            }
        }
        if (it != ff.end()) {
            ld s2 = it->first;
            int ss2 = it->second;
            ld error = std::abs(s1 + s2 - PI);
            if (error < best_error) {
                best_error = error;
                best_approximator_square_sum = ss1 + ss2;
            }
        }
    }
    std::cout << "error: " << best_error << " " << std::endl
              << "square sum: " << best_approximator_square_sum << std::endl;

    return 0;
}
