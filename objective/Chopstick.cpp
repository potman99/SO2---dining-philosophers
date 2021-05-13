#include "Chopstick.hpp"

Chopstick::Chopstick(int priority){
    this->priority = priority;
}

int Chopstick::getPriority(){
    return this->priority;
}

void Chopstick::setAvailable(bool availabilty){

    std::lock_guard<std::mutex> lock(mutex);
    this->available = availabilty;
}

bool Chopstick::takeChopstick(){

    std::lock_guard<std::mutex> lock(mutex);
    if(this->available){
        this->available = false;
        return true;
    }
    else{
        return false;
    }
}