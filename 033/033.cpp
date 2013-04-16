//
//  main.cpp
//  Prbl033
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Note that $\frac{10a + b}{10c + b} = \frac{a}{c}$ is not possible as long as
//  $b \neq 0$ and $a \neq c$, so we only need to search the possibilities of
//
//  \frac{10a + b}{10b + c} = \frac{a}{c}.
//  --------------------------------------
//  Answer:
//

// Test the functionality of <code>Fraction</code> class.
// #define __PRBL032_IS_IN_DEBUGGING_PHASE_01__ 1

#include <iostream>
#include <vector>

static int gcd(int x, int y);

class Fraction{
    
    int numerator;
    int denominator;
    
public:
    
    Fraction(int numerator, int denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
    }
    
    Fraction& operator=(const Fraction& other) {
        this->numerator     = other.numerator;
        this->denominator   = other.denominator;
        return *this;
    }
    
    Fraction simplify() const {
        int numDenomGcd = gcd(numerator, denominator);
        Fraction simplified(numerator / numDenomGcd, denominator / numDenomGcd);
        return simplified;
    }
    
    friend Fraction operator*(const Fraction& fraction1,
                              const Fraction& fraction2) {
        Fraction product(fraction1.numerator * fraction2.numerator,
                         fraction1.denominator * fraction2.denominator);
        return product.simplify();
    }
    
    friend bool operator==(const Fraction& fraction1,
                           const Fraction& fraction2) {
        return (fraction1.numerator * fraction2.denominator ==
                fraction2.numerator * fraction1.denominator);
    }
    
    friend std::ostream& operator<<(std::ostream& output,
                                    const Fraction& fraction) {
        output << fraction.numerator << '/' << fraction.denominator;
        return output;
    }
    
};

int main() {
    
#ifdef __PRBL032_IS_IN_DEBUGGING_PHASE_01__
    Fraction fraction1(1,   2);     std::cout << fraction1 << std::endl;
    Fraction fraction2(150, 300);   std::cout << fraction2 << std::endl;
    Fraction fraction3(100, 201);   std::cout << fraction3 << std::endl;
    std::cout << (fraction1 == fraction2) << std::endl;
    std::cout << (fraction2 == fraction3) << std::endl;
    std::cout << (fraction3 == fraction1) << std::endl;
#endif

    std::vector<Fraction> curiousFractions;

    for (int a = 1; a <= 9; ++a) {
        for (int b = 1; b <= 9; ++b) {
            for (int c = 1; c <= 9; ++c) {
                if ((a == b) && (b == c)) {
                    continue;
                }
                Fraction complicated(10 * a + b, 10 * b + c);
                Fraction simplified(a, c);
                if (complicated == simplified) {
                    std::cout << complicated << ' ' << simplified << std::endl;
                    curiousFractions.push_back(complicated);
                }
            }
        }
    }
    
    Fraction product(1, 1);
    for (std::vector<Fraction>::const_iterator i = curiousFractions.begin();
         i != curiousFractions.end();
         ++i) {
        product = product * (*i);
    }
    std::cout << product << std::endl;
    
    return 0;
}

static int gcd(int x, int y) {
    if (y == 0) {
        return x;
    } else {
        return gcd(y, x % y);
    }
}