#include "Player.h"

#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>

using std::string;
using std::shared_ptr;
using std::invalid_argument;

using namespace Configurations::Player;

bool Player::checkName(const std::string& name){
    if (name.size() > MAX_NAME_SIZE || name.size() < MIN_NAME_SIZE){
        return false;
    }

    for (char letter : name){
        if (!std::isalpha(letter)){
            return false;
        }
    }
    return true;
}

Player::Player(const string& name, std::unique_ptr<Behavior> behavior, std::unique_ptr<Job> job, int hp, int level, int force, int coins)
    : m_name(name), m_hp(HealthPoints(hp)), m_level(level), m_force(force), m_coins(CoinPile(coins)), m_behavior(std::move(behavior)), m_job(std::move(job)){
    if (m_behavior == nullptr){
        throw invalid_argument("Behavior must not be nullptr");
    }

    if (!checkName(name)){
        throw invalid_argument("Name must contain letters only and must not be longer than" + std::to_string(MAX_NAME_SIZE) + "characters");
    }

    if (m_level > MAX_LEVEL || m_level < MIN_LEVEL){
        m_level = MIN_LEVEL;
    }

    if (m_force < MIN_FORCE){
        m_force = MIN_DEFAULT_FORCE;
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

void Player::buff(int buff){
    if (buff < 0){
        throw invalid_argument("buff gets only positive values");
    }
    m_force += buff;
}

int Player::debuff(int debuff){
    if (debuff < 0){
        throw invalid_argument("debuff gets only positive values");
    }
    int before = m_force;
    m_force -= debuff;
    if (m_force < MIN_FORCE){
        m_force = MIN_FORCE;
        return before;
    }
    return m_force - before;
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
    ss << m_name << ", " << m_job->getName() << " with " << m_behavior->getName() << " behavior (level " << m_level << ", force " << m_force << ")";
    return ss.str();
}

bool Player::healthMaxed() const{
    return m_hp == MAX_HP;
}

Job& Player::getJob() const{
    return *m_job;
}