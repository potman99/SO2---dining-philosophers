#include "Table.hpp"

void Table::prepareTable(int philosophersNumber){
    
    for(int i=0; i<philosophersNumber; i++){
        this->philosophers.push_back(new Philosopher(i));
        this->chopsticks.push_back(new Chopstick(i));
    }
}

void Table::startDinner(){

    for(Philosopher* p : this->philosophers){
        p->startDinning();
    }

    

}

void Table::endDinner(){


}