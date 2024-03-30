#pragma once

namespace Configurations{
    // general setup configurations
    namespace Setup{
        const int MIN_PLAYERS = 2;
        const int MAX_PLAYERS = 6;
    };

    // cards configurations
    namespace Card{
        const int MIN_MONSTERS_IN_GANG = 2;
        const int MIN_CARDS = 2;
    };

    // player configurations
    namespace Player{
        const int MIN_NAME_SIZE = 3;
        const int MAX_NAME_SIZE = 15;

        const int MIN_FORCE = 0;
        const int MIN_DEFAULT_FORCE = 1;

        const int MIN_LEVEL = 1;
        const int MAX_LEVEL = 10;
        
        const int MAX_HP = 100;
        const int STARTING_LEVEL = 1;
        const int STARTING_COINS = 10;
        const int STARTING_FORCE = 5;
    }
}
