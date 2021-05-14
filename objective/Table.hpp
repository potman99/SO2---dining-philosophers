#pragma once
#include "Philosopher.hpp"
#include "Chopstick.hpp"
#include <vector>
#include <ncurses.h>
#include <string>

class Table
{
private:
    std::atomic_bool isDinner = {true} ;

    std::vector<Philosopher*> philosophers;
    std::vector<Chopstick*> chopsticks;
    std::unique_ptr<std::thread> infoThread;

public:

    void prepareTable(int);
    void startDinner();
    void endDinner();
    

};

