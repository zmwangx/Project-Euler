#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

typedef std::tuple<int, int, int> point_t;

inline int sqr(int x)
{
    return x * x;
}

inline bool is_square(int x)
{
    return x >= 0 && sqr(int(std::sqrt(x))) == x;
}

std::vector<point_t> generate_points(int r)
{
    std::vector<point_t> points;
    for (int x = -r; x <= r; ++x) {
        for (int y = -r; y <= r; ++y) {
            int z2 = sqr(r) - sqr(x) - sqr(y);
            if (is_square(z2)) {
                int absz = std::sqrt(z2);
                points.push_back({ x, y, -absz });
                if (absz > 0) {
                    points.push_back({ x, y, absz });
                }
            }
        }
    }
    return points;
}

inline double angular_distance(int r, const point_t& p1, const point_t& p2)
{
    const auto& [x1, y1, z1] = p1;
    const auto& [x2, y2, z2] = p2;
    return std::acos(double(x1 * x2 + y1 * y2 + z1 * z2) / sqr(r));
}

inline double area(int r, double a, double b, double c)
{
    double s = (a + b + c) / 2;
    // clang-format off
    double E = 4 * std::atan(std::sqrt(
        std::tan(s / 2) * std::tan((s - a) / 2) * std::tan((s - b) / 2) * std::tan((s - c) / 2)
    ));
    // clang-format on
    return E * sqr(r);
}

inline bool on_same_great_circle(const point_t& p1, const point_t& p2, const point_t& p3)
{
    // Check whether p1, p2, p3 and origin (0, 0, 0) are coplaner by checking
    // whether the determinant
    //
    //   | x1 y1 z1 |
    //   | x2 y2 z2 |
    //   | x3 y3 z3 |
    //
    // is zero (when zero, the three vectors from origin don't span the whole
    // space, hence coplaner).
    const auto& [x1, y1, z1] = p1;
    const auto& [x2, y2, z2] = p2;
    const auto& [x3, y3, z3] = p3;
    return x1 * y2 * z3 + y1 * z2 * x3 + z1 * x2 * y3 - x3 * y2 * z1 - y3 * z2 * x1 - z3 * x2 * y1 == 0;
}

double min_area(int r)
{
    auto points = generate_points(r);
    auto count = points.size();
    std::vector<std::vector<double>> distances(count, std::vector<double>(count));
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            distances[i][j] = angular_distance(r, points[i], points[j]);
        }
    }
    double min = 4 * M_PI * sqr(r);
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            for (int k = 0; k < count; ++k) {
                if (on_same_great_circle(points[i], points[j], points[k])) {
                    continue;
                }
                double a = area(r, distances[i][j], distances[j][k], distances[k][i]);
                if (a < min) {
                    min = a;
                }
            }
        }
    }
    return min;
}

int main()
{
    double sum = 0;
    for (int r = 1; r <= 50; ++r) {
        double area = min_area(r);
        sum += area;
        std::cout << r << "\t" << std::fixed << std::setprecision(6) << area << std::endl;
    }
    std::cout << std::fixed << std::setprecision(6) << sum << std::endl;
    return 0;
}
