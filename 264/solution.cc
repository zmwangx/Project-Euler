#include <cmath>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#define MAX_PERIMETER 100'000
#define STEP_SIZE 5'000'000

inline int sqr(int x)
{
    return x * x;
}

inline double distance(int x1, int y1, int x2, int y2)
{
    return std::sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

inline double perimeter(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return distance(x1, y1, x2, y2) + distance(x2, y2, x3, y3) + distance(x3, y3, x1, y1);
}

int main()
{
    double perimeter_sum = 0;
    double max_radius = MAX_PERIMETER / 4.0;
    double max_r2 = max_radius * max_radius;
    std::cerr << "r^2 max: " << max_r2 << std::endl;
    int r2_lower_bound = 0;
    int r2_upper_bound = STEP_SIZE;
    while (r2_lower_bound <= max_r2) {
        std::cerr << "r^2: " << double(r2_lower_bound) << " to " << double(r2_upper_bound) << std::endl;
        std::unordered_map<int, std::vector<std::pair<int, int>>> circle_lattice_points;
        for (int x = -int(max_radius); x <= max_radius; ++x) {
            int y_bound = std::sqrt(max_r2 - x * x);
            for (int y = -y_bound; y <= y_bound; ++y) {
                int r2 = x * x + y * y;
                if (r2 > r2_lower_bound && r2 <= r2_upper_bound) {
                    circle_lattice_points[r2].push_back({ x, y });
                }
            }
        }
        for (auto& circle : circle_lattice_points) {
            auto r2 = circle.first;
            auto points = circle.second;
            auto num = points.size();
            for (int i = 0; i < num - 2; ++i) {
                auto x1 = points[i].first, y1 = points[i].second;
                for (int j = i + 1; j < num - 1; ++j) {
                    auto x2 = points[j].first, y2 = points[j].second;
                    auto x3 = 5 - x1 - x2, y3 = -y1 - y2;
                    // The third point must be pairwise greater than the second
                    // point, or we'll double count.
                    if (x3 < x2 || (x3 == x2 && y3 <= y2)) {
                        continue;
                    }
                    if (x3 * x3 + y3 * y3 == r2) {
                        double p = perimeter(x1, y1, x2, y2, x3, y3);
                        if (p <= MAX_PERIMETER) {
                            // std::cout << x1 << "," << y1 << "\t" << x2 << "," << y2 << "\t" << x3 << "," << y3 << std::endl;
                            perimeter_sum += p;
                        }
                    }
                }
            }
        }
        r2_lower_bound += STEP_SIZE;
        r2_upper_bound += STEP_SIZE;
    }
    std::cout << std::fixed << std::setprecision(4) << perimeter_sum << std::endl;
}
