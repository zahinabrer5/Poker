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
    int id;
    Card** cards;
    int numOfCards = 2;
    static int numOfPlayers;
    static int idIncrementor;

public:
    Player();

    Player(int numOfCards);

    Player(Card** cards, int numOfCards);

    Player(const Player &p);

    ~Player();

    [[nodiscard]] int getId();

    [[nodiscard]] int getNumOfCards();

    [[nodiscard]] Card** getCards();

    // void addCard(Card* card);

    [[nodiscard]] string toString() const;

    static int getNumOfPlayers();

    void operator=(const Player& other);

    friend ostream& operator<<(ostream& os, const Player& player);
};


#endif //POKER_PLAYER_H
