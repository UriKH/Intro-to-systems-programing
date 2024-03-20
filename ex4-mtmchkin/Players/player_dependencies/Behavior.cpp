#include "Behavior.h"

bool Responsible::buyPotion(const Player& player){
    return !player.getHealthPointsAsObject().healthMaxed();
}

bool RiskTaking::buyPotion(const Player& player){
    return player.getHealthPoints() < 50;
}
