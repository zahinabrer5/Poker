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
int Player::idIncrementor = 0;

Player::Player() {
    cards = new Card*[numOfCards];
    numOfPlayers++;
    id = ++idIncrementor;
}

Player::Player(int numOfCards) {
    if (numOfCards < 1 || numOfCards > 5)
        return;
    this->numOfCards = numOfCards;
    cards = new Card*[numOfCards];
    numOfPlayers++;
    id = ++idIncrementor;
}

Player::Player(Card** cards, int numOfCards) {
    if (numOfCards < 1 || numOfCards > 5)
        return;
    this->numOfCards = numOfCards;
    this->cards = new Card*[numOfCards];
    for (int i = 0; i < numOfCards; i++)
        this->cards[i] = cards[i];
    // Card::deleteCards(cards, numOfCards);
    numOfPlayers++;
    id = ++idIncrementor;
}

Player::Player(const Player &p) : cards(p.cards), numOfCards(p.numOfCards) {
    numOfPlayers++;
    id = ++idIncrementor;
}

Player::~Player() {
    Card::deleteCards(cards, numOfCards);
    numOfPlayers--;
}

int Player::getId() {
    return id;
}

int Player::getNumOfCards() {
    return numOfCards;
}

Card** Player::getCards() {
    return cards;
}

/*
void addCard(Card* card) {
    if (numOfCards == 5)
        return;
    Card** updated = new Card*[++numOfCards];
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
    ss << "Player #" << id << ":\n";
    ss << "===============================\n";
    for (int i = 0; i < numOfCards; i++)
        ss << "Card #" << (i+1) << ": " << cards[i]->toString() << '\n';
    return ss.str();
}

int Player::getNumOfPlayers() {
    return numOfPlayers;
}

void Player::operator=(const Player& other) {
    numOfCards = other.numOfCards;
    cards = other.cards;
}

ostream& operator<<(ostream& os, const Player& player) {
    os << "Player #" << player.id << ":\n";
    os << "===============================\n";
    for (int i = 0; i < player.numOfCards; i++)
        os << "Card #" << (i+1) << ": " << player.cards[i] << '\n';
    return os;
}
