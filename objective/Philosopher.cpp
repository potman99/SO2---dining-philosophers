#include "Philosopher.hpp"

Philosopher::Philosopher( int id){
    this->id=id;
}

void Philosopher::startEatingThread(){
    thread = std::make_unique<std::thread>([this](){startDinning();});
}

void Philosopher::endEatingThread(){
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
    
    this->hasLeft = false;
    this->leftChopstick->setAvailable(true);
}

void Philosopher::releaseRightChopstick(){

     this->hasRight = false;
    this->rightChopstick->setAvailable(true);
}

void Philosopher::eat(){

    this->state = EATING;
    int eatingTime = rand() % this->time_variable;
    std::this_thread::sleep_for(std::chrono::milliseconds(eatingTime));
    this->eatingTimeCounter += eatingTime;
    this->eatingCounter++;
    releaseLeftChopstick();
    releaseRightChopstick();

    this->state = THINKING;
    this->info = "Philosopher: " + std::to_string(this->id) + " is thinking";
    int thinkingTime = rand() % this->time_variable;
    std::this_thread::sleep_for(std::chrono::milliseconds(thinkingTime));
    this->thinkingTimeCounter += thinkingTime;


}

void Philosopher::startDinning(){
    
    while(this->isDining.load()){

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if(this->leftChopstick->getId() < this->rightChopstick->getId()){

            if(!this->hasLeft){
            
                if(this->leftChopstick->takeChopstick()){
                    this->hasLeft = true;
                    this->info = "Philosopher: " + std::to_string(this->getId()) + " has taken chopstick: " + std::to_string(this->leftChopstick->getId());
                   
                }
                else{
                     this->info = "Philosopher: " + std::to_string(this->getId()) + " is waiting";
                    int waitingTime = rand() % this->time_variable;
                    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
                    this->waitingTimeCounter += waitingTime;
                   
                }
            }
            else if(!this->hasRight){

                if(this->rightChopstick->takeChopstick()){
                    this->hasRight = true;
                    this->info = "Philosopher: " + std::to_string(this->getId()) + " has taken chopstick: "+ std::to_string(this->rightChopstick->getId());
               
                }
                else{
                    this->info = "Philosopher: " + std::to_string(this->getId()) + " is waiting";
                    int waitingTime = rand() % this->time_variable;
                    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
                    this->waitingTimeCounter += waitingTime;

                }
            }
            else{
                this->info = "Philosopher: " + std::to_string(this->getId()) + " is eating";
                eat();
            }
        }
        else{
             if(!this->hasRight){
            
                if(this->rightChopstick->takeChopstick()){
                    this->hasRight = true;
                    this->info = "Philosopher: " + std::to_string(this->getId()) + " has taken chopstick: " + std::to_string(this->rightChopstick->getId());
                   
                }
                else{
                     this->info = "Philosopher: " + std::to_string(this->getId()) + " is waiting";
                    int waitingTime = rand() % this->time_variable;
                    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
                    this->waitingTimeCounter += waitingTime;
                    
                }
            }
            else if(!this->hasLeft){

                if(this->leftChopstick->takeChopstick()){
                    this->hasLeft = true;
                    this->info = "Philosopher: " + std::to_string(this->getId()) + " has taken chopstick: " + std::to_string(this->leftChopstick->getId());
                
                }
                else{
                     this->info = "Philosopher: " + std::to_string(this->getId()) + " is waiting";
                    int waitingTime = rand() % this->time_variable;
                    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
                    this->waitingTimeCounter += waitingTime;
                }
            }
            else{
                this->info = "Philosopher: " + std::to_string(this->getId()) + " is eating";
                eat();
            }
        }

        
    }
}


int Philosopher::getEatingTime(){
    return this->eatingTimeCounter;
}

int Philosopher::getThinkingTime(){
    return this->thinkingTimeCounter;
}

int Philosopher::getWaitingTime(){
    return this->waitingTimeCounter;
}

int Philosopher :: getEatingCounter(){
    return this->eatingCounter;
}

int Philosopher::getId(){
    return this->id;
}

std::string Philosopher::getInfo(){
    return this->info;
}