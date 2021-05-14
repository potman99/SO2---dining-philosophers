#include "Table.hpp"

void Table::prepareTable(int philosophersNumber){
    
    for(int i=0; i<philosophersNumber; i++){
        this->philosophers.push_back(new Philosopher(i));
        this->chopsticks.push_back(new Chopstick(i));
    }

    for(int i=0; i<philosophersNumber; i++){
        this->philosophers[i]->takeLeftChopstick(this->chopsticks[i]);
        this->philosophers[i]->takeRightChopstick(this->chopsticks[(philosophersNumber - 1 + i) % philosophersNumber]);
    }
}

void Table::startDinner(){

    for(Philosopher* p : this->philosophers){
        p->startEatingThread();
    }

    bool isEveroneReady = false;

    while(!isEveroneReady){

        for(Philosopher* p : this->philosophers){

            if(!p->getInfo().empty()) isEveroneReady = true;
            else isEveroneReady = false;
        }
    }
    
    infoThread = std::make_unique<std::thread>([this](){
        while(this->isDinner){
            for(Philosopher* p: this->philosophers){
                
                mvprintw(0,0,"PHILOSOPHERS");
                mvprintw(0,40,"EATING COUNTER");
                mvprintw(0,60,"EATING TIME");
                mvprintw(0,80,"WAITING TIME");
                mvprintw(0,100,"THINKING TIME");
                mvprintw((p->getId()+1)*2, 0,"%s", p->getInfo().c_str());
                clrtoeol();
                mvprintw((p->getId()+1)*2, 40,"eaten %d times", p->getEatingCounter());
                mvprintw((p->getId()+1)*2, 60,"%d ms", p->getEatingTime());
                mvprintw((p->getId()+1)*2, 80,"%d ms", p->getWaitingTime());
                mvprintw((p->getId()+1)*2, 100,"%d ms", p->getThinkingTime());
               
            }
                

                std::this_thread::sleep_for(std::chrono::milliseconds(150));
                refresh();
            }
        
    });
    

    

}

void Table::endDinner(){

    
    for(Philosopher* p : this->philosophers){
        p->endEatingThread();
    }

    this->isDinner = false;
    infoThread->join();

    for(Chopstick* c : this->chopsticks){
        delete c;
    }
}