#include <cstdint>
#include <iostream>
#include <vector>

const uint64_t LIMIT = 1'000'000;

int main()
{
    std::vector<uint32_t> g = { 0, 1 };
    std::vector<uint64_t> sums = { 0, 1 };
    uint64_t i = 1;
    uint64_t sum1 = 1, sum2 = 1, last_sum1, last_sum2;
    uint64_t total = 1;
    for (uint64_t n = 2; n < LIMIT; ++n) {
        uint64_t n3 = n * n * n;
        while (sum2 <= n3) {
            i++;
            uint32_t gi = 1 + g[i - g[g[i - 1]]];
            g.push_back(gi);
            last_sum1 = sum1;
            sum1 += gi;
            last_sum2 = sum2;
            sum2 += gi * i;
            continue;
        }
        total += last_sum1 + (n3 - last_sum2 - 1) / i + 1;
    }
    std::cout << total << std::endl;
}
