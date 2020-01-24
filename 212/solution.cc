#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

typedef long long ll;

const int N = 50000;

int main()
{
    std::vector<int> S(6 * N + 1, 0);
    for (int k = 1; k <= 55; ++k) {
        S[k] = (100003LL - 200003LL * k + 300007LL * k * k * k) % 1000000LL;
    }
    for (int k = 56; k <= 6 * N; ++k) {
        S[k] = (S[k - 24] + S[k - 55]) % 1000000LL;
    }
    std::vector<int> x0, y0, z0, x1, y1, z1;
    for (int i = 1; i <= N; ++i) {
        int x = S[6 * i - 5] % 10000;
        int y = S[6 * i - 4] % 10000;
        int z = S[6 * i - 3] % 10000;
        int dx = 1 + S[6 * i - 2] % 399;
        int dy = 1 + S[6 * i - 1] % 399;
        int dz = 1 + S[6 * i] % 399;
        x0.push_back(x);
        y0.push_back(y);
        z0.push_back(z);
        x1.push_back(x + dx);
        y1.push_back(y + dy);
        z1.push_back(z + dz);
    }
    int xmax = 10000 + 399;
    std::vector<std::vector<int>> xsections(xmax);
    for (int i = 0; i < N; ++i) {
        for (int x = x0[i]; x < x1[i]; ++x) {
            xsections[x].push_back(i);
        }
    }
    ll volume = 0;
    for (int x = 0; x < xmax; ++x) {
        std::vector<int> ysection_coords;
        for (auto cuboid_index : xsections[x]) {
            ysection_coords.push_back(y0[cuboid_index]);
            ysection_coords.push_back(y1[cuboid_index]);
        }
        std::sort(ysection_coords.begin(), ysection_coords.end());
        for (unsigned i = 0; i + 1 < ysection_coords.size(); ++i) {
            int y = ysection_coords[i];
            int y_next = ysection_coords[i + 1];
            // Store whether the coordinate is a starting coordinate (z0) or
            // ending coordinate (z1) alongside each z-coordinate.
            std::vector<std::pair<int, int>> zsection_coords;
            for (auto cuboid_index : xsections[x]) {
                if (y >= y0[cuboid_index] && y < y1[cuboid_index]) {
                    // Cuboid with the given index covers [y, y_next).
                    zsection_coords.push_back({ z0[cuboid_index], 1 });
                    zsection_coords.push_back({ z1[cuboid_index], -1 });
                }
            }
            std::sort(zsection_coords.begin(), zsection_coords.end());
            int z_coverage = 0;
            int last = 0;
            int multiplicity = 0;
            for (auto [z, delta] : zsection_coords) {
                if (multiplicity) {
                    z_coverage += z - last;
                }
                multiplicity += delta;
                last = z;
            }
            volume += (y_next - y) * z_coverage;
        }
    }
    std::cout << volume << std::endl;
    return 0;
}
