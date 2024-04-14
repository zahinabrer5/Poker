//
// Created by zahin on 11/04/24.
//

#include <iostream>
#include <string>
#include <sstream>

#include "Player.h"
#include "Hand.h"

using namespace std;

int Player::numOfPlayers = 0;

Player::Player() {
    cards = new Card*[numOfCards];
    numOfPlayers++;
    name = "1";
}

Player::Player(int numOfCards, string name) {
    if (numOfCards < 1 || numOfCards > 5)
        return;
    this->numOfCards = numOfCards;
    cards = new Card*[numOfCards];
    numOfPlayers++;
    this->name = name;
}

Player::Player(Card **cards, int numOfCards, string name) {
    if (numOfCards < 1 || numOfCards > 5)
        return;
    this->numOfCards = numOfCards;
    this->cards = new Card*[numOfCards];
    for (int i = 0; i < numOfCards; i++)
        this->cards[i] = cards[i];
    // Card::deleteCards(cards, numOfCards);
    numOfPlayers++;
    this->name = name;
}

Player::Player(const Player &p) : cards(p.cards), numOfCards(p.numOfCards), name(p.name) {
    numOfPlayers++;
}

Player::~Player() {
    // Card::deleteCards(cards, numOfCards);
    delete[] cards;
    numOfPlayers--;
}

string Player::getName() {
    return name;
}

int Player::getNumOfCards() {
    return numOfCards;
}

Card **Player::getCards() {
    return cards;
}

/*
void addCard(Card *card) {
    if (numOfCards == 5)
        return;
    Card **updated = new Card*[++numOfCards];
    for (int i = 0; i < numOfCards-1; i++)
        updated[i] = cards[i];
    updated[numOfCards-1] = card;
    Card::deleteCards(cards, numOfCards-1);
    cards = updated;
    Card::deleteCards(updated, numOfCards);
}
*/

string Player::toString() const {
    stringstream ss;
    ss << "Player " << name << ":\n";
    ss << "===============================\n";
    for (int i = 0; i < numOfCards; i++)
        ss << "Card " << (i+1) << ": " << cards[i]->toString() << '\n';
    return ss.str();
}

int Player::getNumOfPlayers() {
    return numOfPlayers;
}

void Player::operator=(const Player& other) {
    name = other.name;
    numOfCards = other.numOfCards;
    cards = other.cards;
}

ostream& operator<<(ostream& os, const Player& player) {
    os << "Player " << player.name << ":\n";
    os << "===============================\n";
    for (int i = 0; i < player.numOfCards; i++)
        os << "Card " << (i+1) << ": " << player.cards[i] << '\n';
    return os;
}
