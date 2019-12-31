#include <iomanip>
#include <iostream>
#include <vector>

#include <primesieve.hpp>
#include <ulong_extras.h>

const long N = 10'000'000;
const long K = 100'000;
const long MOD = 10007;
const long MAX = (MOD - 1) * 2;
const long POOL_SIZE = N * 20; // > N * log2(MAX)

class Node {
public:
    static Node pool[POOL_SIZE];
    static Node* ptr;
    static const Node SINK;

    long count;
    const Node *lc, *rc;

    Node();
    Node(long count, const Node* lc, const Node* rc);
    Node* insert(long val, long l = 0, long r = MAX) const;
    long query(const Node* old, long k, long l = 0, long r = MAX) const;
};

Node Node::pool[POOL_SIZE];
Node* Node::ptr = Node::pool;
const Node Node::SINK = Node();

Node::Node()
    : count(0)
    , lc(&SINK)
    , rc(&SINK)
{
}

Node::Node(long count, const Node* lc, const Node* rc)
    : count(count)
    , lc(lc)
    , rc(rc)
{
}

Node* Node::insert(long val, long l, long r) const
{
    Node* node = new (ptr++) Node(count + 1, lc, rc);
    if (l == r) {
        return node;
    }
    long m = (l + r) / 2;
    if (val <= m) {
        node->lc = node->lc->insert(val, l, m);
    } else {
        node->rc = node->rc->insert(val, m + 1, r);
    }
    return node;
}

long Node::query(const Node* old, long k, long l, long r) const
{
    if (l == r) {
        return l;
    }
    long m = (l + r) / 2;
    long lc_count = lc->count - old->lc->count;
    if (k <= lc_count) {
        return lc->query(old->lc, k, l, m);
    } else {
        return rc->query(old->rc, k - lc_count, m + 1, r);
    }
}

int main()
{
    std::vector<long> primes;
    primesieve::generate_n_primes(N, &primes);

    std::vector<long> s(N + 1, 0);
    ulong pre = n_preinvert_limb(MOD);
    for (int k = 1; k <= N; ++k) {
        s[k] = n_powmod2_ui_preinv(primes[k - 1], k, MOD, pre);
    }
    std::vector<long>().swap(primes);

    std::vector<long> s2(N + 1, 0);
    for (int k = 1; k <= N; ++k) {
        s2[k] = s[k] + s[k / 10000 + 1];
    }
    std::vector<long>().swap(s);

    std::vector<const Node*> roots = { &Node::SINK };
    for (int k = 1; k <= N; ++k) {
        roots.push_back(roots.back()->insert(s2[k]));
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= N - K + 1; ++i) {
        // Assume K is even.
        sum += roots[(i + K - 1)]->query(roots[i - 1], K / 2);
        sum += roots[(i + K - 1)]->query(roots[i - 1], K / 2 + 1);
    }
    std::cout << std::fixed << std::setprecision(1) << sum / 2.0L << std::endl;

    return 0;
}
