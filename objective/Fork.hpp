#pragma once
#include <mutex>
#include <condition_variable>
#include <atomic>

class Fork{

private:
    int id;
    std::mutex mutex;
    std::atomic_bool inUse;
    std::condition_variable cvInUse;


public:

    Fork(int forkId);
    int getID();
    void take();
    void release();
    bool isInUse();


};