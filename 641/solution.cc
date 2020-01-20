#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

#include <primesieve.hpp>

#define LG_N 36

#define SEARCH_METHOD_BFS 1
#define SEARCH_METHOD_STACK_DFS 2
#define SEARCH_METHOD_FLAT_DFS 3

#define SEARCH_METHOD SEARCH_METHOD_FLAT_DFS

std::vector<int> prime;
std::vector<double> lg_prime;

int count_numbers_with_divisor_count_decomp(const std::vector<int>& decomp)
{
#if SEARCH_METHOD == SEARCH_METHOD_FLAT_DFS
    int nfactors = decomp.size();
    if (nfactors == 1) {
        double max_lg_p = double(LG_N) / (decomp[0] - 1);
        return std::upper_bound(lg_prime.begin(), lg_prime.end(), max_lg_p) - lg_prime.begin();
    }

    // Tree-walking based linear space DFS.
    int count = 0;
    int factors_filled = 0;
    std::vector<int> factor_indices;
    double lg = 0;
    while (1) {
        int exponent = decomp[factors_filled] - 1;
        bool same_as_prev_exponent = factors_filled && (decomp[factors_filled] == decomp[factors_filled - 1]);
        if (factors_filled == nfactors - 1) {
            // "Leaf node", count.
            double max_lg_p = (LG_N - lg) / exponent;
            int p_upper_index = std::upper_bound(lg_prime.begin(), lg_prime.end(), max_lg_p) - lg_prime.begin();
            // A hack to deal with 10^N = 2^N 5^N which could be missed due to floating point imprecision.
            if (factors_filled == 1 && exponent == LG_N && same_as_prev_exponent
                && p_upper_index + factor_indices[0] == 2 && p_upper_index != 1) {
                p_upper_index++;
            }
            int p_lower_index = same_as_prev_exponent ? factor_indices.back() + 1 : 0;
            if (p_upper_index > p_lower_index) {
                int p_count = p_upper_index - p_lower_index;
                for (auto i : factor_indices) {
                    if (i >= p_lower_index && i < p_upper_index) {
                        p_count--;
                    }
                }
                count += p_count;
            }
        } else {
            // Try to walk down to first child.
            int p_index = same_as_prev_exponent ? factor_indices.back() + 1 : 0;
            while (std::find(factor_indices.begin(), factor_indices.end(), p_index) != factor_indices.end()) {
                p_index++;
            }
            if (p_index < lg_prime.size()) {
                double new_lg = lg + exponent * lg_prime[p_index];
                if (new_lg <= LG_N) {
                    factors_filled++;
                    factor_indices.push_back(p_index);
                    lg = new_lg;
                    continue;
                }
            }
        }

        // No child, try to walk to next sibling or walk up (until there's a next sibling or back at root).
        while (factors_filled) {
            exponent = decomp[factors_filled - 1] - 1;
            int prev_p_index = factor_indices.back();
            int new_p_index = prev_p_index + 1;
            while (std::find(factor_indices.begin(), factor_indices.end(), new_p_index) != factor_indices.end()) {
                new_p_index++;
            }
            if (new_p_index < lg_prime.size()) {
                double new_lg = lg + exponent * (lg_prime[new_p_index] - lg_prime[prev_p_index]);
                if (new_lg <= LG_N) {
                    // Walk to next sibling.
                    factor_indices.back() = new_p_index;
                    lg = new_lg;
                    break;
                }
            }
            // No next sibling, walk up.
            factors_filled--;
            factor_indices.pop_back();
            lg -= exponent * lg_prime[prev_p_index];
        }

        // Back to root, stop.
        if (factors_filled == 0) {
            break;
        }
    }
    return count;

#elif SEARCH_METHOD == SEARCH_METHOD_STACK_DFS
    int nfactors = decomp.size();
    if (nfactors == 1) {
        double max_lg_p = double(LG_N) / (decomp[0] - 1);
        return std::upper_bound(lg_prime.begin(), lg_prime.end(), max_lg_p) - lg_prime.begin();
    }

    std::stack<std::tuple<int, std::vector<int>, double>> s;
    int exponent = decomp[0] - 1;
    for (int j = 0; j < lg_prime.size(); ++j) {
        double lg = lg_prime[j] * exponent;
        if (lg > LG_N) {
            break;
        }
        s.push({ 1, { j }, lg });
    }
    int count = 0;
    int op = 0;
    while (!s.empty()) {
        auto [index, used_prime_indices, prev_lg] = s.top();
        s.pop();

        exponent = decomp[index] - 1;
        bool same_as_prev_exponent = (decomp[index] == decomp[index - 1]);
        double max_lg_p = (LG_N - prev_lg) / exponent;
        // The exclusive upper bound.
        int p_upper_index = std::upper_bound(lg_prime.begin(), lg_prime.end(), max_lg_p) - lg_prime.begin();
        // If exponent is the same as the previous one, make sure this prime
        // factor is greater than the previous one.
        int p_lower_index = same_as_prev_exponent ? used_prime_indices.back() + 1 : 0;
        if (p_upper_index <= p_lower_index) {
            continue;
        }

        if (index == nfactors - 1) {
            int p_count = p_upper_index - p_lower_index;
            // Exclude in-range indices that have already been used.
            for (auto i : used_prime_indices) {
                if (i >= p_lower_index && i < p_upper_index) {
                    p_count--;
                }
            }
            count += p_count;
            continue;
        }

        index++;
        for (int i = p_lower_index; i < p_upper_index; ++i) {
            if (std::find(used_prime_indices.begin(), used_prime_indices.end(), i) != used_prime_indices.end()) {
                continue;
            }
            double lg = prev_lg + lg_prime[i] * exponent;
            std::tuple<int, std::vector<int>, double> el = { index, used_prime_indices, lg };
            std::get<1>(el).push_back(i);
            s.push(el);
        }
    }
    return count;

#elif SEARCH_METHOD == SEARCH_METHOD_BFS
    std::vector<std::pair<std::vector<int>, double>> states;
    int count = 0;
    bool single_factor = (decomp.size() == 1);
    int exponent = decomp[0] - 1;
    for (int j = 0; j < lg_prime.size(); ++j) {
        double lg = lg_prime[j] * exponent;
        if (lg > LG_N) {
            break;
        }
        if (single_factor) {
            count++;
        } else {
            states.push_back({ { j }, lg });
        }
    }
    if (single_factor) {
        return count;
    }
    for (int i = 1; i < decomp.size(); ++i) {
        std::vector<std::pair<std::vector<int>, double>> prev_states;
        prev_states.swap(states);
        exponent = decomp[i] - 1;
        bool last = (i == decomp.size() - 1);
        bool same_as_prev_exponent = (exponent == decomp[i - 1] - 1);
        for (const auto& [prev_indices, prev_lg] : prev_states) {
            // If exponent is the same as the previous one, make sure this prime
            // factor is greater than the previous one.
            for (int j = same_as_prev_exponent ? *prev_indices.rbegin() + 1 : 0; j < lg_prime.size(); ++j) {
                if (std::find(prev_indices.begin(), prev_indices.end(), j) != prev_indices.end()) {
                    continue;
                }
                double lg = prev_lg + lg_prime[j] * exponent;
                if (lg > LG_N) {
                    break;
                }
                if (last) {
                    count++;
                } else {
                    std::pair<std::vector<int>, double> new_state = { prev_indices, lg };
                    new_state.first.push_back(j);
                    states.push_back(new_state);
                }
            }
        }
    }
    return count;
#endif
}

