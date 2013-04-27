/**
 * 206.cpp
 * Project Euler 206
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 * Brute force.
 *
 * The last two digits must be 00. The rest is a 17-digit perfect square
 * starting with 1:
 * 1_2_3_4_5_6_7_8_9
 */

#include <iostream>
#include <string>

#define MIN 100000000
#define MAX 141421356
#define NUM_DIGITS 17

#define arith_t unsigned long long

int main(int argc, const char *argv[]) {
    for (arith_t n = MIN; n <= MAX; n++) {
        if (n % 10 != 3 && n % 10 != 7) {
            continue;
        }
        arith_t square = n * n;
        std::string s = std::to_string(square);
        if (s[0]  == '1' && s[2]  == '2' && s[4]  == '3' &&
            s[6]  == '4' && s[8]  == '5' && s[10] == '6' &&
            s[12] == '7' && s[14] == '8' && s[16] == '9') {
            std::cout << n << ' ' << square << std::endl;
            break;
        }
    }
    return 0;
}
