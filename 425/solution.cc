#include <algorithm>
#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <primesieve.hpp>

const int N = 10'000'000;

int main()
{
    std::vector<int> primes;
    primesieve::generate_primes(N, &primes);
    std::unordered_set<int> primeset(primes.begin(), primes.end());

    // Adjacency list for the graph.
    std::unordered_map<int, std::vector<int>> neighbors;
    for (auto p : primes) {
        std::vector<int> v;
        int pow10 = 1;
        int q, repl;
        while (pow10 < p * 10) {
            int d = (p / pow10) % 10;
            q = p - pow10 * d;
            repl = 0;
            while (repl < 10 && q <= N) {
                if (q != p && primeset.find(q) != primeset.end()) {
                    v.push_back(q);
                }
                q += pow10;
                repl += 1;
            }
            pow10 *= 10;
        }
        std::sort(v.begin(), v.end());
        neighbors[p] = v;
    }

    std::unordered_map<int, int> min_seqmax;
    for (auto p : primes) {
        min_seqmax[p] = 0;
    }
    min_seqmax[2] = 2;
    std::deque<std::pair<int, int>> queue;
    queue.push_back(std::make_pair(2, 2));
    while (!queue.empty()) {
        auto pair = queue.front();
        queue.pop_front();
        int p = pair.first, seqmax = pair.second;
        for (auto q : neighbors[p]) {
            int new_seqmax = std::max(seqmax, q);
            auto it = min_seqmax.find(q);
            if (it->second == 0 || it->second > new_seqmax) {
                it->second = new_seqmax;
                queue.push_back(std::make_pair(q, new_seqmax));
            }
        }
    }

    long long sum = 0;
    for (auto pair : min_seqmax) {
        if (pair.second == 0 || pair.first < pair.second) {
            sum += pair.first;
        }
    }
    std::cout << sum << std::endl;

    return 0;
}
