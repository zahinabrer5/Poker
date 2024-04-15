//
// Created by zahin on 04/03/24.
//

#include <iostream>
#include <string>
#include <sstream>

#include "Card.h"

using namespace std;

int Card::numOfCards = 0;
string Card::faces[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Joker", "Queen", "King", "Ace" };
string Card::suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

// default constructor
Card::Card() {
    numOfCards++;
}

// parameterized constructor
Card::Card(int face, int suit) {
    setFace(face);
    setSuit(suit);
    numOfCards++;
}

// copy constructor
Card::Card(const Card &c) : face(c.face), suit(c.suit) {
    numOfCards++;
}

// destructor
Card::~Card() {
    numOfCards--;
}

// getters & setters
int Card::getFace() const {
    return face;
}

int Card::getSuit() const {
    return suit;
}

void Card::setFace(int f) {
    if (0 <= f && f <= 12)
        face = f;
}

void Card::setSuit(int s) {
    if (0 <= s && s <= 3)
        suit = s;
}

string Card::toString() const {
    stringstream ss;
    ss << faces[face] << " of " << suits[suit];
    return ss.str();
}

__attribute__((unused)) int Card::getNumOfCards() {
    return numOfCards;
}

__attribute__((unused)) void Card::deleteCards(Card **cards, int size) {
    for (int i = 0; i < size; i++)
        delete cards[i];
    delete[] cards;
}

// overload the assignment operator to complete the Rule of Three
Card& Card::operator=(const Card& other) {
    setFace(other.getFace());
    setSuit(other.getSuit());
    return *this;
}

// Card& Card::operator=(const Card& other) = default;

ostream& operator<<(ostream& os, const Card& card) {
    os << Card::faces[card.face] << " of " << Card::suits[card.suit];
    return os;
}
