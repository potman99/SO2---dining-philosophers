#pragma once
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <atomic>
#include "Chopstick.hpp"


enum states{THINKING,WAITING,EATING};

class Philosopher{

    private:
        int id;
        states state;
        std::string info;
        
        int waitingTime = 6;
        int eatingTime = 6;
        int thinkingTime = 6;
        int eatingCounter = 0;
        
        bool hasLeft;
        bool hasRight;
        
        Chopstick* leftChopstick;
        Chopstick* rightChopstick;
        
        std::atomic_bool isDining = {true};
        std::unique_ptr<std::thread> thread;



    public:

        Philosopher(int);
        
        void startEating();
        void endEating();

        void takeLeftChopstick(Chopstick*);
        void takeRightChopstick(Chopstick*);

        void releaseLeftChopstick();
        void releaseRightChopstick();
        void startDinning();
        void eat();

        int getId();
        int getEatingCounter();
        int getWaitingTime();
        int getEatingTime();
        states getState();
       

};