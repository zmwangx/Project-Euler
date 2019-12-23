#!/usr/bin/env python3

N = 123 #200_000


def main():
    c = [0, 0]
    right_subtree_height = 1
    total_cost = 0
    for n in range(2, N + 1):
        root = n - 2 ** right_subtree_height + 1
        right_subtree_cost = sum(n - 2 ** i + 1 for i in range(1, right_subtree_height))
        cost = root + max(c[root - 1], right_subtree_cost)
        # Alternatively, try to augment right subtree.
        alt_root = n - 2 ** (right_subtree_height + 1) + 1
        if alt_root > 0:
            alt_right_subtree_cost = sum(
                n - 2 ** i + 1 for i in range(1, right_subtree_height + 1)
            )
            # print(n, root, right_subtree_cost, alt_root, alt_right_subtree_cost)
            alt_cost = alt_root + max(c[alt_root - 1], alt_right_subtree_cost)
            if alt_cost < cost:
                cost = alt_cost
                right_subtree_height += 1
        c.append(cost)
        total_cost += cost
        print(n, cost, right_subtree_height)
    print(total_cost)


if __name__ == "__main__":
    main()
