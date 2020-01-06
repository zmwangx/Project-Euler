#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <utility>

#define N 70

#define MASK 0xFULL
#define CYCLES_SHIFT 40
#define LAST_EDGE_SHIFT 44

#define LAST_EDGE(state) (((state) >> LAST_EDGE_SHIFT) & MASK)
#define CYCLES(state) (((state) >> CYCLES_SHIFT) & MASK)
#define EDGE_COUNT(state, edge) (((state) >> (4 * (edge))) & MASK)

#define INCREMENT_EDGE_COUNT(state, edge) ((state) + (1ULL << (4 * (edge))))
#define SUBTRACT_COMMON_LOWER_EDGE_COUNTS(state, count) ((state) - (0x11111ULL * (count)))
#define SUBTRACT_COMMON_UPPER_EDGE_COUNTS(state, count) ((state) - (0x1111100000ULL * (count)))
#define ADD_CYCLE_COUNT(state, count) ((state) + ((mask_t)(count) << CYCLES_SHIFT))
#define NORMALIZE_CYCLES(state, lower_count, upper_count)                                                      \
    ADD_CYCLE_COUNT(                                                                                           \
        SUBTRACT_COMMON_UPPER_EDGE_COUNTS(SUBTRACT_COMMON_LOWER_EDGE_COUNTS(state, lower_count), upper_count), \
        lower_count + upper_count)
#define CLEAR_LAST_EDGE(state) ((state) & (~(MASK << LAST_EDGE_SHIFT)))
#define SET_LAST_EDGE(state, edge) (CLEAR_LAST_EDGE(state) | ((mask_t)(edge) << LAST_EDGE_SHIFT))
#define NEW_STATE(state, edge) SET_LAST_EDGE(INCREMENT_EDGE_COUNT(state, edge), edge)

typedef uint64_t mask_t;
typedef uint64_t ulong;

int main()
{
    std::map<mask_t, ulong> count, prev_count;
    // Only consider paths starting with edge 0. There are exactly as many paths starting with edge 6.
    count[1] = 0x1;
    for (int n = 2; n <= N; ++n) {
        count.swap(prev_count);
        std::map<mask_t, ulong>().swap(count);
        for (const auto [state, c] : prev_count) {
            mask_t last_edge = (state >> LAST_EDGE_SHIFT) & MASK;
            mask_t edge1 = last_edge < 5 ? (last_edge == 4 ? 0 : last_edge + 1) : (last_edge == 9 ? 5 : last_edge + 1);
            mask_t edge2 = 9 - last_edge;
            count[NEW_STATE(state, edge1)] += c;
            count[NEW_STATE(state, edge2)] += c;
        }
        for (auto it = count.begin(); it != count.end();) {
            const auto [s, c] = *it;
            int cycles = CYCLES(s);
            int c0 = EDGE_COUNT(s, 0);
            int c1 = EDGE_COUNT(s, 1);
            int c2 = EDGE_COUNT(s, 2);
            int c3 = EDGE_COUNT(s, 3);
            int c4 = EDGE_COUNT(s, 4);
            int c5 = EDGE_COUNT(s, 5);
            int c6 = EDGE_COUNT(s, 6);
            int c7 = EDGE_COUNT(s, 7);
            int c8 = EDGE_COUNT(s, 8);
            int c9 = EDGE_COUNT(s, 9);
            if (cycles + std::max({ c0, c1, c2, c3, c4 }) + std::max({ c5, c6, c7, c8, c9 }) > N / 5) {
                // Cannot possibly balance out within the given number of steps.
                it = count.erase(it);
                continue;
            }
            int lower_common = std::min({ c0, c1, c2, c3, c4 });
            int upper_common = std::min({ c5, c6, c7, c8, c9 });
            if (lower_common == 0 && upper_common == 0) {
                ++it;
                continue;
            }
            count[NORMALIZE_CYCLES(s, lower_common, upper_common)] += c;
            it = count.erase(it);
        }
    }
    assert(count.size() == 2);
    ulong total_count = 2 * (count.begin()->second + count.rbegin()->second);
    std::cout << total_count << std::endl;
    return 0;
}
