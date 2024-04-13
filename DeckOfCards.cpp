//
// Created by zahin on 04/03/24.
//

#include <algorithm>
#include <random>
#include <chrono>
#include <string>

#include "DeckOfCards.h"
#include "Card.h"

using namespace std;

DeckOfCards::DeckOfCards() {
    deck = new Card*[SIZE_OF_DECK];
    int i = 0;
    for (int s = 0; s < 4; s++)
        for (int f = 0; f < 13; f++)
            deck[i++] = new Card(f, s);
}

DeckOfCards::~DeckOfCards() {
    for (int i = 0; i < SIZE_OF_DECK; i++)
        delete deck[i];
    delete[] deck;
}

// see "Example" section from https://cplusplus.com/reference/algorithm/shuffle/
void DeckOfCards::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck, deck+SIZE_OF_DECK, std::default_random_engine(seed));
}

Card* DeckOfCards::dealCard() {
    if (moreCards())
        return deck[currentCard++];
    return {};
}

bool DeckOfCards::moreCards() {
    if (currentCard == SIZE_OF_DECK)
        return false;
    return true;
}
