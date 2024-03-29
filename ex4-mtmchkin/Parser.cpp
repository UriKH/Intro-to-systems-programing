#include "Parser.h"
#include "Players/playerIncludes.h"

using std::ifstream;

bool parsePlayer(std::ifstream& source, std::vector<std::shared_ptr<Job>>& players, const std::string& name);
bool parseGang(std::ifstream& source, CardDeck& cardDeck);
bool addCard(const std::string& word, CardDeck& cardDeck);

void Parser::parsePlayers(const std::string& fileName, std::vector<std::shared_ptr<Job>>& players){
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

bool parsePlayer(std::ifstream& source, std::vector<std::shared_ptr<Job>>& players, const std::string& name){

    std::string jobName, behaviorName;
    source >> std::skipws >> jobName;
    source >> std::skipws >> behaviorName;

    std::shared_ptr<Job> player;
    std::shared_ptr<Behavior> behavior;
    if (behaviorName == RiskTaking().getName()){
        behavior = std::shared_ptr<RiskTaking>(new RiskTaking());
    }
    else if (behaviorName == Responsible().getName()){
        behavior = std::shared_ptr<Responsible>(new Responsible());
    }
    else{
        return false;
    }

    
    if (jobName == "Sorcerer"){
        player = std::shared_ptr<Job>(new Sorcerer(name, behavior));
    }
    else if (jobName == "Warrior"){
        player = std::shared_ptr<Job>(new Warrior(name, behavior));
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
    std::unique_ptr<Gang> gang(new Gang());
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
            gang->pushBack(std::unique_ptr<Encounter>(new Giant()));
        }
        else if (memberWord == "Dragon"){
            gang->pushBack(std::unique_ptr<Encounter>(new Dragon()));
        }
        else if (memberWord == "Goblin"){
            gang->pushBack(std::unique_ptr<Encounter>(new Goblin()));
        }
        else {
            return false;
        }
        size--;
    }

    cardDeck.insertCard(std::move(gang));
    return true;
}

bool addCard(const std::string& word, CardDeck& cardDeck){
    if(word == "Giant"){
        cardDeck.insertCard(std::unique_ptr<Card>(new Giant()));
    }
    else if(word == "Dragon"){
        cardDeck.insertCard(std::unique_ptr<Card>(new Dragon()));
    }
    else if(word == "Goblin"){
        cardDeck.insertCard(std::unique_ptr<Card>(new Goblin()));
    }
    else if(word == "SolarEclipse"){
        cardDeck.insertCard(std::unique_ptr<Card>(new SolarEclipse()));
    }
    else if(word == "PotionsMerchant"){
        cardDeck.insertCard(std::unique_ptr<Card>(new PotionsMerchant()));
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