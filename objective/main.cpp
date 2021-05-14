#include <iostream>
#include <stdlib.h>
#include "Chopstick.hpp"
#include "Philosopher.hpp"
#include "Table.hpp"
#include <ncurses.h>
//#include <time.h>


using namespace std;

int main(){

    srand(time(NULL));

    Table table;
    int philosophersNumber;

    cout<<"Enter number of dinning philosophers:";
    cin >> philosophersNumber;

    cout<<"Number: "<<philosophersNumber;


  
    table.prepareTable(philosophersNumber);

    

    initscr();
    table.startDinner();

    int c;
    while((c=getch()) != 27){
        
    }
    endwin();
    table.endDinner();
    

    return 0;
}