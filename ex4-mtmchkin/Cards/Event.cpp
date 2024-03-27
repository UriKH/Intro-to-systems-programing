#include "Event.h"

Event::Event(const std::string& name):m_name(name){}

string Event::getDescription() const{
    return m_name;
}

int Event::playCard(const Player& player) const{
    return 1;
}

std::string Event::getName() const{
    return m_name;
}