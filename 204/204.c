/**
 * 204.c
 * Project Euler 204
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 * DFS. A lazy version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define arith_t unsigned long long

#define MAX ((arith_t)1000000000)

const arith_t _primes[25] = {
    2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97
};

const arith_t _numPowers[25] = {
    30, 19, 13, 11, 9,  9,  8,  8,  7,  7,
    7,  6,  6,  6,  6,  6,  6,  6,  5,  5,
    5,  5,  5,  5,  5
};

const arith_t _powers[25][30] = {
    {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
     32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
     16777216, 33554432, 67108864, 134217728, 268435456, 536870912},
    {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441,
     1594323, 4782969, 14348907, 43046721, 129140163, 387420489},
    {1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125, 9765625,
     48828125, 244140625},
    {1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607, 282475249},
    {1, 11, 121, 1331, 14641, 161051, 1771561, 19487171, 214358881},
    {1, 13, 169, 2197, 28561, 371293, 4826809, 62748517, 815730721},
    {1, 17, 289, 4913, 83521, 1419857, 24137569, 410338673},
    {1, 19, 361, 6859, 130321, 2476099, 47045881, 893871739},
    {1, 23, 529, 12167, 279841, 6436343, 148035889},
    {1, 29, 841, 24389, 707281, 20511149, 594823321},
    {1, 31, 961, 29791, 923521, 28629151, 887503681},
    {1, 37, 1369, 50653, 1874161, 69343957},
    {1, 41, 1681, 68921, 2825761, 115856201},
    {1, 43, 1849, 79507, 3418801, 147008443},
    {1, 47, 2209, 103823, 4879681, 229345007},
    {1, 53, 2809, 148877, 7890481, 418195493},
    {1, 59, 3481, 205379, 12117361, 714924299},
    {1, 61, 3721, 226981, 13845841, 844596301},
    {1, 67, 4489, 300763, 20151121},
    {1, 71, 5041, 357911, 25411681},
    {1, 73, 5329, 389017, 28398241},
    {1, 79, 6241, 493039, 38950081},
    {1, 83, 6889, 571787, 47458321},
    {1, 89, 7921, 704969, 62742241},
    {1, 97, 9409, 912673, 88529281}
};

static arith_t _counter = 0;

static void dfs(size_t primeId, arith_t prod);

int main(int argc, const char *argv[]) {
    dfs(0, 1);
    printf("%llu\n", _counter);
    return 0;
}

static void
dfs(size_t primeId, arith_t prod) {
    if (primeId == 25) {
        _counter++;
        return;
    }
    for (size_t i = 0; i < _numPowers[primeId]; i++) {
        arith_t power = _powers[primeId][i];
        if (prod * power > MAX) {
            break;
        }
        dfs(primeId + 1, prod * power);
    }
}
