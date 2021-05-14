#include "Chopstick.hpp"

Chopstick::Chopstick(int id){
    this->id = id;
}

int Chopstick::getId(){
    return this->id;
}

void Chopstick::setAvailable(bool availabilty){

    std::lock_guard<std::mutex> lock(chopstickMutex);
    this->available = availabilty;
}

bool Chopstick::takeChopstick(){
    
     std::lock_guard<std::mutex> lock(chopstickMutex);
    if(this->available){

        
        this->available = false;
        return true;
    }
    else{
        
        return false;
    }


}