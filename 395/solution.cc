#include <complex>
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>

#define MAX_DEPTH 99

using namespace std::complex_literals;

typedef std::complex<double> point_t;
typedef std::pair<point_t, point_t> segment_t;

int main()
{
    double xmin = 0, xmax = 1, ymin = 0, ymax = 1;

#define UPDATE_MIN_MAX(p)                          \
    do {                                           \
        double x = std::real(p), y = std::imag(p); \
        if (x < xmin) {                            \
            xmin = x;                              \
        }                                          \
        if (x > xmax) {                            \
            xmax = x;                              \
        }                                          \
        if (y < ymin) {                            \
            ymin = y;                              \
        }                                          \
        if (y > ymax) {                            \
            ymax = y;                              \
        }                                          \
    } while (0)

    std::queue<std::tuple<int, segment_t, double>> q;
    q.push({ 1, { 1i, 1.0 + 1i }, 1 });
    int curr_depth = 1;
    while (!q.empty()) {
        const auto& [depth, base, length] = q.front();
        q.pop();
        if (depth > curr_depth) {
            std::cout << "depth " << curr_depth << ": "
                      << std::fixed << std::setprecision(10)
                      << (xmax - xmin) * (ymax - ymin) << " "
                      << "(xmin=" << xmin << ", "
                      << "xmax=" << xmax << ", "
                      << "ymin=" << ymin << ", "
                      << "ymax=" << ymax << ")"
                      << std::endl;
            curr_depth = depth;
        }
        if (depth > MAX_DEPTH) {
            continue;
        }
        const auto& [a, b] = base;
        const auto delta = b - a;

        // prospective limits
        point_t p1 = (3.15 + 3.35i) * delta + a;
        point_t p2 = (-3.25 + 3.35i) * delta + a;
        point_t p3 = (-3.25 - 1.12i) * delta + a;
        point_t p4 = (3.15 - 1.12i) * delta + a;
        double x1 = std::real(p1), y1 = std::imag(p1), x2 = std::real(p2), y2 = std::imag(p2),
               x3 = std::real(p3), y3 = std::imag(p3), x4 = std::real(p4), y4 = std::imag(p4);
        if (x1 >= xmin && x2 >= xmin && x3 >= xmin && x4 >= xmin
            && x1 <= xmax && x2 <= xmax && x3 <= xmax && x4 <= xmax
            && y1 >= ymin && y2 >= ymin && y3 >= ymin && y4 >= ymin
            && y1 <= ymax && y2 <= ymax && y3 <= ymax && y4 <= ymax) {
            continue;
        }

        // point_t c = (0.68 + 0.48i) * delta + a;
        point_t d = (-0.48 + 0.64i) * delta + a;
        point_t e = (0.16 + 1.12i) * delta + a;
        point_t f = (0.12 + 0.84i) * delta + b;
        point_t g = (0.48 + 0.36i) * delta + b;
        UPDATE_MIN_MAX(d);
        UPDATE_MIN_MAX(e);
        UPDATE_MIN_MAX(f);
        UPDATE_MIN_MAX(g);
        q.push({ depth + 1, { d, e }, 0.8 * length });
        q.push({ depth + 1, { f, g }, 0.6 * length });
    }
    return 0;
}
