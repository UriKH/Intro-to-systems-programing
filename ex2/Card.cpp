#include "Card.h"


Card::Card(CardType type, const CardStats& stats) : m_effect(type), m_stats(stats){}

void Card::applyEncounter(Player& player) const{
    switch (this->m_effect){
    case CardType::Battle:
    {
        bool battleResult = player.getAttackStrength() >= this->m_stats.force;

        if (battleResult){
            player.levelUp();
            player.addCoins(this->m_stats.loot);
        }
        else{
            player.damage(this->m_stats.hpLossOnDefeat);
        }

        printBattleResult(battleResult);
        break;
    }
    case CardType::Buff:{
        if (player.pay(this->m_stats.cost)){
            player.buff(this->m_stats.buff);
        }
        break;
    }
    case CardType::Heal:
    {
        if (player.pay(this->m_stats.cost)){
            player.heal(this->m_stats.heal);
        }
        break;
    }
    case CardType::Treasure:
    {
        player.addCoins(this->m_stats.loot);
        break;
    }
    }
}

void Card::printInfo() const{
    switch (this->m_effect){
    case CardType::Battle:
        printBattleCardInfo(m_stats);
        break;
    case CardType::Buff:
        printBuffCardInfo(m_stats);
        break;
    case CardType::Heal:
        printHealCardInfo(m_stats);
        break;
    case CardType::Treasure:
        printTreasureCardInfo(m_stats);
        break;
    }
}