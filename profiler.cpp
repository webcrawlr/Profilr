#include <iostream>
#include <string>
#include "database.h"

using namespace std;

int main(){
    //For starters, let's just create the database.
    int dbSize = 1000;
    generateNewDatabase(dbSize);
    addCreator();
}

