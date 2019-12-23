#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#define N 200'000

int greedy_subtree(int upper, int size)
{
    if (size == 0) {
        return 0;
    }
    int height = int(std::log2(size)) + 1;
    if (size == (1 << height) - 1) {
        return (height - 1) * (upper + 1) - size + 1;
    }
    int left_subtree_size, right_subtree_size;
    if (size & (1 << (height - 2))) {
        // size > (2^(h-1) - 1) + (2^(h-2) - 1) + 1, so the right subtree must
        // be of height h-1. We fill the left subtree in order to minimize the
        // right subtree.
        left_subtree_size = (1 << (height - 1)) - 1;
        right_subtree_size = size - 1 - left_subtree_size;
    } else {
        // size <= (2^(h-1) - 1) + (2^(h-2) - 1) + 1, so the right subtree
        // should be of height h-2. We fill the right subtree in order to
        // minimize the left subtree.
        right_subtree_size = (1 << (height - 2)) - 1;
        left_subtree_size = size - 1 - right_subtree_size;
    }
    int root = upper - right_subtree_size;
    int left_subtree_cost = greedy_subtree(root - 1, left_subtree_size);
    int right_subtree_cost = greedy_subtree(upper, right_subtree_size);
    return root + std::max(left_subtree_cost, right_subtree_cost);
}

int main()
{
    std::vector<int> c(N, 0);
    int right_subtree_height = 1;
    int last_right_subtree_size = 1;
    long long total = 0;
    for (int n = 2; n <= N; ++n) {
        if (n % 5000 == 0) {
            std::cerr << "progress: " << n << std::endl;
        }
        int right_subtree_size = last_right_subtree_size;
        int max_right_subtree_size = std::min((2 << right_subtree_height) - 1, n / 2);
        int min_cost = n + c[n - 1];
        int minimizer_right_subtree_size = 0;
        while (right_subtree_size <= max_right_subtree_size) {
            int root = n - right_subtree_size;
            int cost = root + std::max(c[root - 1], greedy_subtree(n, right_subtree_size));
            if (cost < min_cost) {
                min_cost = cost;
                minimizer_right_subtree_size = right_subtree_size;
            }
            right_subtree_size++;
        }
        c[n] = min_cost;
        total += min_cost;
        last_right_subtree_size = minimizer_right_subtree_size;
        if (minimizer_right_subtree_size >= 1 << right_subtree_height) {
            right_subtree_height++;
        }
    }
    std::cout << total << std::endl;
    return 0;
}
