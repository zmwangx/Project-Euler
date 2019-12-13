#include <bitset>
#include <deque>
#include <iostream>

const int N = 5;
const int POW_N = 1 << N;

typedef unsigned placement_mask_t;
typedef unsigned sequence_t;
typedef unsigned sequence_mask_t;
typedef unsigned position_t;

int main()
{
    // 000001...1
    placement_mask_t fixed_placements = 1 | (1 << (POW_N - N - 1));
    // 00000, 00001 and 10000 are automatically consumed.
    sequence_mask_t fixed_seqmask = 3 | (1 << (POW_N / 2));
    std::deque<std::tuple<placement_mask_t, position_t, sequence_mask_t>> q;
    q.push_back(std::make_tuple(fixed_placements, 1, fixed_seqmask));
    position_t maxpos = POW_N - N - 2;
    unsigned long long sum = 0;
    while (!q.empty()) {
        auto tup = q.front();
        q.pop_front();
        placement_mask_t placements = std::get<0>(tup);
        position_t pos = std::get<1>(tup);
        sequence_mask_t seqmask = std::get<2>(tup);
        if (pos > maxpos) {
            bool found_conflict = false;
            while (pos < POW_N - 2) {
                sequence_t seq = (placements & ((1 << (pos + 1)) - 1)) >> (pos + 1 - N);
                if (seqmask >> seq & 1) {
                    found_conflict = true;
                    break;
                }
                pos++;
            }
            if (!found_conflict) {
                sum += placements;
                // std::cout << std::bitset<POW_N>(placements) << std::endl;
            }
            continue;
        }
        for (int bit = 0; bit < 2; ++bit) {
            if (bit) {
                // We iterate through 0 first then 1, so we don't need to clear
                // the bit once set.
                placements |= 1 << pos;
            }
            sequence_t seq;
            if (pos >= N - 1) {
                seq = (placements & ((1 << (pos + 1)) - 1)) >> (pos + 1 - N);
            } else {
                // The last (N-1-pos) bits are from the front of placements,
                // which are all 0.
                seq = (placements & ((1 << (pos + 1)) - 1)) << (N - 1 - pos);
            }
            if (!(seqmask >> seq & 1)) {
                q.push_back(std::make_tuple(placements, pos + 1, seqmask | (1 << seq)));
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
