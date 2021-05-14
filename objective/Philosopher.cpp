#include "Philosopher.hpp"

Philosopher::Philosopher( int id){
    this->id=id;
}

void Philosopher::startEating(){
    
}

void Philosopher::endEating(){
    this->isDining = false;
    this->thread->join();
}

void Philosopher::takeLeftChopstick(Chopstick *chopstick){
    this->leftChopstick = chopstick;
}

void Philosopher::takeRightChopstick(Chopstick *chopstick){
    this->rightChopstick = chopstick;
}

void Philosopher::releaseLeftChopstick(){
    this->leftChopstick->setAvailable(true);
    this->hasLeft = false;
}

void Philosopher::releaseRightChopstick(){
    this->rightChopstick->setAvailable(true);
    this->hasRight = false;
}

void Philosopher::eat(){

    this->state = EATING;
    std::this_thread::sleep_for(std::chrono::milliseconds(this->eatingTime));
    this->eatingCounter++;
    releaseLeftChopstick();
    releaseRightChopstick();

    this->state = THINKING;
    this->info = "Philosopher: " + std::to_string(this->id) + " is thinking";
    std::this_thread::sleep_for(std::chrono::milliseconds(this->thinkingTime));


}

void Philosopher::startDinning(){
    
    while(this->isDining.load()){

        if(!this->leftChopstick){
            
            if(this->leftChopstick->takeChopstick()){
                printf("Check left\n");
                //this->hasLeft = true;
                //this->info = "Philosopher: " + std::to_string(this->id) + "has taken chopstick: " + std::to_string(this->leftChopstick->getId());
            }
            else{
                //this->state = WAITING;
                //this->info = "Philosopher: " + std::to_string(this->id) + " is waiting";
            }
            
        }
        else if(!this->rightChopstick->takeChopstick()){
            printf("check right");
            /*
            if(this->rightChopstick->takeChopstick()){
                //this->hasRight = true;
                //this->info = "Philosopher: " + std::to_string(this->id) + "has taken chopstick: " + std::to_string(this->rightChopstick->getId());
            }
            else{
                //this->state = WAITING;
                //this->info = "Philosopher: " + std::to_string(this->id) + " is waiting";
            }
            */
        }
        else{
            eat();
        }
    }
}


int Philosopher::getEatingTime(){
    return this->eatingTime;
}

int Philosopher::getWaitingTime(){
    return this->waitingTime;
}

int Philosopher :: getEatingCounter(){
    return this->eatingCounter;
}

int Philosopher::getId(){
    return this->id;
}