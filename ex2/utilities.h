#ifndef EX2_UTILITIES_H
#define EX2_UTILITIES_H

#include "Card.h"

class CardStats;

/*
 * Prints info of a Battle card:
 *
 * @param card - Stats of the card.
 * @return
 *      void
 */
void printBattleCardInfo(const CardStats& card);


/*
 * Prints info of a Battle outcomes:
 *
 * @param win - Boolean.
 * @return
 *      void
 */
void printBattleResult(bool win);


/*
 * Prints info of a Buff card:
 *
 * @param win - Is the player won or lost the battle?
 * @return
 *      void
 */
void printBuffCardInfo(const CardStats& card);


/*
 * Prints info of a Heal card:
 *
 * @param card - Stats of the card.
 * @return
 *      void
 */
void printHealCardInfo(const CardStats& card);


/*
 * Prints info of a Treasure card:
 *
 * @param card - Stats of the card.
 * @return
 *      void
 */
void printTreasureCardInfo(const CardStats& card);


/*
 * Prints the details of the player:
 *
 * @param name - The name of the player.
 * @param level - The player's level.
 * @param force - The player's force.
 * @param hp - The player's HP points.
 * @param coins - The player's amount of coins.
 * @return
 *      void
 */
void printPlayerInfo(const char* name, int level, int force, int hp, int coins);



#endif //EX2_UTILITIES_H
