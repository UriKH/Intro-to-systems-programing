#include "Mtmchkin.h"
#include "Player.h"


Mtmchkin::Mtmchkin(const char* playerName, const Card* cardsArray, int numOfCards) :
    m_player(Player(playerName)){
    m_cardsArray = copyCardsArray(cardsArray, numOfCards);
    m_numberOfCards = numOfCards;
    m_status = GameStatus::MidGame;
    m_cardIndex = 0;
}

void Mtmchkin::playNextCard(){
    if (m_cardIndex >= m_numberOfCards){
        m_cardIndex = 0;
    }

    m_cardsArray[m_cardIndex].printInfo();
    m_cardsArray[m_cardIndex].applyEncounter(m_player);
    m_player.printInfo();
    m_cardIndex++;

    if (m_player.getLevel() >= GAME_MAX_LEVEL){
        m_status = GameStatus::Win;
    }
    else if (m_player.isKnockedOut()){
        m_status = GameStatus::Loss;
    }
}

bool Mtmchkin::isOver() const{
    return m_status != GameStatus::MidGame;
}

GameStatus Mtmchkin::getGameStatus() const{
    return m_status;
}

Mtmchkin::~Mtmchkin(){
    delete[] m_cardsArray;
}

Mtmchkin::Mtmchkin(const Mtmchkin& mtmchkin) : m_player(Player(mtmchkin.m_player)){
    m_numberOfCards = mtmchkin.m_numberOfCards;
    m_cardsArray = copyCardsArray(mtmchkin.m_cardsArray, m_numberOfCards);
    m_status = mtmchkin.m_status;
    m_cardIndex = mtmchkin.m_cardIndex;
}

Mtmchkin& Mtmchkin::operator=(const Mtmchkin& other){
    if (this == &other){
        return *this;
    }

    m_player = Player(other.m_player);
    m_numberOfCards = other.m_numberOfCards;
    m_cardsArray = copyCardsArray(other.m_cardsArray, m_numberOfCards);
    m_status = other.m_status;
    m_cardIndex = other.m_cardIndex;
    return *this;
}

Card* Mtmchkin::copyCardsArray(const Card* cardsArray, int numOfCards){
    if (!cardsArray || numOfCards <= 0){
        return NULL;
    }

    Card* cards = new Card[numOfCards];
    for (int i = 0; i < numOfCards; i++){
        cards[i] = cardsArray[i];
    }
    return cards;
}