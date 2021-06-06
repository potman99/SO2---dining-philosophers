#pragma once
#include "Fork.hpp"
#include "States.hpp"
#include <thread>
#include <atomic>
#include <string>
#include <unistd.h>



class Philosopher
{
private:

    int id;
    int eatingCounter;
    int eatingTime;
    int waitingTime;
    int thinkingTime;
    Fork* leftFork;
    Fork* rightFork;
    std::thread thread;
    States state;
    std::atomic_bool keepRunning;

public:
    Philosopher(int id, Fork* left, Fork* right);
    ~Philosopher();

    void run();
    void eat();
    void wait();
    void think();
    void stop();
    void takeForks();
    void releaseForks();
   
    int getId();
    States getState();
    int getEatingCounter();
    int getWaitingTime();
    int getEatingTime();
    int getThinkingTime();

    int randomTime();
};

