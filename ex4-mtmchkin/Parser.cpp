#include "Parser.h"
#include "Players/playerIncludes.h"

using std::ifstream;

bool parsePlayer(std::ifstream& source, std::vector<std::shared_ptr<Player>>& players, const std::string& name);
bool parseGang(std::ifstream& source, CardDeck& cardDeck);
bool addCard(const std::string& word, CardDeck& cardDeck);

void Parser::parsePlayers(const std::string& fileName, std::vector<std::shared_ptr<Player>>& players){
    ifstream source(fileName);
    if(!source){    
        throw InvalidPlayersFile();
    }

    int playersCounter = 0;
    std::string name;
    while (source >> std::skipws >> name) {
        if (!parsePlayer(source, players, name)){
            throw InvalidPlayersFile();
        }
        playersCounter++;
    }

    if(playersCounter > 6 && playersCounter < 2){
        throw InvalidPlayersFile();
    }
}

bool parsePlayer(std::ifstream& source, std::vector<std::shared_ptr<Player>>& players, const std::string& name){

    std::string jobName, behaviorName;
    source >> std::skipws >> jobName;
    source >> std::skipws >> behaviorName;

    std::shared_ptr<Player> player;
    std::shared_ptr<Behavior> behavior;
    if (behaviorName == RiskTaking().getName()){
        behavior = std::shared_ptr<RiskTaking>();
    }
    else if (behaviorName == Responsible().getName()){
        behavior = std::shared_ptr<Responsible>();
    }
    else{
        return false;
    }

    
    if (jobName == "Sorcerer"){
        player = std::shared_ptr<Sorcerer>(new Sorcerer(name, behavior));
    }
    else if (jobName == "Warriror"){
        player = std::shared_ptr<Warrior>(new Warrior(name, behavior));
    }
    else{
        return false;
    }

    players.push_back(player);
    return true;
}

void Parser::parseCards(const std::string& fileName, CardDeck &cardDeck){
    ifstream source(fileName);
    if(!source){    
        throw InvalidCardsFile();
    }

    std::string word;
    while (source >> std::skipws >> word) {
        if (word == "Gang") {
            if (!parseGang(source, cardDeck)){
                throw InvalidCardsFile();
            }
        }
        else if (!addCard(word, cardDeck)){
            throw InvalidCardsFile();
        }
    }
}

bool parseGang(std::ifstream& source, CardDeck& cardDeck) {
    std::unique_ptr<Gang> gang;
    int size;
    if (!(source >> size)) {
        return false;
    }

    while (size > 0) {
        std::string memberWord;
        if (!(source >> memberWord)) {
            return false;
        }
        if (memberWord == "Gang") {
            int nestedSize;
            if (!(source >> nestedSize)) {
                return false;
            }
            size += nestedSize - 1;
        }
        else if (memberWord == "Giant"){
            Giant giant;
            gang->pushBack(giant);
        }
        else if(memberWord == "Dragon"){
            Dragon dragon;
            gang->pushBack(dragon);
        }
        else if(memberWord == "Goblin"){
            Dragon dragon;
            gang->pushBack(dragon);
        }
        else {
            return false;
        }
        size--;
    }
    cardDeck.insertBack(std::move(gang));
    return true;
}

bool addCard(const std::string& word, CardDeck& cardDeck){
    if(word == "Giant"){
        std::unique_ptr<Giant> giant;
        cardDeck.insertBack(std::move(giant));
    }
    else if(word == "Dragon"){
        std::unique_ptr<Dragon> dragon;
        cardDeck.insertBack(std::move(dragon));
    }
    else if(word == "Goblin"){
        std::unique_ptr<Goblin> goblin;
        cardDeck.insertBack(std::move(goblin));
    }
    else if(word == "SolarEclipse"){
        std::unique_ptr<SolarEclipse> solarEclipse;
        cardDeck.insertBack(std::move(solarEclipse));
    }
    else if(word == "PotionsMerchant"){
        std::unique_ptr<PotionsMerchant> potionsMerchant;
        cardDeck.insertBack(std::move(potionsMerchant));
    }
    else {
        return false;
    }
    return true;
}

const char* Parser::InvalidCardsFile::what() const noexcept{
    return "Invalid Cards File";
}

const char* Parser::InvalidPlayersFile::what() const noexcept{
    return "Invalid Players File";
}