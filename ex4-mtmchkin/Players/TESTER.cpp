#include "HealthPoints.h"
#include "Behavior.h"
#include "CoinPile.h"
#include "Job.h"
#include "Player.h"

#include <iostream>
#include <assert.h>
#include <string>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;

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
}

void test_Player(){
    Player p("Moshe", 100, 5, 2, 10, new RiskTaking());
    TEST_ERROR_CATCHING(Player p1("Moshasnjcsakjcsajcanksncjae", 100, 5, 2, 10, new RiskTaking()), const std::invalid_argument&, true)
    TEST_ERROR_CATCHING(Player p1("a", 100, 5, 2, 10, nullptr), const std::invalid_argument&, true)
}

void test_Behavior(){
    Player p1("Moshe", 100, 5, 2, 10, new RiskTaking());
    Behavior& b1 = p1.getBehavior();
    assert(b1.buyPotion(p1) == false);
    assert(b1.getName() == "RiskTaking");

    p1.getHealthPointsAsObject().damage(51);
    assert(b1.buyPotion(p1) == true);

    Player p2("Moshe", 100, 5, 2, 10, new Responsible());
    Behavior& b2 = p2.getBehavior();
    assert(b2.buyPotion(p2) == false);
    assert(b2.getName() == "Responsible");

    p2.getHealthPointsAsObject().damage(1);
    assert(b2.buyPotion(p2) == true);
}

int main(){
    run_test(test_HP, "HealthPoints");
    run_test(test_CoinPile, "CoinPile");
    run_test(test_Player, "Player");
    run_test(test_Behavior, "Behavior");
}