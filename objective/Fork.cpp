#include "Fork.hpp"

Fork::Fork(int forkId):
    id(forkId),inUse(false)
    {}


int Fork::getID(){
    return id;
}

void Fork::take() {

    std::unique_lock<std::mutex> l(this->mutex);

    this->cvInUse.wait(l, [this](){return this->inUse == false;});

    this->inUse = true;

    l.unlock();
}

void Fork::release() {
    std::unique_lock<std::mutex> l(this->mutex);

    this->inUse = false;

    l.unlock();
    this->cvInUse.notify_one();
}


bool Fork::isInUse() {
    return inUse;
}

