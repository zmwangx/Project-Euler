#include <algorithm>
#include <array>
#include <iostream>

// #define N 107
// #define BEGIN_STEP 0
// #define END_STEP 1000
#define N 10'000'003
#define BEGIN_STEP 10'000'000
#define END_STEP 10'200'000

typedef long long ll;

std::array<int, 2 * END_STEP> t;
std::array<int, N> a;
std::array<ll, N> ps;

void calculate_t()
{
    t[2] = 1;
    for (int k = 3; k <= 2 * END_STEP - 1; ++k) {
        t[k] = (t[k - 1] + t[k - 2] + t[k - 3]) % N;
    }
}

int main()
{
    calculate_t();
    ll sum = 0;
    for (int i = 1; i <= BEGIN_STEP; ++i) {
        int index = t[2 * i - 2];
        int delta = 2 * t[2 * i - 1] - N + 1;
        a[index] += delta;
    }
    ll curr = 0;
    ll max = 0;
    for (int i = 0; i < N; ++i) {
        if (curr < 0) {
            curr = a[i];
        } else {
            curr += a[i];
        }
        ps[i] = curr;
        if (curr > max) {
            max = curr;
        }
    }
    // ll op_count = 0;
    for (int i = BEGIN_STEP + 1; i <= END_STEP; ++i) {
        if (i % 100 == 0) {
            std::cerr << "progress: " << i << " " << sum << std::endl;
        }
        int index = t[2 * i - 2];
        int delta = 2 * t[2 * i - 1] - N + 1;
        a[index] += delta;
        ps[index] += delta;
        curr = ps[index];
        if (delta > 0 && curr > max) {
            max = curr;
        }
        // op_count++;
        for (int j = index + 1; j < N; ++j) {
            // op_count++;
            if (curr < 0) {
                curr = a[j];
            } else {
                curr += a[j];
            }
            if (curr == ps[j]) {
                break;
            }
            ps[j] = curr;
            if (delta > 0 && curr > max) {
                max = curr;
            }
        }
        // for (int j = 0; j < N; ++j) {
        //     std::cout << a[j] << " ";
        // }
        // std::cout << std::endl;
        // for (int j = 0; j < N; ++j) {
        //     std::cout << ps[j] << " ";
        // }
        // std::cout << std::endl;
        if (delta < 0) {
            max = *std::max_element(ps.begin(), ps.end());
        }
        sum += max;
    }
    // std::cout << op_count << std::endl;
    std::cout << sum << std::endl;
    return 0;
}
