#include <iostream>
#include <queue>
#include <vector>

typedef unsigned long long ull;

std::vector<ull> factors = { 47, 43, 41, 37, 31, 29, 23, 19, 17, 13, 11, 7, 5, 3, 2 };

int main()
{
    std::priority_queue<ull, std::vector<ull>, std::greater<ull>> q;
    q.push(1);
    ull last_smooth = -1;
    ull sum = 0;
    while (!q.empty()) {
        ull smooth = q.top();
        q.pop();
        if (smooth == last_smooth + 1) {
            sum += last_smooth;
            std::cout << last_smooth << " " << sum << std::endl;
        }
        for (auto p : factors) {
            q.push(smooth * p);
            // We require prime factors to be non-decreasing to avoid duplicates.
            if (smooth % p == 0) {
                break;
            }
        }
        last_smooth = smooth;
    }
    return 0;
}
