#include <iostream>
#include <stdlib.h>
#include "Chopstick.hpp"
#include "Philosopher.hpp"
#include "Table.hpp"

using namespace std;

int main(){

    Table table;
    int philosophersNumber = 0;
    
    cout<<"Number of philosophers: ";
    cin >> philosophersNumber;

    table.prepareTable(philosophersNumber);
    table.startDinner();

    while(true){
        cout<<"dinner"<<endl;
    }
    table.endDinner();
    

    return 0;
}