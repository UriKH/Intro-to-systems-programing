#pragma once

#include <vector>
#include "Player.h"

class LeadBoard{
    std::vector<const Player*> m_players;
public:
    LeadBoard() = default;

    void refresh();
    void insert(const Player* player);
    std::vector<const Player*> getPlayers();
};