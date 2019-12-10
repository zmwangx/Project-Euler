#include <iostream>

int main()
{
    const auto k = 6008819575ULL;
    const auto half = (k - 1) / 2;
    auto count = 0ULL;
    for (auto i = 2ULL; i < half; i += 3) {
        if (i % 5 != 0 && i % 11 != 0 && i % 17 != 0 && i % 23 != 0
            && i % 29 != 0 && i % 41 != 0 && i % 47 != 0) {
            count++;
        }
    }
    std::cout << count * 2 << std::endl;
    return 0;
}
