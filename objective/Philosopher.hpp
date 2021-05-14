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
        
        int time_variable = 5000;
        int waitingTimeCounter = 0;
        int eatingTimeCounter = 0;
        int thinkingTimeCounter = 0;
        int eatingCounter = 0;
        
        bool hasLeft;
        bool hasRight;
        
        Chopstick* leftChopstick;
        Chopstick* rightChopstick;
        
        std::atomic_bool isDining = {true};
        std::unique_ptr<std::thread> thread;



    public:

        Philosopher(int);
        
        void startEatingThread();
        void endEatingThread();

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
        int getThinkingTime();
        states getState();
        std::string getInfo();
       

};