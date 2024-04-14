//
// Created by zahin on 11/04/24.
//

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <iostream>
#include <string>

#include "Card.h"
#include "Hand.h"

using namespace std;

class Player {
private:
    string name;
    Card **cards;
    int numOfCards = 2;
    static int numOfPlayers;

public:
    Player();

    Player(int numOfCards, string name);

    Player(Card **cards, int numOfCards, string name);

    Player(const Player &p);

    ~Player();

    [[nodiscard]] string getName();

    [[nodiscard]] int getNumOfCards();

    [[nodiscard]] Card **getCards();

    // void addCard(Card *card);

    [[nodiscard]] string toString() const;

    static int getNumOfPlayers();

    void operator=(const Player& other);

    friend ostream& operator<<(ostream& os, const Player& player);
};


#endif //POKER_PLAYER_H
