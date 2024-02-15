
#include <functional>
#include <string>
#include <iostream>
#include "Player.h"
#include "Card.h"
#include "Mtmchkin.h"

bool testMtmchkin(){ // test number 3
    Card cards[4];
    CardStats stats(3, 40, 10, 30, 1, 20);
    cards[0] = Card(CardType::Treasure, stats);
    cards[1] = Card(CardType::Buff, stats);
    cards[2] = Card(CardType::Battle, stats);
    cards[3] = Card(CardType::Heal, stats);
    Mtmchkin game("Daniel", cards, 4);
    while(!game.isOver()){
        game.playNextCard();
    }
    if (game.getGameStatus()!=GameStatus::Win){
        return false;
    }
    return true;
}

bool testCard(){ // test number 2
    Player player("Efrat",150,2);  //Efrat has 150 max HP and 2 points of force.
    CardStats stats(3, 40, 10, 30, 1, 20);
    Card card1(CardType::Treasure, stats);
    Card card2(CardType::Buff, stats);
    Card card3(CardType::Battle, stats);
    card3.printInfo();
    Card card4(CardType::Heal, stats);
    card1.applyEncounter(player);
    card2.applyEncounter(player);
    card3.applyEncounter(player);
    card4.applyEncounter(player);
    player.printInfo();
    return true;
}

bool testPlayer(){ // test number 1
    Player player1("Efrat",150,2);  //Efrat has 150 max HP and 2 points of force.
    Player player2("Gandalf",300);  //Gandalf has 300 max HP and 5 points of force.
    Player player3("Daniel"); //Gandalf has 100 max HP and 5 points of force.
    player2.printInfo();
    Player player4 = player3;
    player2.addCoins(10);
    if (player1.pay(10)){
        return false;
    }
    player3.heal(10);
    player4.damage(10);
    player2.levelUp();
    player2.buff(1);
    player2.printInfo();
    if (player2.getAttackStrength() != 2 + 6 ){
        return false;
    }
    if (player2.isKnockedOut()){
        std::cout << "Player is dead";
    }
    if (player2.getLevel() != 2){
        return false;
    }
    player1.printInfo();
    player2.printInfo();
    return true;
}



bool testNotEnoughCoins(){ // test number 8
    Player player("Clank",150,2);
    CardStats stats(10, 40, 100, 50, 1, 20);
    Card card1(CardType::Treasure, stats);
    Card card2(CardType::Buff, stats);
    card1.applyEncounter(player);
    card2.applyEncounter(player);
    if (player.getAttackStrength() != 3)
        return false;
    return true;
}

bool testStatusOfGame(){ // test number 7
    Card cards[1];
    CardStats stats(1, 40, 10, 30, 1, 10);
    cards[0] = Card(CardType::Battle, stats);
    Mtmchkin game("Daniel", cards, 1);
    while(!game.isOver()){   
        if (game.getGameStatus()!=GameStatus::MidGame)
            return false;
        game.playNextCard();
    }
    if (game.getGameStatus()!=GameStatus::Win){
        return false;
    }
    return true;
}

bool testHealUpToMaxHP(){ // test number 6
    Player player("Ratchet",150,2);  //Ratchet has 150 max HP and 2 points of force.
    CardStats stats(10, 40, 1, 50, 1, 20);
    Card card1(CardType::Treasure, stats);
    Card card2(CardType::Buff, stats);
    Card card3(CardType::Battle, stats);
    Card card4(CardType::Heal, stats);
    CardStats stats2(10, 150, 1, 30, 1, 20);
    Card card5(CardType::Battle, stats2);

    card1.applyEncounter(player);
    card2.applyEncounter(player);
    card3.applyEncounter(player);
    card4.applyEncounter(player); // should only heal up to 150 and not to 160
    card5.applyEncounter(player);
    player.printInfo();
    if (!player.isKnockedOut())
        return false;
    return true;
    
}

bool testCopyOfCardDeck(){  // test number 5
    Card cards[6];
    CardStats stats(7, 100, 80, 30, 1, 10);
    cards[0] = Card(CardType::Treasure, stats);
    cards[1] = Card(CardType::Treasure, stats);
    cards[2] = Card(CardType::Treasure, stats);
    cards[3] = Card(CardType::Treasure, stats);
    cards[4] = Card(CardType::Buff, stats);
    cards[5] = Card(CardType::Battle, stats);
    Mtmchkin game("Daniel", cards, 6);
    stats.loot = 20;
    cards[0] = Card(CardType::Treasure, stats);
    cards[1] = Card(CardType::Treasure, stats);
    cards[2] = Card(CardType::Treasure, stats);
    cards[3] = Card(CardType::Treasure, stats);
    for (int i = 0; i <6; i++)
        game.playNextCard();
    if (!game.isOver())
        return false;
    return true;
}

bool testPlayerStuff(){ // test number 4
    Player player1("Daniel",1024);
    player1.levelUp();
    player1.levelUp();
    player1.levelUp();
    player1.levelUp();
    if (player1.getLevel() != 5)
        return false;
    if (player1.getAttackStrength() != 10)
        return false;
    player1.addCoins(10);
    if (player1.pay(24))
        return false;
    if (!player1.pay(10))
        return false;
    player1.damage(1000);
    if (player1.isKnockedOut())
        return false;
    // player1.printInfo();
    return true;
}

void run_test(std::function<bool()> test, std::string test_name){
    if(!test()){
        std::cout<<test_name<<" FAILED."<<std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout<<test_name<<" SUCCEEDED."<<std::endl;
    std::cout << std::endl;

}

int main(int argc, char *argv[]) {
    const int NUMBER_OF_TESTS = 8;
    std::function<bool()> tests[NUMBER_OF_TESTS] = {
        testPlayer,
        testCard,
        testMtmchkin,
        // final tests
        testPlayerStuff,
        testCopyOfCardDeck,
        testHealUpToMaxHP,
        testStatusOfGame,
        testNotEnoughCoins
    };

    if (argc < 2) {
        for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
            run_test(tests[i], "Test " + std::to_string(i + 1));
        }
    } else {
        int idx = -1;
        try {
            idx = std::stoi(argv[1]) - 1;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: invalid argument: " << argv[1] << std::endl;
            return 1;
        }
        if (idx < 0 || idx > NUMBER_OF_TESTS - 1) {
            std::cerr << "Error: index out of range: " << argv[1] << std::endl;
            return 1;
        }
        run_test(tests[idx], "Test " + std::to_string(idx + 1));
    }

    return 0;
}
