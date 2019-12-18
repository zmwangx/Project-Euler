#include <iostream>

const long long N = 100'000'000;
const long long P = 1'008'691'207;

int main() {
    long long factorial_sum = 0;
    long long factorial = 1;
    for (long long i = 1; i < N; ++i) {
        factorial = (factorial * i) % P;
        factorial_sum = (factorial_sum + factorial) % P;
    }
    long long result = ((N - 3) * factorial_sum + (N - 1)) % P;
    std::cout << result << std::endl;
    return 0;
}
