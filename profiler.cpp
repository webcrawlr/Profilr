#include <iostream>
#include <string>
#include "database.h"

using namespace std;

int main(){
    //For starters, let's just create the database.
    int dbSize = 318000000; //Approximate size of the United States;
    generateNewDatabase(dbSize);
    addCreator();
}

