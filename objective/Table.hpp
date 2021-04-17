#pragma once
#include "Philosopher.hpp"
#include "Chopstick.hpp"

class Table
{
private:
    bool isDinner;
public:
    void startDinner();
    void stopDinner();
    bool getIsDinner();
};

