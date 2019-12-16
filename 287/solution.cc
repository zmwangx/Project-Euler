#include <iostream>
#include <string>

const int N = 24;
const long long x0 = 1LL << (N - 1), y0 = 1 << (N - 1);
const long long r2 = 1LL << (2 * N - 2);

inline bool black_test(long long x, long long y)
{
    auto dx = x - x0, dy = y - y0;
    return dx * dx + dy * dy <= r2;
}

inline int monotonous_test(int x1, int y1, int x2, int y2)
{
    if (x1 == x2) {
        return black_test(x1, y1) ? 0 : 1;
    }
    if (x2 - x1 > x0) {
        return -1;
    }
    // The points that need testing.
    int tx1, ty1, tx2, ty2;
    bool p1_is_black, p2_is_black;
    if ((x1 < x0 && y1 < y0) || (x1 >= x0 && y1 >= y0)) {
        // Bottom left or top right quadrant.
        tx1 = x1;
        ty1 = y1;
        tx2 = x2;
        ty2 = y2;
    } else {
        // Top left or bottom right quadrant.
        tx1 = x1;
        ty1 = y2;
        tx2 = x2;
        ty2 = y1;
    }
    p1_is_black = black_test(tx1, ty1);
    p2_is_black = black_test(tx2, ty2);
    if (p1_is_black && p2_is_black) {
        return 0;
    } else if (!p1_is_black && !p2_is_black) {
        return 1;
    } else {
        return -1;
    }
}

std::string minimal_sequence(int x1, int y1, int x2, int y2)
{
    int color;
    if ((color = monotonous_test(x1, y1, x2, y2)) != -1) {
        if (color == 0) {
            return "10";
        } else {
            return "11";
        }
    }
    std::string s("0");
    int xmid = (x1 + x2) / 2;
    int ymid = (y1 + y2) / 2;
    s += minimal_sequence(x1, ymid + 1, xmid, y2);
    s += minimal_sequence(xmid + 1, ymid + 1, x2, y2);
    s += minimal_sequence(x1, y1, xmid, ymid);
    s += minimal_sequence(xmid + 1, y1, x2, ymid);
    return s;
}

int main()
{
    auto s = minimal_sequence(0, 0, (1 << N) - 1, (1 << N) - 1);
    // std::cout << s << std::endl;
    std::cout << s.length() << std::endl;
    return 0;
}
