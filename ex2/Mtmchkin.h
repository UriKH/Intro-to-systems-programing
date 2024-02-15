//
// Created by Daniel_Meents on 07/04/2022.
//

#ifndef EX2_GAME_H
#define EX2_GAME_H
#include <iostream>
#include "Player.h"
#include "Card.h"

/*
 * GameStatus:
 * MidGame - The game is still active and the player continues to encounter cards.
 * Win - The player reached level 10.
 * Loss - The player's HP is 0.
*/
enum class GameStatus{Win, Loss, MidGame};

class Mtmchkin {
public:

    /*
     * C'tor of the game:
     *
     * @param playerName - The name of the player.
     * @param cardsArray - A ptr to the cards deck.
     * @param numOfCards - Num of cards in the deck.
     * @result
     *      An instance of Mtmchkin
    */
    Mtmchkin(const char* playerName, const Card* cardsArray, int numOfCards);


    /*
     * Play the next Card - according to the instruction in the exercise document
     *
     * @return
     *      void
    */
    void playNextCard();

    /*
     *  Check if the game ended:
     *
     *  @return
     *          True if the game ended
     *          False otherwise
     */
    bool isOver() const;


    /*
     *  Get the status of the game:
     *
     *  @return
     *          GameStatus - the current status of the running game
     */
    GameStatus getGameStatus() const;


    /*
     *  destructor copy constructor and operator= not default destructor because allocated memory
     */
    ~Mtmchkin();
	
    Mtmchkin(const Mtmchkin& mtmchkin);

    Mtmchkin& operator=(const Mtmchkin& other);

private:
    Player m_player;
    Card * m_cardsArray;
    int m_numberOfCards;
    GameStatus m_status;
    int m_cardIndex;
    static Card* copyCardsArray(const Card* cardsArray, int numOfCards);
    static const int GAME_MAX_LEVEL = 10;

};


#endif //EX2_GAME_H
