#include "Philosopher.hpp"
#include <ncurses.h>


Philosopher::Philosopher(int _id, Fork* left, Fork* right):
    id(_id),leftFork(left),
    rightFork(right),
    state(States::Wait),
    thread(&Philosopher::run, this),
    keepRunning(true),
    eatingCounter(0),
    eatingTime(0),
    waitingTime(0),
    thinkingTime(0)
    {}



Philosopher::~Philosopher(){
    this->thread.join();
    printf("Philosopher [%d]",id);
}

void Philosopher::run(){

    while (this->keepRunning){

        wait();
        takeForks();
        eat();
        releaseForks();
        think();
    }
    
}

void Philosopher::takeForks(){
    if(this->leftFork->getID() < this->rightFork->getID()){

        this->leftFork->take();
        this->state = States::LeftForkAquired;
        this->rightFork->take();
    }
    else{
        this->rightFork->take();
        this->state = States::RightForkAquired;
        this->leftFork->take();
    }
}


void Philosopher::releaseForks() {
    if(this->leftFork->getID() < this->rightFork->getID()) {
        // release right fork first
        this->rightFork->release();
        this->state = States::LeftForkAquired;
        this->leftFork->release();

    } else {
        // release left fork first
        this->leftFork->release();
        this->state = States::RightForkAquired;
        this->rightFork->release();
    }
}


void Philosopher::stop(){
    this->keepRunning = false;
}

void Philosopher::eat(){
    
    state = States::Eat;
    int time = randomTime();
    this->eatingTime += time/1000;
    eatingCounter++;
    usleep(time);





}

void Philosopher::wait(){

    this->state = States::Wait;
    int time = randomTime();
    this->waitingTime += time/1000;
    usleep(time);
}

void Philosopher::think(){

    this->state = States::Think;
    int time = randomTime();
    this->thinkingTime += time/1000;
    usleep(time);
}

int Philosopher::getId(){
    return id;
}

States Philosopher::getState(){
    return state;
}

int Philosopher::getEatingCounter(){
    return eatingCounter;
}

int Philosopher::getWaitingTime(){
    return waitingTime;
}

int Philosopher::getEatingTime(){
    return eatingTime;
}

int Philosopher::getThinkingTime(){
    return thinkingTime;
}


int Philosopher::randomTime(){
    int randomNumber = (rand() % 3000000) + 2000000;
    return randomNumber;
}