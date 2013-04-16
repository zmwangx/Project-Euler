//
//  main.cpp
//  Prbl029
//  Project Euler
//
//  Created by Zhiming Wang on 12/06/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  It suffices to find the number of quadruplets $(a_1, b_1, a_2, b_2)$ such
//  that
//
//  a_1^{b_1} = a_2^{b_2}.
//
//  Note that if $b_1$ and $b_2$ are coprime, then there must exist some
//  positive integer $t$ such that $a_1 = t^{b_2}, a_2 = t^{b_1}$. The number
//  of this kind of $a_1$ and $a_2$ are very limited; so are $b_1$ and $b_2$,
//  consequently.
//
//  Based on this, we can count upon all possible coprime $b_1$ and $b_2$.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>

struct Power {
    int base;
    int index;
    
    Power(int base, int index) {
        this->base  = base;
        this->index = index;
    }
    
    friend bool operator<(const Power& power1, const Power& power2) {
        if (power1.base != power2.base) {
            return power1.base < power2.base;
        } else {
            return power1.index < power2.index;
        }
    }
};

typedef std::set<Power> EqualPowers;

typedef std::map<Power, EqualPowers> EqualPowerMap;

/**
 * The actual range in action is [2, RANGE].
 */
const int RANGE = 100;

static void generateMaxBases(std::vector<int>& maxBasesWithIndices);
static int gcd(int x, int y);

int main() {
    // maxBasesWithIndices[k] is the maximum base of k-th powers in the range
    // [2, RANGE].
    std::vector<int> maxBasesWithIndices;
    generateMaxBases(maxBasesWithIndices);
    int maxIndex = static_cast<int>(maxBasesWithIndices.size()) - 1;

    /*
#ifdef __PRBL29_IS_IN_DEBUGGING_PHASE_01__
    // std::vector<int> test{0, 4095, 199, 15, 7, 5, 3, 2, 1, 1, 1, 1, 1};
    // computeNumberOfRepeatSets(3, test);
#endif
    
    std::vector<int> numbersOfRepeatSets;
    // Repeating 0 or 1 time is meaningless, so these slots are filled by 0.
    numbersOfRepeatSets.push_back(0);
    numbersOfRepeatSets.push_back(0);
    int nRepeatTimes = 2;
    while (true) {
        int numberOfRepeatSets =
        computeNumberOfRepeatSets(nRepeatTimes, numbersOfPowersWithIndex);
        if (numberOfRepeatSets != 0) {
            numbersOfRepeatSets.push_back(numberOfRepeatSets);
            ++nRepeatTimes;
        } else {
            break;
        }
    }
 */
    
    EqualPowerMap equalPowerMap;
    
    for (int index1 = 1; index1 <= maxIndex - 1; ++index1) {
        for (int index2 = index1 + 1; index2 <= maxIndex; ++index2) {
            if (gcd(index1, index2) == 1) {
                for (int indicesGcd = 1;
                     indicesGcd * index2 <= RANGE;
                     ++indicesGcd) {
                    if ((index1 == 1) && (indicesGcd == 1)) {
                        continue;
                    }
                    int actualIndex1 = index1 * indicesGcd;
                    int actualIndex2 = index2 * indicesGcd;
                    for (int basicBase = 2;
                         basicBase <= maxBasesWithIndices[index2];
                         ++basicBase) {
                        int actualBase1 =
                        static_cast<int>(std::pow(basicBase, index2));
                        int actualBase2 =
                        static_cast<int>(std::pow(basicBase, index1));

                        Power power1(actualBase1, actualIndex1);
                        Power power2(actualBase2, actualIndex2);
                        
                        equalPowerMap[power1].insert(power2);
                        equalPowerMap[power2].insert(power1);
                    }
                }
            }
        }
    }
    

    // Entry repeatCountMap[k] stands for the number of powers involved in a k-
    // repeat, namely, a structure like:
    // a_1^{b_1} = a_2^{b_2} = \cdots = a_k^{b_k}.
    std::map<int, int> repeatCountMap;
    for (EqualPowerMap::const_iterator i = equalPowerMap.begin();
         i != equalPowerMap.end();
         ++i) {
        // the (*i) entry involves nRepeats number of powers.
        int nRepeats = static_cast<int>(i->second.size()) + 1;
        if (repeatCountMap.find(nRepeats) != repeatCountMap.end()) {
            // Key already exists.
            ++repeatCountMap[nRepeats];
        } else {
            // Need to insert new key.
            repeatCountMap[nRepeats] = 1;
        }
    }
    
    int nRedundantCounts = 0;
    for (std::map<int, int>::const_iterator i = repeatCountMap.begin();
         i != repeatCountMap.end();
         ++i) {
        int nRepeats = i->first;
        int nPowersInvolved = i->second;
        nRedundantCounts += nPowersInvolved / nRepeats * (nRepeats - 1);
    }
    
    int nDistinctTerms = (RANGE - 1) * (RANGE - 1) - nRedundantCounts;
    
    std::cout << nDistinctTerms << std::endl;
    
    return 0;
}

static void generateMaxBases(std::vector<int>& maxBasesWithIndices)
{
    // The 0-th element is meaningless, and is pre-filled with 0.
    maxBasesWithIndices.push_back(0);
    int index = 1;
    while (true) {
        // n^index <= RANGE
        int maxBaseWithIndex =
        std::floor(std::exp(std::log(RANGE) / index));
        if (maxBaseWithIndex > 1) {
            maxBasesWithIndices.push_back(maxBaseWithIndex);
        } else {
            break;
        }
        ++index;
    }
}
 
static int gcd(int x, int y) {
    if (y == 0) {
        return x;
    } else {
        return gcd(y, x % y);
    }
}
