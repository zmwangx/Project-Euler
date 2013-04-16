//
//  poker.cpp
//  Prbl054
//  Project Euler
//
//  Created by Zhiming Wang on 12/08/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//

// Test the functionality of less than operator of <code>Hand</code> objects.
// #define __POKER_IS_IN_DEBUGGING_PHASE_01__ 1

#include "poker.h"

#include <string>
#include <map>
#include <algorithm>

#include <iostream>

const std::map<char, Card::ValueType> VALUE_MAP = {
    {'2', Card::POKER_2},    {'3', Card::POKER_3},     {'4', Card::POKER_4},
    {'5', Card::POKER_5},    {'6', Card::POKER_6},     {'7', Card::POKER_7},
    {'8', Card::POKER_8},    {'9', Card::POKER_9},     {'T', Card::POKER_10},
    {'J', Card::POKER_JACK}, {'Q', Card::POKER_QUEEN}, {'K', Card::POKER_KING},
    {'A', Card::POKER_ACE}
};

const std::map<char, Card::SuitType> SUIT_MAP = {
    {'H', Card::HEARTS},    {'D', Card::DIAMONDS},
    {'C', Card::CLUBS},     {'S', Card::SPADES}
};

Card::Card(ValueType value, SuitType suit) {
    value_ = value;
    suit_ = suit;
}

Card::Card(const std::string& cardRepresentation) {
    const std::string& card = cardRepresentation;
    value_ = VALUE_MAP.find(card[0])->second;
    suit_ = SUIT_MAP.find(card[1])->second;
}

bool operator<(const Card& card1, const Card& card2) {
    if (card1.value_ < card2.value_) {
        return true;
    } else if (card1.value_ > card2.value_) {
        return false;
    } else {
        return card1.suit_ > card2.suit_;
    }
}

/**
 * Returns -1 for less, 0 for equal, and 1 for greater. Note that cards1 and 
 * card2 must be of the same length.
 */
int cardsCompare(const Cards& cards1, const Cards& cards2) {
    Cards::const_reverse_iterator it1 = cards1.rbegin();
    Cards::const_reverse_iterator it2 = cards2.rbegin();
    while (it1 != cards1.rend() && it2 != cards2.rend()) {
        if ((*it1).getValue() < (*it2).getValue()) {
            return -1;
        }
        if ((*it1).getValue() > (*it2).getValue()) {
            return 1;
        }
        ++it1;
        ++it2;
    }
    return 0;
}

