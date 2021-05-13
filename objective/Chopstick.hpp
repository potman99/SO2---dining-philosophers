#pragma once
#include <mutex>

class Chopstick{

    private:
        
        bool available = true;
        int priority;
        std::mutex mutex;

    public:

        Chopstick(int);
        int getPriority();
        void setAvailable(bool);
        bool takeChopstick();
    
    

};