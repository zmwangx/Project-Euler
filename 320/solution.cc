#include <chrono>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

typedef long long ll;
typedef boost::multiprecision::int128_t int128_t;

const int N = 1'000'000;
const ll MULTIPLIER = 1234567890;
const ll MOD = 1E18;
const ll REMAINDER_THRESHOLD = 20;

std::vector<int> pp(N + 1, 0);
std::vector<int> primes;

void sieve()
{
    for (int n = 2; n <= N; ++n) {
        if (pp[n] == 0) {
            primes.push_back(n);
            for (int m = n + n; m <= N; m += n) {
                pp[m] = n;
            }
        }
    }
}

inline ll factorial_exponent(ll n, int p)
{
    ll result = 0;
    while (n) {
        n /= p;
        result += n;
    }
    return result;
}

// Returns a vector of unsatisfied prime and exponent pairs.
inline std::vector<std::pair<int, ll>> test_divisiblility(ll m, const std::vector<std::pair<int, ll>>& targets)
{
    std::vector<std::pair<int, ll>> unsatisfied;
    for (auto [p, exp] : targets) {
        if (factorial_exponent(m, p) < exp) {
            unsatisfied.push_back({ p, exp });
        }
    }
    return unsatisfied;
}

inline ll calc_N(int n, ll previous)
{
    std::vector<std::pair<int, ll>> targets;
    for (auto p : primes) {
        if (p > n) {
            break;
        }
        if (n % p > REMAINDER_THRESHOLD) {
            continue;
        }
        targets.push_back({ p, factorial_exponent(n, p) * MULTIPLIER });
    }

    auto unsatisfied = test_divisiblility(previous, targets);
    if (unsatisfied.size() == 0) {
        return previous;
    }
    targets.swap(unsatisfied);
    ll lower = previous;
    ll upper = n * MULTIPLIER;

#define TEST_AND_UPDATE_BOUNDS(x)                     \
    do {                                              \
        unsatisfied = test_divisiblility(x, targets); \
        if (unsatisfied.size() > 0) {                 \
            lower = x;                                \
            targets.swap(unsatisfied);                \
        } else {                                      \
            upper = x;                                \
        }                                             \
    } while (0)

    TEST_AND_UPDATE_BOUNDS(upper - MULTIPLIER);
    while (lower < upper - 1) {
        ll mid = (lower + upper) / 2;
        TEST_AND_UPDATE_BOUNDS(mid);
    }
    return upper;
}

int main()
{
    sieve();
    int128_t sum = 0;
    ll prev = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 10; i <= N; ++i) {
        if (i % 100'000 == 0) {
            auto now = std::chrono::high_resolution_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
            std::cerr << ms << "ms " << i << std::endl;
        }
        prev = calc_N(i, prev);
        sum += prev;
        // std::cout << i << " " << prev << " "
        //           << std::fixed << std::setprecision(10) << double(prev) / MULTIPLIER << std::endl;
    }
    std::cout << sum << " " << sum % MOD << std::endl;
    return 0;
}
