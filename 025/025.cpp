//
//  main.cpp
//  Prbl025
//  Project Euler
//
//  Created by Zhiming Wang on 12/06/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  We use the formula
//
//  F_n = \frac{1}{\sqrt{5}} [((1 + \sqrt{5}) / 2)^n -
//                            ((1 - \sqrt{5}) / 2)^n]
//
//  with the problem. We can prove with abstract algebra that in order for $F_n
//  $ to be dividable by $5^k$, we need $5^k|n$; so it follows without much
//  effort (just check $n = 5^k, and it's way larger than $10^k$) that $10^k$
//  will never be present in the Fibonacci sequence. So it suffices that
//
//  \frac{1}{\sqrt{5}} ((1 + \sqrt{5}) / 2)^n > 10^{k-1}
//
//  in order for $F_n$ to be at least $k$ digits long. That is,
//
//  k > \frac{\ln (\sqrt{5} \dot 10^{k-1})}{\ln (\frac{1 + \sqrt{5}}{2})}.
//
//  And by solving this we are done with a $O(1)$ algorithm.
//  --------------------------------------------------------
//  Answer: 4782
//

#include <iostream>
#include <cmath>

const int NUMBER_OF_DIGITS = 1000;

int main() {
    double numerator   = std::log(std::sqrt(5)) +
                         (NUMBER_OF_DIGITS - 1) * std::log(10);
    double denominator = std::log((std::sqrt(5) + 1) / 2);
    
    std::cout << std::ceil(numerator / denominator) << std::endl;
    
    return 0;
}