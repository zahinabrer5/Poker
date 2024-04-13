//
// Created by zahin on 04/03/24.
//

#ifndef POKER_CARD_H
#define POKER_CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card {
private:
    int face = 0;
    int suit = 0;
    static int numOfCards;


public:
    static string faces[];
    static string suits[];

    Card();

    Card(int face, int suit);

    Card(const Card &c);

    ~Card();

    // [[nodiscard]] tells compiler to warn if function is called without using
    // the return value
    [[nodiscard]] int getFace() const;

    [[nodiscard]] int getSuit() const;

    void setFace(int face);

    void setSuit(int suit);

    [[nodiscard]] string toString() const;

    static int getNumOfCards();

    static void deleteCards(Card** cards, int size);

    void operator=(const Card& other);

    friend ostream& operator<<(ostream& os, const Card& card);
};


#endif //POKER_CARD_H
