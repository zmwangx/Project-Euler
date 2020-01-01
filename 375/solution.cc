#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

const long N = 2'000'000'000;

int main()
{
    // std::unordered_map<long, long> valpos;
    long r = 290797;
    std::vector<long> s = { r };
    long period = 0;
    for (long n = 1; n <= N; ++n) {
        r = r * r % 50'515'093;
        if (n > 1 && r == s[1]) {
            period = n - 1;
            break;
        }
        s.push_back(r);
    }

    // Study at most three periods, then use results for the middle priod for
    // all other periods.
    for (long len = period; len + period <= N && len + period <= 3 * period; len += period) {
        s.insert(s.end(), s.begin() + 1, s.begin() + period + 1);
    }
    s.insert(s.end(), s.begin() + 1, s.begin() + N % period + 1);
    long repeats = std::max(0L, N - 3 * period) / period;
    long m = N - repeats * period;

    std::vector<long> left(m + 1, 0), right(m + 1, 0);
    std::stack<std::pair<long, long>> stack;
    for (long n = 1; n <= m; ++n) {
        long curr = s[n];
        long length = 1;
        while (!stack.empty()) {
            auto [value, sub_length] = stack.top();
            if (value <= curr) {
                break;
            }
            stack.pop();
            length += sub_length;
        }
        stack.push({ curr, length });
        left[n] = length;
    }
    std::stack<std::pair<long, long>>().swap(stack);
    for (long n = m; n >= 1; --n) {
        long curr = s[n];
        long length = 1;
        while (!stack.empty()) {
            auto [value, sub_length] = stack.top();
            if (value < curr) {
                break;
            }
            stack.pop();
            length += sub_length;
        }
        stack.push({ curr, length });
        right[n] = length;
    }

    std::vector<long> minpositions;
    for (long n = 1; n <= period; ++n) {
        if (right[n] == m - n + 1) {
            minpositions.push_back(n);
        }
    }
    assert(minpositions.size() == 1);
    long minpos = minpositions[0];
    unsigned long long sum = 0;
    for (long n = 1; n <= m; ++n) {
        if ((n - minpos) % period != 0) {
            sum += s[n] * left[n] * right[n];
        }
    }
    if (repeats) {
        for (long n = period + 1; n <= period * 2; ++n) {
            if (n != period + minpos) {
                sum += repeats * s[n] * left[n] * right[n];
            }
        }
    }
    for (long pos = minpos; pos <= N; pos += period) {
        sum += s[minpos] * (pos - std::max(pos - period, 0L)) * (N - pos + 1);
    }
    std::cout << sum << std::endl;

    return 0;
}
