#include <cstdint>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>
#include <primesieve.hpp>

typedef boost::multiprecision::int128_t int128_t;

const int64_t N = 10'000'000'000;

int main()
{
    std::vector<int> primes;
    primesieve::generate_primes(int(sqrt(N)), &primes);
    int nprimes = primes.size();
    int128_t result = 0;
    int128_t total_sum = N * (N + 1) / 2 - 1;
    std::stack<std::tuple<int, int, int64_t>> s;
    s.push({ 0, -1, 1 });
    int64_t cycle_count = 0;
    while (!s.empty()) {
        auto [length, last_index, product] = s.top();
        s.pop();
        cycle_count++;
        if (cycle_count % 1'000'000 == 0) {
            std::cerr << cycle_count << " " << length << " " << product << std::endl;
        }
        if (length > 0) {
            int sign = length % 2 == 0 ? -1 : 1;
            int64_t count = N / product;
            result += sign * primes[last_index] * count;
            total_sum -= sign * product * count * (count + 1) / 2;
        }
        length++;
        for (int i = last_index + 1; i < nprimes; ++i) {
            int64_t new_product = product * primes[i];
            if (new_product <= N) {
                s.push({ length, i, new_product });
            }
        }
    }
    std::cout << result + total_sum << std::endl;
    return 0;
}
