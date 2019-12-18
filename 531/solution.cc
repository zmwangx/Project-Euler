#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

#include <fmpzxx.h>

#include <fmpz_factorxx.h>

int main()
{
    flint::fmpzxx one(1);
    std::vector<std::pair<flint::fmpzxx, flint::fmpzxx>> n_phi;
    for (unsigned n = 1000000; n < 1005000; ++n) {
        flint::fmpzxx phi(n);
        // fmpzxx b(1000033 * 2);
        // auto res = gcdinv(a, b);
        // std::cout << res.get<0>() << " " << res.get<1>() << std::endl;
        auto factorization = flint::factor(n);
        for (size_t i = 0; i < factorization.size(); ++i) {
            auto p = factorization.p(i);
            phi *= (p - one);
            phi /= p;
        }
        n_phi.push_back(std::make_pair(flint::fmpzxx(n), phi));
    }

    flint::fmpzxx sum(0);
    for (size_t i = 0; i < n_phi.size(); ++i) {
        auto n = n_phi[i].first, phi_n = n_phi[i].second;
        for (size_t j = i + 1; j < n_phi.size(); ++j) {
            auto m = n_phi[j].first, phi_m = n_phi[j].second;
            auto gcdinv = flint::gcdinv(n, m);
            auto g = gcdinv.get<0>();
            if (phi_n % g != phi_m % g) {
                continue;
            }
            auto n_times_ninv = gcdinv.get<1>() * n;
            auto m_times_minv = g - n_times_ninv;
            auto mod = m * n / g;
            sum += (phi_m * n_times_ninv + phi_n * m_times_minv) / g % mod;
        }
    }
    std::cout << sum << std::endl;
}
