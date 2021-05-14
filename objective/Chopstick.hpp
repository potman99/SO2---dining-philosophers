#pragma once
#include <mutex>

class Chopstick{

    private:
        
        bool available = true;
        int id;
        std::mutex chopstickMutex;

    public:

        Chopstick(int);
        int getId();
        void setAvailable(bool);
        bool takeChopstick();
    
    

};