#include <array>
#include <cmath>
#include <iostream>

const auto LIMIT = 64'000'000ULL;
std::array<unsigned long long, LIMIT + 1> sigma;

void calculate_sigmas()
{
    std::fill(sigma.begin(), sigma.end(), 1);
    for (auto i = 2ULL; i <= LIMIT; ++i) {
        auto i_square = i * i;
        for (auto j = i; j <= LIMIT; j += i) {
            sigma[j] += i_square;
        }
    }
}

inline bool is_perfect_square(unsigned long long n)
{
    unsigned long long root = std::sqrt(n);
    return root * root == n;
}

size_t sum_perfect_ns()
{
    size_t sum = 0;
    for (auto i = 1ULL; i <= LIMIT; ++i) {
        if (is_perfect_square(sigma[i])) {
            std::cout << i << " " << sigma[i] << std::endl;
            sum += i;
        }
    }
    return sum;
}

int main()
{
    calculate_sigmas();
    std::cout << sum_perfect_ns() << std::endl;
    return 0;
}
