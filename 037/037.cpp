//
//  main.cpp
//  Prbl037
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  The only solutions with 2 or 5 are 23 and 53. All other solutions should
//  consist solely of 1, 3, 7 and 9.
//
//  Analyze the number of 1s and 7s. Considering mod 3 properties, there exist
//  at most two 1s and 7s in total. The following table shows the all possible
//  circumstances that need to be checked.
//
//  # of 1  # of 7  possibilities
//  0       0       impossible
//  1       0       313
//  0       1       73, 37, 373
//  2       0       31...13
//  1       1       7...13, 37...13, 31...7, 31...73
//  0       2       7...7, 7...73, 37...7, 37...37
//
//  So we need to find the possible extensions of 31..., 7..., 37..., and use
//  possible extensions to expand to all possible individual truncable prime.
//  Then we can simply check all possibilities.
//  -------------------------------------------
//  Answer: 748317
//

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "prime.h"

typedef std::vector<std::string> StringVec;
typedef std::set<std::string> StringSet;

static StringVec append3Or9(std::string basicPrefix);
static bool isTruncable(std::string nString);

int main() {
    StringVec prefixesStarting31 = append3Or9("31");
    StringVec prefixesStarting7  = append3Or9("7");
    StringVec prefixesStarting37 = append3Or9("37");
    
    StringSet possibilities;
    possibilities.insert("23");
    possibilities.insert("53");
    
    possibilities.insert("313");
    possibilities.insert("73");
    possibilities.insert("37");
    possibilities.insert("373");
    for (StringVec::const_iterator i = prefixesStarting31.begin();
         i != prefixesStarting31.end();
         ++i) {
        possibilities.insert(*i + "13");
        possibilities.insert(*i + "7");
        possibilities.insert(*i + "73");
    }
    for (StringVec::const_iterator i = prefixesStarting7.begin();
         i != prefixesStarting7.end();
         ++i) {
        possibilities.insert(*i + "13");
        possibilities.insert(*i + "7");
        possibilities.insert(*i + "73");
    }
    for (StringVec::const_iterator i = prefixesStarting37.begin();
         i != prefixesStarting37.end();
         ++i) {
        possibilities.insert(*i + "13");
        possibilities.insert(*i + "7");
        possibilities.insert(*i + "73");
    }
    
    int sumTruncablePrimes = 0;
    for (StringSet::const_iterator i = possibilities.begin();
         i != possibilities.end();
         ++i) {
        if (isTruncable(*i)) {
            std::cout << *i << std::endl;
            sumTruncablePrimes += std::atoi((*i).c_str());
        }
    }
    std::cout << "sum: " << sumTruncablePrimes << std::endl;
    
    return 0;
}

/**
 * Generates all possible prefixes expanding <code>basicPrefix</code> with 3 or 
 * 9.
 */
static StringVec append3Or9(std::string basicPrefix) {
    StringVec prefixes;
    prefixes.push_back(basicPrefix);
    // Use StringVec to model a queue.
    StringVec::size_type front, rear;
    front = 0; rear = 0;
    while (front <= rear) {
        std::string prefix = prefixes[front];
        // Try to append 3.
        if (isPrime(std::atoi((prefix + '3').c_str()))) {
            prefixes.push_back(prefix + '3');
            ++rear;
        }
        // Try to append 9.
        if (isPrime(std::atoi((prefix + '9').c_str()))) {
            prefixes.push_back(prefix + '9');
            ++rear;
        }
        ++front;
    }
    return prefixes;
}

static bool isTruncable(std::string nString) {
    for (int count = 1; count <= nString.length(); ++count) {
        if (!isPrime(std::atoi((nString.substr(0, count)).c_str()))) {
            return false;
        }
    }
    for (int pos = 0; pos < nString.length(); ++pos) {
        if (!isPrime(std::atoi((nString.substr(pos)).c_str()))) {
            return false;
        }
    }
    return true;
}