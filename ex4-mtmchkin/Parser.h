#pragma once

#include "CardDeck.h"
#include <vector>
#include "Players/Player.h"
#include <fstream>
#include "Cards/Monsters.h"
#include "Cards/Event.h"

class Parser{
public:
    static void parsePlayers(const std::string& fileName, std::vector<std::shared_ptr<Job>>& players);
    static void parseCards(const std::string& fileName, CardDeck& cardDeck);

    class InvalidPlayersFile: public std::exception{
        const char* what() const noexcept override;
    };

    class InvalidCardsFile : public std::exception{
        const char* what() const noexcept override;
    };

    Parser() = delete;
};
