#pragma once

#include "Encounter.h"

class Gang : public Encounter{
public:
    Gang() : Encounter("Gang", 0, 0, 0, 0){}
    void pushBack(const Encounter& monster); //gets a monster (not gang!), and adds it to the vector
};
