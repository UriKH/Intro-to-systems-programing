#pragma once

#include "CardDeck.h"
#include <vector>
#include "Players/Player.h"
#include <fstream>
#include "Cards/Monsters.h"
#include "Cards/Event.h"

class Parser{
public:

    /**
     * Loads data from provided file to the players vector.
     * 
     * @param players the players vector.
     * @param fileName the file name.
     * 
     * @return void
    */
    static void parsePlayers(const std::string& fileName, std::vector<std::shared_ptr<Player>>& players);
    
    /**
     * Loads data from provided file to the cards deck.
     * 
     * @param fileName the file name.
     * @param cardDeck the cards deck.
     * 
     * @return void
    */
    static void parseCards(const std::string& fileName, CardDeck& cardDeck);

    class InvalidPlayersFile: public std::exception{
        const char* what() const noexcept override;
    };

    class InvalidCardsFile : public std::exception{
        const char* what() const noexcept override;
    };

    Parser() = delete;
};
