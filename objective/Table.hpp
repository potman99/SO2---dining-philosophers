#pragma once
#include "Philosopher.hpp"
#include "Chopstick.hpp"
#include <vector>

class Table
{
private:
    std::atomic_bool isDinner = {true} ;

    std::vector<Philosopher*> philosophers;
    std::vector<Chopstick*> chopsticks;

public:

    void prepareTable(int);
    void startDinner();
    void endDinner();
    

};

