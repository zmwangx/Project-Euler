#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_map>
#include <vector>

typedef std::vector<long> NumberVec;
typedef std::unordered_map<long, std::unordered_map<long, long>> SumMap;

const long N = 100;

// If element_count is 0, calculates sums for all element counts; otherwise,
// calculate sums only for the specific element count.
//
// Assumes the range is sorted in ascending order.
SumMap calculate_sums(NumberVec::iterator first, NumberVec::iterator last, long element_count = 0)
{
    SumMap result;
    result[0][0] = 1;
    size_t n = last - first;
    assert(n > 0);
    if (n == 1) {
        result[1][*first] = 1;
        return result;
    }

    auto middle = first + n / 2;
    long n1 = middle - first;
    auto result1 = calculate_sums(first, middle);
    long n2 = last - middle;
    auto result2 = calculate_sums(middle, last);

    // Straightforward unoptimized code.
    //
    // #define CALC_SUMS_FOR_ELEM_COUNT(elem_count)                                                   \
    //     do {                                                                                       \
    //         if (n >= N / 2) {                                                                      \
    //             std::cout << n << " " << elem_count << std::endl;                                  \
    //         }                                                                                      \
    //         long minsum = std::accumulate(first, first + elem_count, 0);                           \
    //         long maxsum = std::accumulate(last - elem_count, last, 0);                             \
    //         std::vector<long> c(maxsum + 1, 0);                                                    \
    //         long min_ec1 = std::max(0L, elem_count - n2);                                          \
    //         long max_ec1 = std::min(elem_count, n1);                                               \
    //         for (long ec1 = min_ec1; ec1 <= max_ec1; ++ec1) {                                      \
    //             long ec2 = elem_count - ec1;                                                       \
    //             if (n >= N) {                                                                      \
    //                 std::cout << n << " " << elem_count << "=" << ec1 << "+" << ec2 << " "         \
    //                           << result1[ec1].size() << "*" << result2[ec2].size() << std::endl;   \
    //             }                                                                                  \
    //             for (auto& p1 : result1[ec1]) {                                                    \
    //                 for (auto& p2 : result2[ec2]) {                                                \
    //                     auto s1 = p1.first, count1 = p1.second, s2 = p2.first, count2 = p2.second; \
    //                     c[s1 + s2] += count1 * count2;                                             \
    //                 }                                                                              \
    //             }                                                                                  \
    //         }                                                                                      \
    //         for (long sum = minsum; sum <= maxsum; ++sum) {                                        \
    //             if (c[sum] >= 2) {                                                                 \
    //                 result[elem_count][sum] = 2;                                                   \
    //             } else if (c[sum] == 1) {                                                          \
    //                 result[elem_count][sum] = 1;                                                   \
    //             }                                                                                  \
    //         }                                                                                      \
    //     } while (0)

#define CALC_SUMS_FOR_ELEM_COUNT(elem_count)                                                                                   \
    do {                                                                                                                       \
        if (n >= N / 2) {                                                                                                      \
            std::cout << n << " " << elem_count << std::endl;                                                                  \
        }                                                                                                                      \
        long minsum = std::accumulate(first, first + elem_count, 0);                                                           \
        long maxsum = std::accumulate(last - elem_count, last, 0);                                                             \
        std::vector<long> c(maxsum + 1, 0);                                                                                    \
        long min_ec1 = std::max(0L, elem_count - n2);                                                                          \
        long max_ec1 = std::min(elem_count, n1);                                                                               \
        for (long ec1 = min_ec1; ec1 <= max_ec1; ++ec1) {                                                                      \
            long ec2 = elem_count - ec1;                                                                                       \
            size_t size1 = result1[ec1].size(), size2 = result2[ec2].size();                                                   \
            if (n >= N) {                                                                                                      \
                std::cout << n << " " << elem_count << "=" << ec1 << "+" << ec2 << " "                                         \
                          << size1 << "*" << size2 << std::endl;                                                               \
            }                                                                                                                  \
            auto rs1 = &(result1[ec1]), rs2 = &(result2[ec2]);                                                                 \
            if (size1 > size2) {                                                                                               \
                std::swap(rs1, rs2);                                                                                           \
            }                                                                                                                  \
            long sub_minsum = std::accumulate(first, first + ec1, 0) + std::accumulate(first + n / 2, first + n / 2 + ec2, 0); \
            long sub_maxsum = std::accumulate(first + n / 2 - ec1, first + n / 2, 0) + std::accumulate(last - ec2, last, 0);   \
            if (size1 * size2 > 10000 * (sub_maxsum - sub_minsum)) {                                                           \
                for (long sum = sub_minsum; sum <= sub_maxsum; ++sum) {                                                        \
                    if (c[sum] >= 2) {                                                                                         \
                        continue;                                                                                              \
                    }                                                                                                          \
                    for (auto& p1 : *rs1) {                                                                                    \
                        auto s1 = p1.first, count1 = p1.second;                                                                \
                        auto p2 = rs2->find(sum - s1);                                                                         \
                        if (p2 != rs2->end()) {                                                                                \
                            auto count2 = p2->second;                                                                          \
                            c[sum] += count1 * count2;                                                                         \
                            if (c[sum] >= 2) {                                                                                 \
                                break;                                                                                         \
                            }                                                                                                  \
                        }                                                                                                      \
                    }                                                                                                          \
                }                                                                                                              \
            } else {                                                                                                           \
                for (auto& p1 : *rs1) {                                                                                        \
                    for (auto& p2 : *rs2) {                                                                                    \
                        auto s1 = p1.first, count1 = p1.second, s2 = p2.first, count2 = p2.second;                             \
                        c[s1 + s2] += count1 * count2;                                                                         \
                    }                                                                                                          \
                }                                                                                                              \
            }                                                                                                                  \
        }                                                                                                                      \
        for (long sum = minsum; sum <= maxsum; ++sum) {                                                                        \
            if (c[sum] >= 2) {                                                                                                 \
                result[elem_count][sum] = 2;                                                                                   \
            } else if (c[sum] == 1) {                                                                                          \
                result[elem_count][sum] = 1;                                                                                   \
            }                                                                                                                  \
        }                                                                                                                      \
    } while (0)

    if (element_count == 0) {
        // Calculate sums for all element counts.
        for (long elem_count = 1; elem_count <= n / 2; ++elem_count) {
            CALC_SUMS_FOR_ELEM_COUNT(elem_count);
        }
    } else {
        // Only calculate sums for element_count (if <= n/2) or n - element_count.
        long elem_count = element_count;
        if (element_count > n / 2) {
            elem_count = n - element_count;
        }
        CALC_SUMS_FOR_ELEM_COUNT(elem_count);
    }

    long total = std::accumulate(first, last, 0);

#define HANDLE_REFLECTION(elem_count)              \
    do {                                           \
        auto reflection = result[n - elem_count];  \
        for (auto& p : reflection) {               \
            auto s = p.first, count = p.second;    \
            result[elem_count][total - s] = count; \
        }                                          \
    } while (0)

    if (element_count == 0) {
        for (long elem_count = n / 2 + 1; elem_count <= n; ++elem_count) {
            HANDLE_REFLECTION(elem_count);
        }
    } else if (element_count > n / 2) {
        HANDLE_REFLECTION(element_count);
    }
    return result;
}

int main()
{
    std::vector<long> numbers;
    for (long i = 1; i <= N; ++i) {
        numbers.push_back(i * i);
    }
    auto result = calculate_sums(numbers.begin(), numbers.end(), N / 2);
    std::map<long, long> ordered(result[N / 2].begin(), result[N / 2].end());
    long sum = 0;
    for (auto& p : ordered) {
        if (p.second == 1) {
            sum += p.first;
        }
        // std::cout << p.first << ": " << p.second << std::endl;
    }
    std::cout << sum << std::endl;
    return 0;
}