Rank::Rank(Cards cards) {
    std::sort(cards.begin(), cards.end());
    
    // All ranks possible.
    
    // Check consecutive.
    if (areConsecutive(cards)) {
        // Straight, Starght Flush, or Royal Flush.
        
        // Check flush
        if (areFlush(cards)) {
            // Straight Flush or Royal Flush.
            
            // Check royal
            if (cards.back().value_ == Card::POKER_ACE) {
                // Royal Flush.
                rankType_ = ROYAL_FLUSH;
                rankCards_ = cards;
                return;
            }
            
            // Striaght Flush.
            rankType_ = STRAIGHT_FLUSH;
            rankCards_ = cards;
            return;
        }
        
        // Straight.
        rankType_ = STRAIGT;
        rankCards_ = cards;
        return;
    }
    
    // High Card, One Pair, Two Pairs, Three of a Kind, Flush, Full House, and
    // Four of a Kind possible.
    
    // Check four-repeats.
    {
        std::pair<Cards, Cards> fourOneDivision = findRepeatValues<4>(cards);
        Cards& repeats = fourOneDivision.first;
        if (!repeats.empty()) {
            // Four of a Kind.
            rankType_ = FOUR_OF_A_KIND;
            rankCards_ = repeats;
            return;
        }
    }
    
    // High Card, One Pair, Two Pairs, Three of a Kind, Flush, and Full House
    // possible.
    
    // Check three-repeats.
    {
        std::pair<Cards, Cards> threeTwoDivision = findRepeatValues<3>(cards);
        Cards& repeats = threeTwoDivision.first;
        if (!repeats.empty()) {
            // Three of a Kind, Flush, or Full House.
            
            // Check if the remaining is a two-repeat.
            Cards& rest = threeTwoDivision.second;
            std::pair<Cards, Cards> restDivision = findRepeatValues<2>(rest);
            if (!restDivision.first.empty()) {
                // Full House.
                rankType_ = FULL_HOUSE;
                // <code>rankCards_</code> of Full House must be dealt with in
                // special, since whatever the value, the triplet is of higher
                // priority than the pair.
                rankCards_ = restDivision.first;
                rankCards_.push_back(repeats[0]);
                rankCards_.push_back(repeats[1]);
                rankCards_.push_back(repeats[2]);
                return;
            }
            
            // Three of a Kind or Flush.
            
            // Check flush.
            if (areFlush(cards)) {
                // Flush.
                rankType_ = FLUSH;
                rankCards_ = cards;
                return;
            }
            
            // Three of a Kind.
            rankType_ = THREE_OF_A_KIND;
            rankCards_ = repeats;
            return;
        }
    }
    
    // High Card, One Pair, Two Pairs, and Flush possible.
    
    // Check flush.
    if (areFlush(cards)) {
        rankType_ = FLUSH;
        rankCards_ = cards;
        return;
    }
    
    // High Card, One Pair, and Two Pairs possible.
    
    // Check pairs.
    {
        std::pair<Cards, Cards> twoThreeDivision = findRepeatValues<2>(cards);
        Cards& repeats1 = twoThreeDivision.first;
        if (!repeats1.empty()) {
            // One Pair or Two Pairs.
            
            // Check remaining for another pair.
            Cards& rest = twoThreeDivision.second;
            std::pair<Cards, Cards> restDivision = findRepeatValues<2>(rest);
            Cards& repeats2 = restDivision.first;
            if (!repeats2.empty()) {
                // Two Pairs.
                rankType_ = TWO_PAIRS;
                std::merge(repeats1.begin(), repeats1.end(),
                           repeats2.begin(), repeats2.end(),
                           std::back_inserter(rankCards_));
                return;
            }
            
            // One Pair.
            rankType_ = ONE_PAIR;
            rankCards_ = repeats1;
            return;
        }
    }
    
    // High Card.
    rankType_ = HIGH_CARD;
    rankCards_.push_back(cards.back());
    return;
}

bool areConsecutive(const Cards& cards) {
    Cards::size_type cardIndex = 0;
    while ((cardIndex + 1 < cards.size()) &&
           (cards[cardIndex].value_ + 1 == cards[cardIndex + 1].value_)) {
        ++cardIndex;
    }
    if (cardIndex + 1 == cards.size()) {
        return true;
    } else {
        return false;
    }
}

bool areFlush(const Cards& cards) {
    Card::SuitType suit = cards.front().suit_;
    for (Cards::const_iterator i = cards.begin() + 1;
         i != cards.end();
         ++i) {
        if ((*i).suit_ != suit) {
            return false;
        }
    }
    return true;
};

Hand::Hand(const Cards& cards) : rank_(cards), cards_(cards) {
    std::sort(cards_.begin(), cards_.end());
}

bool operator<(const Hand& hand1, const Hand& hand2) {
    // Compare rank.
    
#ifdef __POKER_IS_IN_DEBUGGING_PHASE_01__
    std::cout << std::endl;
    
    std::cout << hand1.rank_.rankType_ + 1 << " "
              << hand2.rank_.rankType_ + 1 << std::endl;
    
    std::cout << hand1.rank_.rankCards_.back().value_ + 1 << " "
              << hand2.rank_.rankCards_.back().value_ + 1 << std::endl;
#endif
    
    if (hand1.rank_.rankType_ < hand2.rank_.rankType_) {
        return true;
    } else if (hand2.rank_.rankType_ < hand1.rank_.rankType_) {
        return false;
    }
    
    // Compare rank values.
    int rankValuesCompare = cardsCompare(hand1.rank_.rankCards_,
                                         hand2.rank_.rankCards_);
    if (rankValuesCompare == -1) {
        return true;
    } else if (rankValuesCompare == 1) {
        return false;
    }
    
    // Compare single card values.
    int cardsValuesCompare = cardsCompare(hand1.cards_, hand2.cards_);
    if (cardsValuesCompare == -1) {
        return true;
    } else if (cardsValuesCompare == 1) {
        return false;
    }
    
    // Impossible
    return false;
}
