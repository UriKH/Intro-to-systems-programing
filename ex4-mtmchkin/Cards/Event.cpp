#include "Event.h"

Event::Event(const std::string& name) : m_name(name){}

string Event::getDescription() const{
    return m_name;
}

std::string Event::getName() const{
    return m_name;
}