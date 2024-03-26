#include "Player.h"

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;
using std::shared_ptr;
using std::invalid_argument;

Player::Player(const string& name, int hp, int level, int force, int coins, shared_ptr<Behavior> behavior)
    : m_name(name), m_hp(HealthPoints(hp)), m_level(level), m_force(force), m_coins(CoinPile(coins)), m_behavior(behavior){
    if (m_behavior == nullptr){
        throw invalid_argument("behavior must not be nullptr");
    }

    if (name.size() > MAX_NAME_SIZE){
        throw invalid_argument("Name is longer than " + std::to_string(MAX_NAME_SIZE) + "characters");
    }

    if (m_level > MAX_LEVEL || m_level < MIN_LEVEL){
        m_level = MIN_LEVEL;
    }

    if (m_force < MIN_FORCE){
        m_force = MIN_FORCE;
    }
}

string Player::getName() const{
    return m_name;
}

const HealthPoints& Player::getHealthPoints() const{
    return m_hp;
}

HealthPoints& Player::getHealthPoints(){
    return m_hp;
}

int Player::getLevel() const{
    return m_level;
}

int Player::getForce() const{
    return m_force;
}

const CoinPile& Player::getCoins() const{
    return m_coins;
}

CoinPile& Player::getCoins(){
    return m_coins;
}

Behavior& Player::getBehavior(){
    return *m_behavior;
}

const Behavior& Player::getBehavior() const{
    return *m_behavior;
}

bool Player::isMaxedOut() const{
    return getLevel() == MAX_LEVEL;
}

// bool Player::isKnockedOut() const{
//     return !m_hp.isAlive();
// }

void Player::buff(int buff){
    if (buff < 0){
        throw invalid_argument("buff gets only positive values");
    }
    m_force += buff;
}

void Player::debuff(int debuff){
    if (debuff < 0){
        throw invalid_argument("debuff gets only positive values");
    }

    m_force -= debuff;
    if (m_force < MIN_FORCE){
        m_force = MIN_FORCE;
    }
}

void Player::levelUp(int levels){
    if (levels < 0){
        throw invalid_argument("level-up amount get positive values  only");
    }
    m_level += levels;
    if (m_level > MAX_LEVEL){
        m_level = MAX_LEVEL;
    }
}

string Player::getDescription() const{
    std::stringstream ss;
    ss << m_name << " with" << m_behavior->getName() << " behavior (level " << m_level << ", force " << m_force << ")";
    return ss.str();
}