#pragma once
#include <mutex>

class Chopstick{

    private:
        int id;
        int owner;
        bool dirty = true;
        std::mutex mutex;

    public:
        Chopstick(int chopstickId, int ownerId);
        void finishMeal();
        void askForChopstick(int ownerId);

        std::mutex& getMutex(){
            return mutex;
        }

        int getId(){
            return id;
        }

        int getOwner(){
            return owner;
        }

    

};