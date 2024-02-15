#include "Card.h"
#include "utilities.h"


Card::Card(CardType type, const CardStats& stats) : m_effect(type), m_stats(stats){}

void Card::applyEncounter(Player& player) const{
    switch (m_type){
    case CardType::Battle:
        bool battleResult = player.getAttackStrength() >= m_stats->force;

        if (battleResult){
            player.levelUp(1);
            player.addCoins(m_stats->loot);
        }
        else{
            player.demage(m_stats->hpLoss);
        }

        printBattleResult(battleResult);
        break;
    case CardType::Buff || CardType::Heal:
        if (!player.pay(m_stats->cost)){
            break;
        }

        if (CardType::Heal){
            player.heal(m_stats->heal);
        }
        else{
            player.buff(m_stats->buff);
        }
        break;
    case CardType::Treasure:
        player.addCoins(m_stats->loot);
        break;
    }
}

void Card::printInfo() const{
    switch (m_type){
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