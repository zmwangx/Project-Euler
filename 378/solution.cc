#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include <primesieve.hpp>

const long N = 60'000'000;
const unsigned long long MOD = 1'000'000'000'000'000'000;

typedef std::vector<std::pair<long, long>> factorization_t;

std::vector<factorization_t> fact(N + 2);
std::array<long, N + 1> dT;

void compute_factorizations()
{
    std::cerr << "computing factorizations..." << std::endl;
    std::vector<long> primes;
    long max = N + 1;
    primesieve::generate_primes(max, &primes);
    for (auto p : primes) {
        for (long n = p; n <= max; n += p) {
            long m = n;
            long exp = 0;
            while (m % p == 0) {
                m /= p;
                exp++;
            }
            fact[n].push_back({ p, exp });
        }
    }
}

void compute_dT()
{
    std::cerr << "computing dT..." << std::endl;
    for (long i = 1; i <= N; ++i) {
        if (i % 1'000'000 == 0) {
            std::cerr << "progress: " << i << "/" << N << std::endl;
        }
        std::unordered_map<long, long> prime_factors;
        for (auto& [p, exp] : fact[i]) {
            prime_factors[p] += exp;
        }
        for (auto& [p, exp] : fact[i + 1]) {
            prime_factors[p] += exp;
        }
        prime_factors[2]--;
        long result = 1;
        for (auto& [p, exp] : prime_factors) {
            result *= exp + 1;
        }
        dT[i] = result;
    }
}

// Binary search tree using buckets. Values must be in the range [1, max].
class BucketBinarySearchTree {
    long height_;
    std::vector<long> c_;

public:
    BucketBinarySearchTree(long max);
    // Inserts x into tree and returns the current number of strictly smaller
    // than x elements.
    long insert_smaller(long x);
    // Inserts x into tree and returns the current number of strictly greater
    // than x elements.
    long insert_greater(long x);
    void clear();
};

BucketBinarySearchTree::BucketBinarySearchTree(long max)
    : height_(long(std::log2(max)) + 1)
    , c_(1 << height_, 0)
{
}

long BucketBinarySearchTree::insert_smaller(long x)
{
    long h = height_ - 1;
    long node = 1 << h, next;
    long smaller = 0;
    while (x != node) {
        h--;
        if (x > node) {
            next = node + (1 << h);
            // Node and the entire left subtree are smaller.
            smaller += c_[node] - c_[next];
        } else {
            next = node - (1 << h);
        }
        c_[node]++;
        node = next;
    }
    c_[node]++;
    if (h > 0) {
        // Elements in the left subtree are smaller.
        h--;
        smaller += c_[node - (1 << h)];
    }
    return smaller;
}

long BucketBinarySearchTree::insert_greater(long x)
{
    long h = height_ - 1;
    long node = 1 << h, next;
    long greater = 0;
    while (x != node) {
        h--;
        if (x < node) {
            next = node - (1 << h);
            // Node and the entire right subtree are greater.
            greater += c_[node] - c_[next];
        } else {
            next = node + (1 << h);
        }
        c_[node]++;
        node = next;
    }
    c_[node]++;
    if (h > 0) {
        // Elements in the right subtree are greater.
        h--;
        greater += c_[node + (1 << h)];
    }
    return greater;
}

void BucketBinarySearchTree::clear()
{
    std::fill(c_.begin(), c_.end(), 0);
}

void compute_Tr()
{
    std::cerr << "computing Tr..." << std::endl;
    long max = *std::max_element(dT.begin(), dT.end());
    std::cerr << "max dT: " << max << std::endl;

    std::vector<long> c1(N + 1), c2(N + 1);
    BucketBinarySearchTree tree(max);
    for (long i = 1; i <= N; ++i) {
        c1[i] = tree.insert_greater(dT[i]);
    }
    tree.clear();
    for (long i = N; i >= 1; --i) {
        c2[i] = tree.insert_smaller(dT[i]);
    }

    unsigned long long count = 0;
    for (long j = 2; j <= N - 1; ++j) {
        (count += c1[j] * c2[j]) %= MOD;
    }
    std::cout << count << std::endl;
}

int main()
{
    compute_factorizations();
    compute_dT();
    std::vector<factorization_t>().swap(fact);
    compute_Tr();
    return 0;
}
