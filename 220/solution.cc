#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#define MAX_K 50
#define STEPS 1'000'000'000'000

using namespace std::complex_literals;

typedef long long ll;
typedef std::complex<long double> complex;

class Movement {
public:
    ll steps;
    complex offset;
    complex direction;

    Movement();
    Movement(ll steps, complex offset, complex direction);
    friend Movement operator+(const Movement&, const Movement&);
    friend std::ostream& operator<<(std::ostream&, const Movement&);
};

Movement::Movement()
    : steps(0)
    , offset(0)
    , direction(1)
{
}

Movement::Movement(ll steps, complex offset, complex direction)
    : steps(steps)
    , offset(offset)
    , direction(direction)
{
}

Movement operator+(const Movement& m1, const Movement& m2)
{
    return Movement(m1.steps + m2.steps, m1.offset + m1.direction * m2.offset, m1.direction * m2.direction);
}

std::ostream& operator<<(std::ostream& os, const Movement& m)
{
    os << "(" << m.steps << ", ";
    ll oreal = std::llround(std::real(m.offset)), oimag = std::llround(std::imag(m.offset));
    if (oreal && oimag) {
        if (oimag > 0) {
            if (oimag == 1) {
                os << oreal << "+i";
            } else {
                os << oreal << "+" << oimag << "i";
            }
        } else {
            if (oimag == -1) {
                os << oreal << "-i";
            } else {
                os << oreal << "-" << -oimag << "i";
            }
        }
    } else if (oimag) {
        if (oimag == 1) {
            os << "i";
        } else if (oimag == -1) {
            os << "-i";
        } else {
            os << oimag << "i";
        }
    } else {
        os << oreal;
    }
    os << ", ";
    ll dreal = std::llround(std::real(m.direction)), dimag = std::llround(std::imag(m.direction));
    if (dreal == 1 && dimag == 0) {
        os << 1;
    } else if (dreal == 0 && dimag == 1) {
        os << "i";
    } else if (dreal == -1 && dimag == 0) {
        os << -1;
    } else if (dreal == 0 && dimag == -1) {
        os << "-i";
    } else {
        std::cerr << "fatal: invalid direction " << m.direction << std::endl;
        assert(0 && "invalid direction");
    }
    os << ")";
    return os;
}

const Movement L(0, 0, 1i), R(0, 0, -1i), F(1, 1, 1);
std::vector<Movement> ma, mb;

Movement calculate_movement(ll steps, int k, bool in_a)
{
    if (steps == 0) {
        return Movement();
    }
    // std::cout << steps << " " << k << " " << in_a << std::endl;
    k--;
    ll s = (1LL << k) - 1;
    assert(steps < 2 * s + 1);
    if (in_a) {
        if (steps == 2 * s) {
            return ma[k] + R + mb[k];
        } else if (steps > s) {
            return ma[k] + R + calculate_movement(steps - s, k, false);
        } else if (steps == s) {
            return ma[k];
        } else {
            return calculate_movement(steps, k, true);
        }
    } else {
        if (steps > s + 1) {
            return L + F + ma[k] + L + calculate_movement(steps - 1 - s, k, false);
        } else if (steps == s + 1) {
            return L + F + ma[k];
        } else if (steps > 1) {
            return L + F + calculate_movement(steps - 1, k, true);
        } else {
            return L + F;
        }
    }
}

complex calculate_dest(ll steps)
{
    int k = std::ceil(std::log2l(steps));
    Movement m;
    if (steps == 1LL << k) {
        m = ma[k];
    } else {
        m = calculate_movement(steps - 1, k, true);
    }
    return (Movement(1, 1i, 1i) + m).offset;
}

int main()
{
    ma.push_back({});
    mb.push_back({});
    for (int i = 1; i <= MAX_K; ++i) {
        ma.push_back(ma[i - 1] + R + mb[i - 1] + F + R);
        mb.push_back(L + F + ma[i - 1] + L + mb[i - 1]);
        // std::cout << i << "\t" << ma[i] << "\t" << mb[i] << std::endl;
    }
    complex dest = calculate_dest(STEPS);
    std::cout << std::llround(std::real(dest)) << "," << std::llround(std::imag(dest)) << std::endl;
    return 0;
}