int count_numbers_with_divisor_count(int d, bool only_confirm_existence = false)
{
    if (d == 1) {
        return 1;
    }
    // d is small enough so we can brute force its divisors.
    std::vector<int> d_divisors;
    for (int i = 1; i * i <= d; ++i) {
        if (d % i == 0) {
            d_divisors.push_back(i);
        }
    }
    for (int i = d_divisors.size() - 1; i >= 0; --i) {
        if (d_divisors[i] * d_divisors[i] == d) {
            continue;
        }
        d_divisors.push_back(d / d_divisors[i]);
    }
    std::stack<std::tuple<int, std::vector<int>, double>> s;
    s.push({ d, {}, 0 });
    int count = 0;
    while (!s.empty()) {
        auto [remaining, decomp, lg_min] = s.top();
        auto last = decomp.size() ? decomp.back() : remaining;
        s.pop();
        for (auto x : d_divisors) {
            if (x > remaining || x > last) {
                // Make sure the decomposition is in non-increasing order.
                break;
            }
            if (x == 1 || remaining % x != 0) {
                continue;
            }
            if (decomp.size() >= lg_prime.size()) {
                continue;
            }
            double new_lg_min = lg_min + (x - 1) * lg_prime[decomp.size()];
            if (new_lg_min > LG_N) {
                continue;
            }
            std::vector<int> new_decomp(decomp);
            new_decomp.push_back(x);
            if (x == remaining) {
                if (only_confirm_existence) {
                    return 1;
                } else {
                    // for (auto y : new_decomp) {
                    //     std::cout << y << " ";
                    // }
                    // std::cout << ": " << new_lg_min << std::endl;
                    count += count_numbers_with_divisor_count_decomp(new_decomp);
                    continue;
                }
            }
            s.push({ remaining / x, new_decomp, new_lg_min });
        }
    }
    return count;
}

int main()
{
    // 2^4 p^4 <= N, unless 2^4 p^4 > p^6, i.e. p < 4.
    int prime_bound = std::max(std::powl(10, LG_N / 4.0) / 2, 3.0L);
    primesieve::generate_primes(prime_bound, &prime);
    for (auto p : prime) {
        lg_prime.push_back(std::log10(p));
    }

    int d_factor_bound = std::log2l(10) * LG_N + 1;
    std::vector<int> d_factors;
    primesieve::generate_primes(5, d_factor_bound, &d_factors);

    // std::cout << count_numbers_with_divisor_count(1369) << std::endl;
    // return 0;

    std::stack<std::pair<int, int>> s;
    s.push({ 1, d_factor_bound });
    long long total_count = 1;
    while (!s.empty()) {
        auto [prev_d, factor_bound] = s.top();
        s.pop();
        for (auto p : d_factors) {
            if (p > factor_bound) {
                break;
            }
            int d = prev_d * p;
            if (d % 6 == 1) {
                int d_count = count_numbers_with_divisor_count(d);
                if (d_count == 0) {
                    // d is already too large.
                    break;
                }
                std::cout << d << ": " << d_count << std::endl;
                total_count += d_count;
            } else {
                if (count_numbers_with_divisor_count(d, true) == 0) {
                    // d is already too large.
                    break;
                }
            }
            // Make sure prime factors are added in a non-increasing fashion.
            s.push({ d, p });
        }
    }
    std::cout << total_count << std::endl;

    return 0;
}
