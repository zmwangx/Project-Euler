#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::uint256_t int_type;

const int_type N = 1'000'000'000'000'000ULL;
const int_type MODULUS = 1'000'000'000ULL;

inline int_type square_sum(int_type n)
{
    return n * (n + 1) * (2 * n + 1) / 6;
}

int_type SIGMA2(int_type n)
{
    const int_type root = sqrt(n);
    int_type sum = 0;
    for (int_type i = 1; i <= root; ++i) {
        sum = (sum + (n / i) * i * i) % MODULUS;
    }
    int_type ss_last = square_sum(root);
    for (int_type i = root; i > 0; --i) {
        int_type ss = square_sum(n / i);
        sum = (sum + i * (ss - ss_last)) % MODULUS;
        ss_last = ss;
    }
    return sum;
}

int main()
{
    std::cout << SIGMA2(N) << std::endl;
    return 0;
}
