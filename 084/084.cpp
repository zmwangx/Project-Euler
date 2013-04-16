//
//  main.cpp
//  Prbl084
//  Project Euler
//
//  Created by Zhiming Wang on 12/13/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Simulation with sufficiently many turns.
//  ----------------------------------------
//  Answer:
//

#include <iostream>
#include <vector>

#include "random.h"

static const int DICE_SIZE = 4;
static const int NUMBER_OF_RUNS = 10000;
static const int NUMBER_OF_TURNS_WITHIN_EACH_RUN = 10000;

enum SQUARE {
    GO,    A1,    CC1,   A2,    T1,    R1,    B1,    CH1,   B2,    B3,
    JAIL,  C1,    U1,    C2,    C3,    R2,    D1,    CC2,   D2,    D3,
    FP,    E1,    CH2,   E2,    E3,    R3,    F1,    F2,    U2,    F3,
    G2J,   G1,    G2,    CC3,   G3,    R4,    CH3,   H1,    T2,    H2,
};

static void generateCardPile(std::vector<int>& pile);
static void move(SQUARE& position,
                 int& consecutiveDoublesCounter,
                 std::vector<int>& ccPile,
                 std::vector<int>& chPile,
                 int& ccPilePosition,
                 int& chPilePosition);
static SQUARE performCommunityChest(int cardNo, SQUARE current);
static SQUARE performChance(int cardNo, SQUARE current);

int main() {
    std::vector<int> nLandings;
    for (int i = 0; i < 40; ++i) {
        nLandings.push_back(0);
    }
    
    for (int nRun = 0; nRun < NUMBER_OF_RUNS; ++nRun) {
        // Generate CC and CH piles.
        std::vector<int> ccPile;
        std::vector<int> chPile;
        generateCardPile(ccPile);
        generateCardPile(chPile);
        int ccPilePosition = 0;
        int chPilePosition = 0;
        
        int nTurns = 0;
        SQUARE position = GO;
        
        int consecutiveDoublesCounter = 0;
        while (true) {
            move(position, consecutiveDoublesCounter,
                 ccPile, chPile, ccPilePosition, chPilePosition);
            ++nLandings[static_cast<int>(position)];
            ++nTurns;
            if (nTurns == NUMBER_OF_TURNS_WITHIN_EACH_RUN) {
                break;
            }
        }
    }
    
    for (int i = 0; i < 40; ++i) {
        std::cout << i << ' ' << nLandings[i] << std::endl;
    }
    
    return 0;
}

static void generateCardPile(std::vector<int>& pile) {
    pile.clear();
    for (int cardNo = 1; cardNo <= 16; ++cardNo) {
        pile.push_back(cardNo);
    }
    for (int i = 0; i < 16; ++i) {
        int swapIndex = randomInt(i, 15);
        int temp;
        temp = pile[i];
        pile[i] = pile[swapIndex];
        pile[swapIndex] = temp;
    }
}

static void move(SQUARE& position,
                 int& consecutiveDoublesCounter,
                 std::vector<int>& ccPile,
                 std::vector<int>& chPile,
                 int& ccPilePosition,
                 int& chPilePosition) {
    int dice1 = randomInt(1, DICE_SIZE);
    int dice2 = randomInt(1, DICE_SIZE);
    
    if (dice1 == dice2) {
        ++consecutiveDoublesCounter;
    } else {
        consecutiveDoublesCounter = 0;
    }
    if (consecutiveDoublesCounter == 3) {
        position = JAIL;
        consecutiveDoublesCounter = 0;
        return;
    }
    
    position =
    static_cast<SQUARE>((static_cast<int>(position) + dice1 + dice2) % 40);
    
    if (position == G2J) {
        position = JAIL;
    }
    
    // Chance must come first, since we can actually go from CH3 to CC3.
    if ((position == CH1) || (position == CH2) || (position == CH3)) {
        chPilePosition = (chPilePosition + 1) % 16;
        int cardNo = chPile[chPilePosition];
        position = performChance(cardNo, position);
    }
    
    if ((position == CC1) || (position == CC2) || (position == CC3)) {
        ccPilePosition = (ccPilePosition + 1) % 16;
        int cardNo = ccPile[ccPilePosition];
        position = performCommunityChest(cardNo, position);
    }
}

static SQUARE performCommunityChest(int cardNo, SQUARE current) {
    //
    // Rules:
    //
    // Community Chest (2/16 cards):
    // 1. Advance to GO
    // 2. Go to JAIL
    //
    
    SQUARE landing;
    switch (cardNo) {
        case 1:
            landing = GO;
            break;
            
        case 2:
            landing = JAIL;
            break;
            
        default:
            landing = current;
            break;
    }
    return landing;
}

static SQUARE performChance(int cardNo, SQUARE current) {
    //
    // Rules:
    //
    // Chance (10/16 cards):
    // 1. Advance to GO
    // 2. Go to JAIL
    // 3. Go to C1
    // 4. Go to E3
    // 5. Go to H2
    // 6. Go to R1
    // 7. Go to next R (railway company)
    // 8. Go to next R
    // 9. Go to next U (utility company)
    // 10. Go back 3 squares.
    //
    
    SQUARE landing;
    switch (cardNo) {
        case 1:
            landing = GO;
            break;
            
        case 2:
            landing = JAIL;
            break;
            
        case 3:
            landing = C1;
            break;
            
        case 4:
            landing = E3;
            break;
            
        case 5:
            landing = H2;
            break;
            
        case 6:
            landing = R1;
            break;
            
        case 7: case 8:
            switch (current) {
                case CH1:
                    landing = R2;
                    break;
                    
                case CH2:
                    landing = R3;
                    break;
                    
                case CH3:
                    landing = R1;
                    break;
                    
                default:
                    break;
            }
            break;
            
        case 9:
            switch (current) {
                case CH1: case CH3:
                    landing = U1;
                    break;
                    
                case CH2:
                    landing = U2;
                    break;
                    
                default:
                    break;
            }
            break;
            
        case 10:
            landing = static_cast<SQUARE>(current - 3); // current >= 3 for all
                                                        // Chance squares.
            
        default:
            landing = current;
            break;
    }
    return landing;
}
