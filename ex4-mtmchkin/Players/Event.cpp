#include "Event.h"

Event::Event(const std::string& name):m_name(name){}

string Event::getDescription() const{
    return m_name;
}

void Event::playCard(const Player& player) const{
    
}

std::string Event::getName() const{
    return m_name;
}