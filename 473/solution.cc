#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef long long ll;
typedef long double ld;
typedef unsigned long long mask_t;
// Algebraic integers a + b sqrt(5) in Z(sqrt(5)).
typedef std::pair<ll, ll> algebraic_t;

const ll LIMIT = 10'000'000'000;

int main()
{
    std::vector<algebraic_t> s = { { 1, 1 }, { 4, 0 } };
    ld sqrt5 = std::sqrtl(5);
    for (int i = 2;; ++i) {
        auto [aim1, bim1] = s[i - 1];
        auto [aim2, bim2] = s[i - 2];
        ll ai = 5 * bim1 - aim2;
        ll bi = aim1 - bim2;
        if (ai + bi * sqrt5 > 2 * LIMIT) {
            break;
        }
        s.push_back({ ai, bi });
        // std::cout << "2S(" << i << ") = " << ai << (bi >= 0 ? " + " : " - ") << std::abs(bi) << " sqrt(5)" << std::endl;
    }
    int max_index = s.size() - 1;
    std::vector<ll> pairsum(max_index + 1, 0);
    for (int i = 5; i <= max_index; i += 2) {
        pairsum[i] = (s[i].first + s[i - 3].first) / 2;
    }

    // Queue elements are of the form {next_index, current_sum, mask}.
    std::queue<std::tuple<int, ll, mask_t>> q;
    q.push({ 5, 0, 0 }); // 0
    q.push({ 5, 2, 0b111 }); // S1
    ll total = 1;
    while (!q.empty()) {
        auto [i, current_sum, mask] = q.front();
        q.pop();
        if (i > max_index) {
            total += current_sum;
            continue;
        }
        int im3 = i - 3;
        q.push({ i + 2, current_sum, mask });
        if (!(mask & (1ULL << im3))) {
            ll new_sum = current_sum + pairsum[i];
            if (new_sum <= LIMIT) {
                q.push({ i + 2, new_sum, mask | (0b111111ULL << (i - 4)) });
            }
        }
    }
    std::cout << total << std::endl;

    return 0;
}
