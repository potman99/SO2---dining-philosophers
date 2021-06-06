#include <stdio.h>
#include "Table.hpp"
#include <ncurses.h>


int main(int argc, char const *argv[])
{
    srand((unsigned) time(0));


    printf("Elo");
    int number = 10;
    Table table;

    initscr();
    cbreak();
    noecho();
    table.prepareTable(number);

    while (getch() != 27) {
        
    }
    endwin();



    table.endDinner();
    table.cleanUpDinner();
    printf("END");
    
    return 0;
}
