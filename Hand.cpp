//
// Created by zahin on 11/04/24.
//

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Hand.h"

using namespace std;

// https://cplusplus.com/forum/beginner/4639/
// https://stackoverflow.com/a/65282525/21405641
bool (*(functions[9]))(Hand *hand) = {
    Hand::checkPair,
    Hand::check2Pair,
    Hand::check3OfAkind,
    Hand::checkStraight,
    Hand::checkFlush,
    Hand::checkFullHouse,
    Hand::check4OfAKind,
    Hand::checkStraightFlush,
    Hand::checkRoyalFlush
};

string Hand::handTypes[] = { "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush" };
int Hand::SIZE_OF_HAND = 5;
int Hand::numOfHands = 0;

Hand::Hand() {
    cards = new Card*[SIZE_OF_HAND];
    numOfHands++;
}

Hand::Hand(Card **cards) {
    this->cards = new Card*[SIZE_OF_HAND];
    for (int i = 0; i < SIZE_OF_HAND; i++)
        this->cards[i] = cards[i];
    // Card::deleteCards(cards, SIZE_OF_HAND);
    numOfHands++;
    // cout << "Line 41 of Hand.cpp reached" << endl;
    determineHighestHand();
    // cout << "Line 43 of Hand.cpp reached" << endl;
}

Hand::Hand(const Hand &h) : cards(h.cards), highestHand(h.highestHand) {
    numOfHands++;
}

Hand::~Hand() {
    // we don't delete **cards in the destructor, since we assume the cards are
    // taken from a DeckOfCards object, which should be later deleted by the
    // programmer
    // ^ this also applies to Player and Card classes
    // Card::deleteCards(cards, SIZE_OF_HAND);
    delete[] cards;
    numOfHands--;
}

Card **Hand::getCards() {
    return cards;
}

int Hand::getHighestHandRaw() {
    return highestHand;
}

string Hand::getHighestHand() {
    return handTypes[highestHand-1];
}

string Hand::toString() const {
    stringstream ss;
    ss << "Hand:\n";
    ss << "===============================\n";
    for (int i = 0; i < SIZE_OF_HAND; i++)
        ss << "Card #" << (i+1) << ": " << cards[i]->toString() << '\n';
    ss << "Highest Hand: " << handTypes[highestHand-1] << '\n';
    return ss.str();
}

int Hand::getNumOfHands() {
    return numOfHands;
}

// void Hand::deleteHand(Hand *hand) {
//     Card::deleteCards(hand->getCards(), Hand::SIZE_OF_HAND);
//     delete hand;
// }

void Hand::operator=(const Hand& other) {
    cards = other.cards;
    highestHand = other.highestHand;
}

ostream& operator<<(ostream& os, const Hand& hand) {
    os << "Hand:\n";
    os << "===============================\n";
    for (int i = 0; i < Hand::SIZE_OF_HAND; i++)
        os << "Card #" << (i+1) << ": " << hand.cards[i] << '\n';
    os << "Highest Hand: " << Hand::handTypes[hand.highestHand-1] << '\n';
    return os;
}

void Hand::determineHighestHand() {
    for (int i = 8; i >= 0; i--) {
        if (functions[i](this)) {
            highestHand = i+2;
            return;
        }
    }

    highestHand = 1; // high card (doesn't fit into the other categories)
}

bool Hand::checkRoyalFlush(Hand *hand) {
    if (!checkFlush(hand))
        return false;

    for (int i = 0; i < Hand::SIZE_OF_HAND; i++)
        if (hand->getCards()[i]->getFace() < 8)
            return false;

    return true;
}

bool Hand::checkStraightFlush(Hand *hand) {
    if (!checkFlush(hand))
        return false;

    checkStraight(hand);

    return false;
}

bool Hand::check4OfAKind(Hand *hand) {
    map<int,int> map;
    for (int i = 0; i < Hand::SIZE_OF_HAND; i++)
        map[hand->getCards()[i]->getFace()]++;

    if (map.size() != 2) return false;

    int first = map.begin()->second;
    // end points to the imaginary element after the last element of the map
    int last = map.rbegin()->second; // map.rbegin() == prev(map.end())
    if (first == 1 && last == 4 || first == 4 && last == 1)
        return true;

    return false;
}

bool Hand::checkFullHouse(Hand *hand) {
    map<int,int> map;
    for (int i = 0; i < Hand::SIZE_OF_HAND; i++)
        map[hand->getCards()[i]->getFace()]++;

    if (map.size() != 2) return false;

    int first = map.begin()->second;
    int last = map.rbegin()->second;
    if (first == 2 && last == 3 || first == 3 && last == 2)
        return true;

    return false;
}

bool Hand::checkFlush(Hand *hand) {
    for (int i = 1; i < Hand::SIZE_OF_HAND; i++)
        if (hand->getCards()[i]->getSuit() != hand->getCards()[i-1]->getSuit())
            return false;
    return true;
}

bool Hand::checkStraight(Hand *hand) {
    int *faces = new int[Hand::SIZE_OF_HAND];
    for (int i = 0; i < Hand::SIZE_OF_HAND; i++)
        faces[i] = hand->getCards()[i]->getFace();
    sort(faces, faces+Hand::SIZE_OF_HAND);
    for (int i = 1; i < Hand::SIZE_OF_HAND; i++)
        if (faces[i] != faces[i-1]+1) {
            delete[] faces;
            return false;
        }

    delete[] faces;
    return true;
}

bool Hand::check3OfAkind(Hand *hand) {
    unordered_map<int,int> map;
    for (int i = 0; i < Hand::SIZE_OF_HAND; i++)
        map[hand->getCards()[i]->getFace()]++;

    if (map.size() != 3) return false;

    // https://stackoverflow.com/a/8484055/21405641
    vector<int> vals;
    vals.reserve(map.size());
    for (auto kv : map)
        vals.push_back(kv.second);
    sort(begin(vals), end(vals));

    return vals[0] == 1 && vals[1] == 1 && vals[2] == 3;
}

bool Hand::check2Pair(Hand *hand) {
    unordered_map<int,int> map;
    for (int i = 0; i < Hand::SIZE_OF_HAND; i++)
        map[hand->getCards()[i]->getFace()]++;

    if (map.size() != 3) return false;

    vector<int> vals;
    vals.reserve(map.size());
    for (auto kv : map)
        vals.push_back(kv.second);
    sort(begin(vals), end(vals));

    return vals[0] == 1 && vals[1] == 2 && vals[2] == 2;
}

bool Hand::checkPair(Hand *hand) {
    unordered_map<int,int> map;
    for (int i = 0; i < Hand::SIZE_OF_HAND; i++) {
        int face = hand->getCards()[i]->getFace();
        map[face]++;
    }

    if (map.size() != 4) return false;

    vector<int> vals;
    vals.reserve(map.size());
    for (auto kv : map)
        vals.push_back(kv.second);
    sort(begin(vals), end(vals));

    return vals[0] == 1 && vals[1] == 1 && vals[2] == 1 && vals[3] == 2;
}
