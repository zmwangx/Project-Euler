//
//  poker.h
//  Prbl054
//  Project Euler
//
//  Created by Zhiming Wang on 12/08/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//

#ifndef __ProjectEuler__poker__
#define __ProjectEuler__poker__

#include <string>
#include <vector>
#include <utility>

class Card;
class Rank;
class Hand;

typedef std::vector<Card> Cards;

bool operator<(const Cards& cards1, const Cards& cards2);

class Card {
    
    friend Rank;
    friend Hand;
    
public:
    
    enum ValueType {
        NO_SUCH,    POKER_2,    POKER_3,    POKER_4,    POKER_5,    POKER_6,
        POKER_7,    POKER_8,    POKER_9,    POKER_10,   POKER_JACK, POKER_QUEEN,
        POKER_KING, POKER_ACE
    };
    
    enum SuitType {
        HEARTS,     DIAMONDS,   CLUBS,      SPADES
    };
    
    Card() {
        // Do nothing;
    }
    Card(ValueType value, SuitType suit);
    Card(const std::string& cardRepresentation);
    Card(const Card& other) {
        *this = other;
    }
    
    ~Card() {
        // Do nothing.
    };
    
    Card& operator=(const Card& other) {
        value_ = other.value_;
        suit_ = other.suit_;
        return *this;
    }
    
    ValueType getValue() const {
        return value_;
    }
    
    SuitType getSuit() const {
        return suit_;
    }
    
    friend bool operator<(const Card& card1, const Card& card2);
    
private:
    
    ValueType value_;
    SuitType suit_;
    
};

bool cardsCompare(const Card& card1, const Card& card2);

class Rank {
    
    friend Card;
    friend Hand;
    
public:
    
    enum RankType {
        HIGH_CARD,      ONE_PAIR,       TWO_PAIRS,      THREE_OF_A_KIND,
        STRAIGT,        FLUSH,          FULL_HOUSE,     FOUR_OF_A_KIND,
        STRAIGHT_FLUSH, ROYAL_FLUSH
    };
    
    Rank() {
        // Do nothing.
    };    
    Rank(Cards card);
    
    ~Rank() {
        // Do nothing.
    };
    
    Rank& operator=(const Rank& other) {
        rankType_ = other.rankType_;
        rankCards_ = other.rankCards_;
        return *this;
    }
    
    RankType getRankType() const {
        return rankType_;
    }
        
private:
    
    RankType rankType_;
    Cards rankCards_;
    
    /**
     * Accepts only sorted input, and returns sorted output. Return value is a 
     * pair of <code>Cards</code> objects, the first of which contains the 
     * repeat-valued cards (empty if no satisfactory ones are found), the second 
     * of which contains all the rest cards.
     */
    template <int nRepeats>
    friend std::pair<Cards, Cards> findRepeatValues(const Cards& cards);
    
    friend bool areConsecutive(const Cards& cards);
    
    friend bool areFlush(const Cards& cards);
};

template <int nRepeats>
std::pair<Cards, Cards> findRepeatValues(const Cards& cards) {
    Cards repeats;
    Cards rest;
    Cards::size_type cardIndex = 0;
    while (cardIndex < cards.size()) {
        Card::ValueType value = cards[cardIndex].value_;
        while ((cardIndex < cards.size()) &&
               (cards[cardIndex].value_ == value)) {
            repeats.push_back(cards[cardIndex]);
            ++cardIndex;
        }
        if (repeats.size() == nRepeats) {
            while (cardIndex < cards.size()) {
                rest.push_back(cards[cardIndex]);
                ++cardIndex;
            }
            return std::make_pair(repeats, rest);
        }
        while (!repeats.empty()) {
            rest.push_back(repeats.back());
            repeats.pop_back();
        }
    }
    // Not found.
    return std::make_pair(repeats, rest);
}

bool areConsecutive(const Cards& cards);

bool areFlush(const Cards& cards);

class Hand {
    
    friend Card;
    friend Rank;
    
public:

    Hand() {
        // Do nothing.
    }    
    Hand(const Cards& cards);
    
    ~Hand() {
        // Do nothing.
    };
    
    Hand& operator=(const Hand& other) {
        cards_ = other.cards_;
        rank_ = other.rank_;
        return *this;
    }
    
    Rank::RankType getRankType() const {
        return rank_.rankType_;
    }
    
    friend bool operator<(const Hand& hand1, const Hand& hand2);
        
private:
    
    Cards cards_;
    Rank rank_;
    
};

#endif /* defined(__ProjectEuler__poker__) */
