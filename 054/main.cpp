//
//  main.cpp
//  Prbl054
//  Project Euler
//
//  Created by Zhiming Wang on 12/08/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  No algorithm. Follow the rules.
//  -------------------------------
//  Answer:
//

// Test the functionality of <code>poker.h/findRepeatValues</code>.
// #define __PRBL054_IS_IN_DEBUGGING_PHASE_01 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "poker.h"

static Hand readHand(std::istream& input);

int main() {
    
#ifdef __PRBL054_IS_IN_DEBUGGING_PHASE_01
    Cards cards;
    Card card1("2H");
    Card card2("2D");
    Card card3("4C");
    Card card4("4D");
    Card card5("4S");
    cards.push_back(card1);
    cards.push_back(card2);
    cards.push_back(card3);
    cards.push_back(card4);
    cards.push_back(card5);
    std::pair<Cards, Cards> pair = findRepeatValues<3>(cards);
    Cards repeats = pair.first;
    Cards rest = pair.second;
    for (Cards::const_iterator i = repeats.begin(); i != repeats.end(); ++i) {
        std::cout << i->getValue() << " " << i->getSuit() << std::endl;
    }
    for (Cards::const_iterator i = rest.begin(); i != rest.end(); ++i) {
        std::cout << i->getValue() << " " << i->getSuit() << std::endl;
    }
#endif
    
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl054/poker.txt");

    int counter = 0;
    int counterPlayer1Wins = 0;
    int counterPlayer2Wins = 0;
    
    while (input.good()) {
        if (counter == 24) {
            counter = counter;
        }
        std::string lineInput;
        std::getline(input, lineInput);
        if (lineInput.empty()) {
            break;
        }
        
        std::istringstream lineStream(lineInput);
        Hand player1Hand = readHand(lineStream);
        Hand player2Hand = readHand(lineStream);

        ++counter;
        if (player1Hand < player2Hand) {
            std::cout << "2 ";
            ++counterPlayer2Wins;
        } else {
            std::cout << "1 ";
            ++counterPlayer1Wins;
        }
        if (counter % 10 == 0) {
            std::cout << std::endl;
        }
    }
    
    std::cout << std::endl;
    std::cout << "player1 wins: " << counterPlayer1Wins << std::endl;
    std::cout << "player2 wins: " << counterPlayer2Wins << std::endl;
    
    return 0;
}

static Hand readHand(std::istream& input) {
    Cards cards;
    for (int i = 0; i < 5; ++i) {
        std::string cardRepresentation;
        input >> cardRepresentation;
        Card card(cardRepresentation);
        cards.push_back(card);
    }
    Hand hand(cards);
    return hand;
}