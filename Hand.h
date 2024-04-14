//
// Created by zahin on 11/04/24.
//

#ifndef POKER_HAND_H
#define POKER_HAND_H

#include <iostream>
#include <string>

#include "Card.h"

using namespace std;

class Hand {
public:
    static string handTypes[];
    static int SIZE_OF_HAND;

private:
    Card **cards;
    int highestHand = 0;
    static int numOfHands;

public:
    Hand();

    Hand(Card **cards);

    Hand(const Hand &h);

    ~Hand();

    [[nodiscard]] Card** getCards();

    [[nodiscard]] int getHighestHandRaw();

    [[nodiscard]] string getHighestHand();

    [[nodiscard]] string toString() const;

    static int getNumOfHands();

    static void deleteHand(Hand *hand);

    void operator=(const Hand& other);

    friend ostream& operator<<(ostream& os, const Hand& hand);

    static bool checkRoyalFlush(Hand *hand);

    static bool checkStraightFlush(Hand *hand);

    static bool check4OfAKind(Hand *hand);

    static bool checkFullHouse(Hand *hand);

    static bool checkFlush(Hand *hand);

    static bool checkStraight(Hand *hand);

    static bool check3OfAkind(Hand *hand);

    static bool check2Pair(Hand *hand);

    static bool checkPair(Hand *hand);

private:
    void determineHighestHand();
};


#endif //POKER_HAND_H
