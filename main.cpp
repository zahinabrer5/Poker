#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "DeckOfCards.h"
#include "Card.h"
#include "Hand.h"
#include "Player.h"

using namespace std;

int getInt();
void getUserInput(int numPlayers, int winner, int bestHand);
void makeCombiUtil(vector<vector<int>> &ans,
                   vector<int> &tmp, int n, int left, int k);
vector<vector<int>> makeCombi(int n, int k);
void printVector(const vector<int>& v);
bool playAgain();
string checkPlural(const string &s, const double &x);

double points = 0;

int main() {
    int games = 0;

    do {
        games++;

        DeckOfCards *deck = new DeckOfCards();

        deck->shuffle();

        int max = (52-Hand::SIZE_OF_HAND)/2;
        int numPlayers;
        do {
            cout << "Enter number of players (1-" << max << "): ";
            numPlayers = getInt();
        } while (!(1 <= numPlayers && numPlayers <= max));

        Card **communityCards = new Card *[Hand::SIZE_OF_HAND];
        cout << "\nCommunity Cards:\n";
        cout << "===============================\n";
        for (int i = 0; i < Hand::SIZE_OF_HAND; i++) {
            communityCards[i] = deck->dealCard();
            cout << "Card " << (i+1) << ": "
                << communityCards[i]->toString() << '\n';
        }
        cout << '\n';

        int winner = 0;
        int bestHand = 0;

        for (int i = 0; i < numPlayers; i++) {
            // Out of 7 cards (community cards + current player's cards),
            // choose 5 cards to make a hand and check if it's the best possible
            // hand for the current player
            int n = 7;
            int k = 5;

            Card **cards = new Card *[n];
            cards[0] = deck->dealCard();
            cards[1] = deck->dealCard();
            Player *player = new Player(cards, 2, to_string(i+1));
            cout << player->toString() << '\n';
            delete player;
            for (int j = 2; j < n; j++)
                cards[j] = communityCards[j-2];

            // for (int i = 0; i < n; i++)
                // cout << "Card " << (i+1) << ": "
                //     << cards[i]->toString() << '\n';

            vector<vector<int>> combinations = makeCombi(n, k);
            for (vector<int> comb : combinations) {
                // cout << "Comb: ";
                // printVector(comb);
                Card **handCards = new Card *[k];
                for (int j = 0; j < k; ++j)
                    handCards[j] = cards[comb[j]-1];
                Hand *hand = new Hand(handCards);
                // cout << hand->toString() << "---\n";
                if (hand->getHighestHandRaw() > bestHand) {
                    bestHand = hand->getHighestHandRaw();
                    winner = i+1;
                }
                delete[] handCards;
                delete hand;
            }

            delete[] cards;
        }

        delete[] communityCards;
        delete deck;

        getUserInput(numPlayers, winner, bestHand);
    } while (playAgain());

    cout << "Thanks for playing. You got " << points << " "
        << checkPlural("point", points) << " out of " << games << " "
        << checkPlural("game", games) << " (" << fixed << showpoint
        << setprecision(2) << points/games*100 << "%)\n";

    return 0;
}

void ignoreLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
int getInt() {
    while (true) { // Loop until user enters a valid input
        // cout << "Enter an integer: ";
        int x{};
        cin >> x;

        // Check for failed extraction
        if (!cin) { // If the previous extraction failed
            if (cin.eof()) // If the stream was closed
                exit(0);   // Shut down the program now

            // Let's handle the failure
            cin.clear();  // Put us back in 'normal' operation mode
            ignoreLine(); // And remove the bad input

            cout << "Please enter an integer: ";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return x;     // Return the value we extracted
    }
}

// https://www.geeksforgeeks.org/make-combinations-size-k/
void makeCombiUtil(vector<vector<int>> &ans,
                   vector<int> &tmp, int n, int left, int k) {
    // Pushing this vector to a vector of vector
    if (k == 0) {
        ans.push_back(tmp);
        return;
    }

    // i iterates from left to n. First time
    // left will be 1
    for (int i = left; i <= n; ++i) {
        tmp.push_back(i);
        makeCombiUtil(ans, tmp, n, i+1, k-1);

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

void printVector(const vector<int>& v) {
    for (auto i : v)
        cout << i << ' ';
    cout << '\n';
}

void getUserInput(int numPlayers, int winner, int bestHand) {
    if (numPlayers > 1) {
        int winnerInput;
        do {
            cout << "If there are multiple winners, pick the first one.\n";
            cout << "Who wins this round of poker? Enter a player (1-"
                << numPlayers << "): ";
            winnerInput = getInt();
        } while (!(1 <= winnerInput && winnerInput <= numPlayers));

        if (winnerInput != winner) {
            cout << "Wrong! The actual winner was Player " << winner << '\n';
            // cout << "Player " << winner << "'s hand was "
            //     << Hand::handTypes[bestHand-1] << '\n';
        } else points += 0.5;
    } else points += 0.5;

    cout << "What hand did Player " << winner << " have?\n";
    int bestHandInput;
    for (int i = 0; i < 10; i++)
        cout << (i+1) << ": " << Hand::handTypes[i] << '\n';
    do {
        cout << "Enter the corresponding hand number (1-10): ";
        bestHandInput = getInt();
    } while (!(1 <= bestHandInput && bestHandInput <= 10));

    if (bestHandInput != bestHand)
        cout << "Wrong! The winner's hand was "
            << Hand::handTypes[bestHand-1] << '\n';
    else {
        cout << "Correct!\n";
        points += 0.5;
    }
}

bool playAgain() {
    int ans;
    do {
        cout << "Play again? 1=Yes, 0=No: ";
        ans = getInt();
    } while (!(0 <= ans && ans <= 1));
    bool ret = (bool)ans;
    if (ret)
        for (int i = 0; i < 5; i++)
            cout << '\n';
    return ret;
}

string checkPlural(const string &s, const double &x) {
    stringstream ss;
    ss << s;
    if (x != 1)
        ss << 's';
    return ss.str();
}
