//
// Created by zahin on 04/03/24.
//

#ifndef POKER_DECKOFCARDS_H
#define POKER_DECKOFCARDS_H


#include "Card.h"

class DeckOfCards {
private:
    Card** deck;
    int currentCard = 0;
    static const int SIZE_OF_DECK = 52;

public:
    DeckOfCards();

    ~DeckOfCards();

    void shuffle();

    Card* dealCard();

    bool moreCards();
};


#endif //POKER_DECKOFCARDS_H
