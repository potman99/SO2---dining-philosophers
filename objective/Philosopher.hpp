#pragma once
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>

enum states{THINKING,HUNGRY,EATING};

class Philosopher{

    private:
        int id;
        states state;
        std::thread thread;
        int sleep_time = 6;

    public:
        Philosopher(int id);

        void start();
        void run();
        void wait();
        void eat();
        void think();
        std::string getStateString();


        int getId(){
            return id;
        }

        states getState(){
            return state;
        }


};