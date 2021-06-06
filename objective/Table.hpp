#pragma once
#include "Philosopher.hpp"
#include "Fork.hpp"
#include <thread>
#include <vector>
#include <ncurses.h>
#include <string>

class Table
{
private:
    int philNumber;
    bool keepRunning;
    std::vector<Philosopher*> philosophers;
    std::vector<Fork*> forks;
    std::thread displayThread;
public:
    void prepareTable(int number);
    void endDinner();
    void cleanUpDinner();
    void display();
   
};

