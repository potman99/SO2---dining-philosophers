#include "Chopstick.hpp"

Chopstick::Chopstick(int chopstickId, int ownerId){
    id = chopstickId;
    owner = ownerId;
    dirty = true;
}

void Chopstick::askForChopstick(int ownerId){

    while (owner != ownerId)
    {
        if(dirty){
            std::scoped_lock<std::mutex> lock(mutex);
            dirty = false;
            owner = ownerId;

        }

        else{
            
        }
    }
    
}