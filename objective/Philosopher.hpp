#pragma once
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <atomic>
#include "Chopstick.hpp"

enum states{THINKING,HUNGRY,EATING};

class Philosopher{

    private:
        int id;
        states state;
        
        int sleep_time = 6;
        int eating_time = 6;
        
        bool hasLeft;
        bool hasRight;
        
        Chopstick* leftChopstick;
        Chopstick* rightChopstick;
        
        std::atomic_bool isEating = {true};
        std::unique_ptr<std::thread> thread;



    public:
       

};