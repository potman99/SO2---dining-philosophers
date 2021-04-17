#include "Table.hpp"

void Table::startDinner(){
    isDinner = true;
}

void Table::stopDinner(){
    isDinner = false;
}

bool Table::getIsDinner(){
    return isDinner;
}