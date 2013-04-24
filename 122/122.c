/**
 * 122.c
 * Project Euler 122
 * Created by Zhiming Wang on 04/24/2013.
 * --------------------------------------
 * IDDFS.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_EXPONENT 200
#define MAX_DEPTH 10

static int _trace[MAX_DEPTH + 1]; // for DFS
static size_t _currentDepth;
static size_t _recursionCount = 0;

static size_t _result[MAX_EXPONENT + 1] = {0};

static void iddfs(size_t depth);
              
int main(int argc, const char *argv[]) {
    // initialization
    _trace [0] = 1;
    _result[1] = 0;
    _trace [1] = 2;
    _result[2] = 1;
    for (size_t depth = 2; depth <= MAX_DEPTH; depth++) {
        // set current iterative deepening depth
        _currentDepth = depth;
        iddfs(1); // 1 and 2 fixed
        printf("depth: %zu; recursion count: %zu\n", depth, _recursionCount);
    }
    // testing print
    size_t numDetermined = 1; // we don't output 1 since it is so trivial
    for (int i = 2; i <= MAX_EXPONENT; i++) {
        if (_result[i] != 0) {
            printf("%3d: %zu\t", i, _result[i]);
            numDetermined++;
            if (numDetermined % 5 == 0) {
                putchar('\n');
            }
        }
    }
    if (numDetermined % 5 != 0) {
        putchar('\n');
    }
    printf("number of solved exponents: %zu\n", numDetermined);

    // NOTE: the section below is coined up out of hindsight!
    // 
    // after testing, only 191 cannot be covered in 10 steps, and it is
    // obvioulsy doable in 11 steps (the last step by 190 + 1)
    // so we manually assign 11 to _result[191] and compute the sum
    _result[191] = 11;
    size_t sum = 0;
    for (int i = 1; i <= MAX_EXPONENT; i++) {
        sum += _result[i];
    }
    printf("sum: %zu\n", sum);
    
    return 0;
}

static void
iddfs(size_t depth) {
    _recursionCount++;
    // iterative deepening
    if (depth >= _currentDepth) {
        return;
    }
    
    // try all combinations, but in the descending order
    // descending order has no advantage when searching entire trees, but will
    // be superior when search for certain values
    int last = _trace[depth];
    for (int j = depth; j >= 0; j--) {
        for (int i = j; i >= 0; i--) {
            int new = _trace[i] + _trace[j];
            if (new <= last) {
                // don't need to examine smaller i's
                // continue onto next j
                break;
            }
            if (new > MAX_EXPONENT) {
                // uninteresting
                continue;
            }
            
            // update result
            if (_result[new] == 0) {
                _result[new] = depth + 1;
            }
            // recursive call
            _trace[depth + 1] = new;
            iddfs(depth + 1);
        }
    }
}
