#include "Cards/cardIncludes.h"
#include "Players/playerIncludes.h"
#include "LeaderBoard.h"

#include <iostream>
#include <assert.h>
#include <string>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::make_shared;
using std::shared_ptr;

#define TEST_ERROR_CATCHING(function_call, exception_type, except_fail)\
{\
    bool thrown = false; \
    try{\
        function_call; \
    } \
    catch (exception_type){\
        thrown = true; \
    }\
    assert(thrown == except_fail);\
}

template <typename T>
void run_test(T testFunc, const string& t_name){
    static int counter = 1;

    cout << "> running test " << counter << ": " << t_name << "" << endl;
    testFunc();
    cout << "test finished successfully" << endl << endl;
    counter++;
}

void test_HP(){
    // constructor
    HealthPoints hp;
    TEST_ERROR_CATCHING(HealthPoints fail(-1), const std::invalid_argument&, true)
    TEST_ERROR_CATCHING(HealthPoints fail(0), const std::invalid_argument&, true)

    assert(hp == 100);
    assert(hp.healthMaxed() == true);
    assert(hp > HealthPoints::MIN_HP == true);

    // damage
    hp -= 50;
    assert(hp == 50);
    assert(hp.healthMaxed() == false);
    assert(hp > HealthPoints::MIN_HP == true);

    // heal
    hp += 100;
    assert(hp == 100);
    assert(hp.healthMaxed() == true);

    // kill
    hp -= 1000;
    assert(hp > HealthPoints::MIN_HP == false);
    assert(hp == 0);

    // int convertion operator
    int coins = hp;
    assert(coins == 0);
}

void test_CoinPile(){
    TEST_ERROR_CATCHING(CoinPile fail(-1), const std::invalid_argument&, true)

    CoinPile p1;
    assert(p1 == 0);

    // add
    p1 += 10;
    assert(p1 == 10);

    // pay
    assert(p1 -= 6 == true);
    assert(p1 == 4);
    assert(p1 -= 4 == true);
    assert(p1 == 0);
    assert(p1 -= 0 == true);
    assert(p1 -= 1 == false);

    // int convertion operator
    int coins = p1;
    assert(coins == 0);
}

void test_Player(){
    Player p("Moshe", 100, 5, 2, 10, std::make_shared<RiskTaking>());
    TEST_ERROR_CATCHING(Player p1("Moshasnjcsakjcsajcanksncjae", 100, 5, 2, 10, std::make_shared<RiskTaking>()), const std::invalid_argument&, true)
    TEST_ERROR_CATCHING(Player p1("M e", 100, 5, 2, 10, std::make_shared<RiskTaking>()), const std::invalid_argument&, true)
    TEST_ERROR_CATCHING(Player p1("a", 100, 5, 2, 10, nullptr), const std::invalid_argument&, true)

    assert(p.getCoins() == 10);
}

void test_Behavior(){
    Player p1("Moshe", 100, 5, 2, 10, std::make_shared<RiskTaking>());
    Behavior& b1 = p1.getBehavior();
    assert(b1.buyPotion(p1) == false);
    assert(b1.getName() == "RiskTaking");

    p1.getHealthPoints() -= 51;
    assert(b1.buyPotion(p1) == true);

    Player p2("Moshe", 100, 5, 2, 10, std::make_shared<Responsible>());
    Behavior& b2 = p2.getBehavior();
    assert(b2.buyPotion(p2) == false);
    assert(b2.getName() == "Responsible");

    p2.getHealthPoints() -= 1;
    assert(b2.buyPotion(p2) == true);
}

void func(Player& p){
    return;
}

void test_Jobs(){
    Warrior w("Moshe", std::make_shared<Responsible>());
    Sorcerer s("Itzik", std::make_shared<Responsible>());

    w.applySolarEclipse();
    assert(w.getForce() == 1);

    s.applySolarEclipse();
    assert(s.getForce() == 3);
}

void test_LeadBoard(){
    LeaderBoard b, b2;
    std::shared_ptr<Player> p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

    p1 = std::make_shared<Player>("AMoshea", 100, 2, 1, 10, std::make_shared<RiskTaking>());
    p2 = std::make_shared<Player>("Mosheb", 100, 2, 1, 10, std::make_shared<RiskTaking>());
    p3 = std::make_shared<Player>("Moshec", 100, 2, 1, 10, std::make_shared<RiskTaking>());
    p4 = std::make_shared<Player>("Moshed", 100, 4, 1, 10, std::make_shared<RiskTaking>());
    p5 = std::make_shared<Player>("Moshee", 100, 7, 1, 10, std::make_shared<RiskTaking>());
    p6 = std::make_shared<Player>("Moshef", 100, 7, 2, 10, std::make_shared<RiskTaking>());
    p7 = std::make_shared<Player>("Mosheg", 100, 7, 3, 10, std::make_shared<RiskTaking>());
    p8 = std::make_shared<Player>("Mosheh", 100, 7, 4, 11, std::make_shared<RiskTaking>());
    p9 = std::make_shared<Player>("Moshei", 100, 7, 4, 12, std::make_shared<RiskTaking>());
    p10 = std::make_shared<Player>("Moshej", 100, 7, 4, 13, std::make_shared<RiskTaking>());
    b2.insert(p10);
    b2.insert(p9);
    b2.insert(p8);
    b2.insert(p7);
    b2.insert(p6);
    b2.insert(p5);
    b2.insert(p4);
    b2.insert(p3);
    b2.insert(p2);
    b2.insert(p1);

    b.insert(p6);
    b.insert(p2);
    b.insert(p4);
    b.insert(p8);
    b.insert(p1);
    b.insert(p7);
    b.insert(p5);
    b.insert(p9);
    b.insert(p3);
    b.insert(p10);

    for (size_t i = 0; i < b.getPlayers().size(); i++){
        assert(b.getPlayers()[i] == b2.getPlayers()[i]);
    }
}

int applySolarEclipse(Player& p, const Card* c){
    p.buff(1);
    return 1;
}

int main(){
    run_test(test_HP, "HealthPoints");
    run_test(test_CoinPile, "CoinPile");
    run_test(test_Player, "Player");
    run_test(test_Behavior, "Behavior");
    run_test(test_Jobs, "Jobs");
    run_test(test_LeadBoard, "LeaderBoard");
}