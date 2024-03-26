#pragma once

#include <vector>
#include <memory>
#include "Player.h"

class LeadBoard{
    std::vector<std::shared_ptr<Player>> m_players;
public:
    LeadBoard() = default;

    void refresh();
    void insert(const std::shared_ptr<Player> player);
    const std::shared_ptr<Player> getTop() const;
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;
};