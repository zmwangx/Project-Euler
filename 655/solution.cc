#include <iostream>
#include <vector>

const int MAX_LENGTH = 32;
const long P = 10000019;

int main()
{
    std::vector<long> pow10;
    for (long i = 0, s = 1; i <= ((MAX_LENGTH + 1) / 2 + 1) / 2; ++i, s *= 10) {
        pow10.push_back(s);
    }
    std::vector<long> pow10m;
    for (long i = 0, s = 1; i < MAX_LENGTH; ++i, (s *= 10) %= P) {
        pow10m.push_back(s);
    }
    long long total_count = 0;
    for (int length = 1; length <= MAX_LENGTH; ++length) {
        int half_length = (length + 1) / 2;
        int left_quarter_length = (half_length + 1) / 2;
        int right_quarter_length = half_length - left_quarter_length;
        std::vector<long> multipliers; // = { 10001, 1010, 100 };
        for (int i = 0; i < half_length; ++i) {
            int j = length - 1 - i;
            if (i != j) {
                multipliers.push_back(pow10m[i] + pow10m[j]);
            } else {
                multipliers.push_back(pow10m[i]);
            }
        }
        std::vector<long> r1_count(P, 0);
        std::vector<long> r2_count(P, 0);
        for (long n = pow10[left_quarter_length - 1]; n < pow10[left_quarter_length]; ++n) {
            long m = n;
            long i = left_quarter_length - 1;
            long r1 = 0;
            while (m > 0) {
                r1 += (m % 10) * multipliers[i];
                m /= 10;
                i--;
            }
            r1 %= P;
            r1_count[r1]++;
        }
        if (right_quarter_length > 0) {
            for (long n = 0; n < pow10[right_quarter_length]; ++n) {
                long m = n;
                long i = half_length - 1;
                long r2 = 0;
                while (m > 0) {
                    r2 += (m % 10) * multipliers[i];
                    m /= 10;
                    i--;
                }
                r2 %= P;
                r2_count[r2]++;
            }
        }
        total_count += r1_count[0] * r2_count[0];
        for (long r1 = 1; r1 < P; ++r1) {
            total_count += r1_count[r1] * r2_count[P - r1];
        }
    }
    std::cout << total_count << std::endl;
    return 0;
}
