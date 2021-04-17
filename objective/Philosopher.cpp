#include "Philosopher.hpp"

Philosopher::Philosopher(int id){
    this->id = id;
    this->state = THINKING;
}

void Philosopher::start(){
    std::thread td(&Philosopher::run, this);
}

void Philosopher::run(){

}

void Philosopher::think(){
    std::cout<<"is thinking ";
    wait();
    state = HUNGRY;
}

void Philosopher::eat(){

}

void Philosopher::wait(){
    srand(time(NULL));
    sleep(rand()%sleep_time);
}

std::string Philosopher::getStateString(){

    switch (state)
	{
	case states::HUNGRY:
		return "hungry";
	case states::EATING:
		return "eating";
	case states::THINKING:
		return "thinking";
	}

return "NONE";
}