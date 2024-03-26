#include "Warrior.h"
#include "Sorcerer.h"
#include "Player.h"
#include "LeadBoard.h"
#include "Event.h"

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

    assert(hp.getCurrentHP() == 100);
    assert(hp.healthMaxed() == true);
    assert(hp.isAlive() == true);

    // damage
    hp.damage(50);
    assert(hp.getCurrentHP() == 50);
    assert(hp.healthMaxed() == false);
    assert(hp.isAlive() == true);

    // heal
    hp.heal(100);
    assert(hp.getCurrentHP() == 100);
    assert(hp.healthMaxed() == true);

    // kill
    hp.damage(1000);
    assert(hp.isAlive() == false);
    assert(hp.getCurrentHP() == 0);

    // int convertion operator
    int coins = hp;
    assert(coins == 0);
}

void test_CoinPile(){
    TEST_ERROR_CATCHING(CoinPile fail(-1), const std::invalid_argument&, true)

    CoinPile p1;
    assert(p1.getCoins() == 0);

    // add
    p1.add(10);
    assert(p1.getCoins() == 10);

    // pay
    assert(p1.pay(6) == true);
    assert(p1.getCoins() == 4);
    assert(p1.pay(4) == true);
    assert(p1.getCoins() == 0);
    assert(p1.pay(0) == true);
    assert(p1.pay(1) == false);

    // int convertion operator
    int coins = p1;
    assert(coins == 0);
}

void test_Player(){
    Player p("Moshe", 100, 5, 2, 10, std::make_shared<RiskTaking>());
    TEST_ERROR_CATCHING(Player p1("Moshasnjcsakjcsajcanksncjae", 100, 5, 2, 10, std::make_shared<RiskTaking>()), const std::invalid_argument&, true)
    TEST_ERROR_CATCHING(Player p1("a", 100, 5, 2, 10, nullptr), const std::invalid_argument&, true)

    assert(p.getCoins() == 10);
}

void test_Behavior(){
    Player p1("Moshe", 100, 5, 2, 10, std::make_shared<RiskTaking>());
    Behavior& b1 = p1.getBehavior();
    assert(b1.buyPotion(p1) == false);
    assert(b1.getName() == "RiskTaking");

    p1.getHealthPoints().damage(51);
    assert(b1.buyPotion(p1) == true);

    Player p2("Moshe", 100, 5, 2, 10, std::make_shared<Responsible>());
    Behavior& b2 = p2.getBehavior();
    assert(b2.buyPotion(p2) == false);
    assert(b2.getName() == "Responsible");

    p2.getHealthPoints().damage(1);
    assert(b2.buyPotion(p2) == true);
}

void func(Player& p){
    return;
}

void test_Jobs(){
    Warrior w("Moshe", 100, 5, 2, 10, std::make_shared<Responsible>());
    Sorcerer s("Itzik", 100, 5, 2, 10, std::make_shared<Responsible>());

    Job::getFunctionality(w, SolarEclipse())(w);
    assert(w.getForce() == 1);

    Job::getFunctionality(s, SolarEclipse())(s);
    assert(s.getForce() == 3);
}

void test_LeadBoard(){
    LeaderBoard b, b2;
    std::shared_ptr<Player> p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

    p1 = std::make_shared<Player>("AMoshe1", 100, 2, 1, 10, std::make_shared<RiskTaking>());
    p2 = std::make_shared<Player>("Moshe2", 100, 2, 1, 10, std::make_shared<RiskTaking>());
    p3 = std::make_shared<Player>("Moshe3", 100, 2, 1, 10, std::make_shared<RiskTaking>());
    p4 = std::make_shared<Player>("Moshe4", 100, 4, 1, 10, std::make_shared<RiskTaking>());
    p5 = std::make_shared<Player>("Moshe5", 100, 7, 1, 10, std::make_shared<RiskTaking>());
    p6 = std::make_shared<Player>("Moshe6", 100, 7, 2, 10, std::make_shared<RiskTaking>());
    p7 = std::make_shared<Player>("Moshe7", 100, 7, 3, 10, std::make_shared<RiskTaking>());
    p8 = std::make_shared<Player>("Moshe8", 100, 7, 4, 11, std::make_shared<RiskTaking>());
    p9 = std::make_shared<Player>("Moshe9", 100, 7, 4, 12, std::make_shared<RiskTaking>());
    p10 = std::make_shared<Player>("Moshe10", 100, 7, 4, 13, std::make_shared<RiskTaking>());
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

    b.refresh();

    for (size_t i = 0; i < b.getPlayers().size(); i++){
        assert(b.getPlayers()[i] == b2.getPlayers()[i]);
    }
}

int applySolarEclipse(Player& p){
    p.buff(1);
    return 1;
}

void INIT_FUNCTIONALITY(){
    Job::initializeMap(Job::getDefaultFunctionlity());
    Job::addFunctionality("Sorcerer", SolarEclipse(), applySolarEclipse);
}

int main(){
    INIT_FUNCTIONALITY();

    run_test(test_HP, "HealthPoints");
    run_test(test_CoinPile, "CoinPile");
    run_test(test_Player, "Player");
    run_test(test_Behavior, "Behavior");
    run_test(test_Jobs, "Jobs");
    run_test(test_LeadBoard, "LeaderBoard");
}