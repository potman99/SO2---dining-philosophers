#include "Table.hpp"

void Table::prepareTable(int number){
    
    this->philNumber = number;
    this->keepRunning = true;

    for(int i=0; i<philNumber; i++){
        this->forks.push_back(new Fork(i));
    }

    for(int i=0; i<philNumber; i++){
        this->philosophers.push_back(new Philosopher(i,forks[i],forks[(i + 1) % philNumber]));
    }

   
    displayThread = std::thread(&Table::display, this);
   
}


void Table::endDinner(){

    for(Philosopher* p: this->philosophers){
        
        p->stop();
    }

    keepRunning = false;

}

void Table::display(){

    while (keepRunning)
    {
         for(Philosopher* p: this->philosophers){

                std::string info = stateToString(p->getState());
                
                mvprintw(0,0,"PHILOSOPHERS");
                mvprintw(0,40,"EATING COUNTER");
                mvprintw(0,60,"EATING TIME");
                mvprintw(0,80,"WAITING TIME");
                mvprintw(0,100,"THINKING TIME");
                mvprintw((p->getId()+1)*2, 0,"%d %s", p->getId(), info.c_str());
                clrtoeol();
                mvprintw((p->getId()+1)*2, 40,"eaten %d times", p->getEatingCounter());
                mvprintw((p->getId()+1)*2, 60,"%d ms", p->getEatingTime());
                mvprintw((p->getId()+1)*2, 80,"%d ms", p->getWaitingTime());
                mvprintw((p->getId()+1)*2, 100,"%d ms", p->getThinkingTime());

               
            }

               refresh();
    }
    


            
    
}

void Table::cleanUpDinner(){

    forks.clear();
    philosophers.clear();
    displayThread.join();  
  
}