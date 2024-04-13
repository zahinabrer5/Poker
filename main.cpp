#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "DeckOfCards.h"
#include "Card.h"
#include "Hand.h"
#include "Player.h"

using namespace std;

void makeCombiUtil(vector<vector<int>>& ans,
    vector<int>& tmp, int n, int left, int k);
vector<vector<int>> makeCombi(int n, int k);

int main() {
    DeckOfCards* deck = new DeckOfCards();
    
    deck->shuffle();

    int max = (52-5)/2;
    int numPlayers = 0;
    do {
        cout << "Enter number of players (1-" << max << "): ";
        cin >> numPlayers;
    } while (!(1 <= numPlayers && numPlayers <= max));

    Card** communityCards = new Card*[5];
    cout << "\nCommunity Cards:\n";
    cout << "===============================\n";
    for (int i = 0; i < 5; i++) {
        communityCards[i] = deck->dealCard();
        cout << communityCards[i]->toString() << '\n';
    }
    cout << '\n';

    int winner = 0;
    int bestHand = 0;

    for (int i = 0; i < numPlayers; i++) {
        // 7 choose 5 
        int n = 7;
        int k = 5;
        
        Card** cards = new Card*[n];
        cards[0] = deck->dealCard();
        cards[1] = deck->dealCard();
        // cout << "Line 48 reached" << endl;
        Player* player = new Player(cards, 2);
        // cout << "Line 50 reached" << endl;
        cout << player->toString() << '\n';
        for (int i = 2; i < n; i++) {
            cards[i] = communityCards[i-2];
            // cout << cards[i]->toString() << endl;
        }
        
        // cout << "Line 57 reached" << endl;
        // for each possible hand in cards...

        // std::vector<Card*> ints;
        // for (int i = 0; i < n; i++)
        //     ints.push_back(cards[i]);
        // for (int i = 0; i < n; ints.push_back(cards[i++]));
        // cout << "Line 64 reached" << endl;

        vector<vector<int>> combinations = makeCombi(n, k);
        for (vector<int> comb : combinations) {
            Card** handCards = new Card*[k];
            // cout << "Line 68 reached" << endl;
            for (int i = 0; i < k; ++i) {
                handCards[i] = cards[comb[i]-1];
                // cout << ints[i]->toString() << endl;
            }
            // cout << "Line 73 reached" << endl;
            Hand* hand = new Hand(handCards);
            // cout << "Line 75 reached" << endl;
            if (hand->getHighestHandRaw() > bestHand) {
                // cout << "Line 77 reached" << endl;
                bestHand = hand->getHighestHandRaw();
                winner = i+1;
            }
            // cout << hand->toString() << "---\n";
            // cout << "Line 81 reached" << endl;
            // Card::deleteCards(handCards, k);
            // Hand::deleteHand(hand);
            // cout << "Line 84 reached" << endl;
        }
    
        // Card::deleteCards(cards, n);
    }

    int winnerInput = 0;
    do {
        cout << "Who wins this round of poker? Enter a player (1-" << numPlayers << "): ";
        cin >> winnerInput;
    } while (!(1 <= winnerInput && winnerInput <= numPlayers));

    if (winnerInput != winner) {
        cout << "Wrong! The actual winner was Player #" << winner << '\n';
        cout << "Player #" << winner << "'s hand was " << Hand::handTypes[bestHand-1] << '\n';
        return 0;
    }

    cout << "What hand did Player #" << winner << " have?\n";
    int bestHandInput = 0;
    do {
        for (int i = 0; i < 10; i++)
            cout << (i+1) << ": " << Hand::handTypes[i] << '\n';
        cout << "Enter the corresponding hand number (1-10): ";
        cin >> bestHandInput;
    } while (!(1 <= bestHandInput && bestHandInput <= 10));

    if (bestHandInput != bestHand) {
        cout << "Wrong! The winner's hand was " << Hand::handTypes[bestHand-1] << '\n';
        return 0;
    }

    cout << "Correct! Thanks for playing.\n";

    return 0;
}

// https://www.geeksforgeeks.org/make-combinations-size-k/
void makeCombiUtil(vector<vector<int>>& ans,
    vector<int>& tmp, int n, int left, int k) {
    // Pushing this vector to a vector of vector
    if (k == 0) {
        ans.push_back(tmp);
        return;
    }
 
    // i iterates from left to n. First time
    // left will be 1
    for (int i = left; i <= n; ++i)
    {
        tmp.push_back(i);
        makeCombiUtil(ans, tmp, n, i + 1, k - 1);
 
        // Popping out last inserted element
        // from the vector
        tmp.pop_back();
    }
}

vector<vector<int>> makeCombi(int n, int k) {
    vector<vector<int>> ans;
    vector<int> tmp;
    makeCombiUtil(ans, tmp, n, 1, k);
    return ans;
}
