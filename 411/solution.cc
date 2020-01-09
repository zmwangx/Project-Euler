#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

#define USE_VECTOR_FOR_STATIONS 1

int longest_nondecreasing_subsequence(const std::vector<int>& s)
{
    std::vector<int> m;
    int l = 0;
    for (int i = 0; i < s.size(); ++i) {
        int curr = s[i];
        int lo = 0, hi = l - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (s[m[mid]] <= curr) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (lo >= l) {
            m.push_back(i);
            l++;
        } else {
            m[lo] = i;
        }
    }
    return l;
}

int calc_S(int n)
{
    if (n == 1) {
        return 1;
    }
#if USE_VECTOR_FOR_STATIONS
    std::vector<std::pair<int, int>> stations;
    for (int r2 = 1, r3 = 1, i = 0; i <= 2 * n; (r2 *= 2) %= n, (r3 *= 3) %= n, ++i) {
        stations.push_back({ r2, r3 });
    }
    std::sort(stations.begin(), stations.end());
    std::vector<int> ycoords;
    std::pair<int, int> last = { -1, -1 };
    for (const auto& coord : stations) {
        if (coord == last) {
            continue;
        }
        ycoords.push_back(coord.second);
        last = coord;
    }
    std::vector<std::pair<int, int>>().swap(stations);
#else
    std::map<int, std::set<int>> stations;
    for (int r2 = 1, r3 = 1, i = 0; i <= 2 * n; (r2 *= 2) %= n, (r3 *= 3) %= n, ++i) {
        stations[r2].insert(r3);
    }
    std::vector<int> ycoords;
    for (const auto& [r2, r3s] : stations) {
        for (const auto r3 : r3s) {
            ycoords.push_back(r3);
            std::cout << "(" << r2 << "," << r3 << ") " << std::endl;
        }
    }
    std::map<int, std::set<int>>().swap(stations);
#endif
    return longest_nondecreasing_subsequence(ycoords);
}

int main()
{
    long long sum = 0;
    for (int k = 1; k <= 30; ++k) {
        int k5 = k * k * k * k * k;
        int S = calc_S(k5);
        std::cout << k << "\t" << k5 << "\t" << S << std::endl;
        sum += S;
    }
    std::cout << sum << std::endl;
    return 0;
}
