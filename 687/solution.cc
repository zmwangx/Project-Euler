#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <random>

std::array<int, 52> ranks = {
    1, 1, 1, 1,
    2, 2, 2, 2,
    3, 3, 3, 3,
    4, 4, 4, 4,
    5, 5, 5, 5,
    6, 6, 6, 6,
    7, 7, 7, 7,
    8, 8, 8, 8,
    9, 9, 9, 9,
    10, 10, 10, 10,
    11, 11, 11, 11,
    12, 12, 12, 12,
    13, 13, 13, 13
};
std::array<bool, 14> perfect;

inline int perfect_count()
{
    std::fill(perfect.begin(), perfect.end(), true);
    for (int i = 0; i < 51; ++i) {
        if (ranks[i] == ranks[i + 1]) {
            perfect[ranks[i]] = false;
        }
    }
    int count = 0;
    for (int rank = 1; rank <= 13; ++rank) {
        if (perfect[rank]) {
            count++;
        }
    }
    return count;
}

int main()
{
    int total = 0;
    std::array<int, 14> counters{};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto g = std::default_random_engine(seed);
    for (; total < 10'000'000; ++total) {
        std::shuffle(ranks.begin(), ranks.end(), g);
        counters[perfect_count()]++;
    }
    double expectation = 0;
    double prime_prob = 0;
    for (int i = 0; i <= 13; ++i) {
        double prob = double(counters[i]) / total;
        expectation += i * counters[i];
        if (i == 2 || i == 3 || i == 5 || i == 7 || i == 11 || i == 13) {
            prime_prob += prob;
        }
        std::cout << i << "\t" << counters[i] << "\t" << prob << std::endl;
    }
    expectation /= total;
    std::cout << expectation << std::endl;
    std::cout << prime_prob << std::endl;
}
