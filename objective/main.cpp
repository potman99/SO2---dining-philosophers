#include <iostream>
#include <stdlib.h>
#include "Chopstick.hpp"
#include "Philosopher.hpp"

using namespace std;

int main(){

    //Chopstick c =  Chopstick(1,99);
    Philosopher p = Philosopher(1);
    cout<<"Hello: "<< p.getId()<<endl;
    p.think();
    cout<<"State: "<<p.getStateString()<<endl;
    //c.getMutex();

    return 0;
}