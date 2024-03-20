
#include "utilities.h"

#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

void printStartMessage() {
    cout << "Game is about to start!" << endl;
    cout << "These are the players:" << endl;
    cout << endl;
}

void printStartPlayerEntry(int index, const Player& player) {
    cout << index << ". " << player.getDescription() << endl;
}

void printTurnDetails(int index, const Player& player, const Card& card) {
    cout << "Turn: " << index << endl;
    cout << "Player: " << player.getDescription() << endl;
    cout << "Card: " << card.getDescription() << endl;
}

void printTurnOutcome(string outcome) {
    cout << outcome << endl;
    cout << endl;
}

void printRoundStart() {
    cout << "New round starts!" << endl;
    cout << endl;
}

void printRoundEnd() {
    cout << "Round has ended!" << endl;
}

void printLeaderBoardMessage() {
    cout << "Leader board is as follows:" << endl;
    cout << "Ranking    Player Name     Level     Force HP    Coins" << endl;
}

void printLeaderBoardEntry(int i, const Player& player) {
    cout << i << "          ";
    const int nameDistance = 16;
    const int distance = 6;
    string name = player.getName();
    cout << name;
    for(unsigned int i = 0; i < nameDistance - name.size(); i++){
        cout << " ";
    }
    int level = player.getLevel();
    cout << level;
    if(level < 10){
        cout << " ";
    }
    int force = player.getForce();
    cout <<  "        " << force;
    for(unsigned int i = 0; i < distance - to_string(force).size(); i++){
        cout << " ";
    }
    int healthPoints = player.getHealthPoints();
    cout << healthPoints;
    for(unsigned int i = 0; i < distance - to_string(healthPoints).size(); i++){
        cout << " ";
    }
    int coins = player.getCoins();
    cout << coins;
    cout << endl;
}

void printBarrier() {
    cout << endl;
    cout << "----------------------------------------";
    cout << endl << endl;
}

void printGameOver() {
    cout << "Game is over!" << endl;
}

void printWinner(const Player& player) {
    cout << "The winner is: " << player.getName() << endl;
    cout << "Congratulations!" << endl;
    cout << endl;
}

void printNoWinners() {
    cout << "There are no winners in this game." << endl;
    cout << "Better luck next time!" << endl;
}


string getEncounterWonMessage(const Player& player, int loot) {
    return player.getName() + " won the encounter, gained " + to_string(loot) + " coins and leveled up!";
}

string getEncounterLostMessage(const Player& player, int damage) {
    return player.getName() + " lost the encounter and took " + to_string(damage) + " damage!";
}

string getPotionsPurchaseMessage(const Player& player, int amount) {
    return player.getName() + " bought " + to_string(amount) + " potions!";
}

string getSolarEclipseMessage(const Player& player, int effect) {
    return player.getName() + " was affected by a solar eclipse! their force has changed by " + to_string(effect) + "!";
}
