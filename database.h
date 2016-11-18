/*
    Writer: Raymond Muller
    Part of the Profiler Project.
    This module deals with the reading and writing of the database.
    FUTURE UPDATES:  
    Error handling for strange IDs?  Given that we are getting attributes, shouldn't be a problem, but still.
    Optimize program.
*/

#include <cstdlib>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>
#include "profile.h"

using namespace std;

struct Person{
	//Displayed attributes
	string name;
	int age; //Not included in the code, to further simulate a facial recognition system.
    int income;
	string gender; //1 = male, 2 = female.  First digit of identifier.
	string race; //White = 0, Hispanic/Latino = 1, Black = 2, Native American = 3, Asian = 4, Islander = 5, Middle Eastern = 6, Mixed = 7.
	string eyeColor; //Hazel = 0, light brown = 1, dark brown = 2, black = 3, gray = 4, green = 5, light blue = 6, blue = 7.
    string hairColor; //Brown = 0, black = 1, blonde = 2, red = 3.
	string occupation;
	string fact;
	//Hidden attributes.   Added to the end of the string to match to people, but not returned by normal user calls.
	string chinSize; //0 - 2.
    string eyebrowThickness; //0-2.
    string eyeShape; //0-2.
    string headSize; //0-2.
    //int headShape; //Closed out for less posibilities in prototype
    //Unique id: Go down line.  Example, Native American female with hazel eyes, black hair, midsize chin, thin eyebrows, round eye shape, and medium head: 13011021.
};

//Truncated person, for getting database values
struct tPerson{
    int id;
    string name;
    string fact;
    int age;
    string occupation;
    int income;
};
struct IDGenerated{
    //Storage of IDs to make sure that all people are unique
    int id;
    IDGenerated* next; //Next link
};

const int ATTRIBUTE_SIZE = 8; //Number of attributes.
int attributeChoices[ATTRIBUTE_SIZE] = {2,8,8,4,3,3,3,3};
//---------------------------------------------------------------------------------READING THE DATABASE:
//Function that returns attributes of an ID in a neat array
//Note that IDSize is always 8.
int* spliceID(int ID, const int IDSize){
    int splicedID[IDSize];
    for(int i = IDSize; i > 0; i--){
        int digitPlace = pow(10,(IDSize-i) + 1);
        int thisID = (ID % digitPlace);
        thisID /= digitPlace;
        splicedID[i] = thisID;
    }
    return splicedID;
}
string returnAttribute(int number, string choices[]){
    return choices[number];
}
//Attributes should be 8.
string* readID(int ID, const int ATTRIB){
    //Elements: Gender(0), race(1), eyecolor(2), haircolor(3).  Hidden attributes, read anyway: chin size(4), eyebrow thickness(5), eye shape(6, and head size(7).
    const int attributes = 8;
    string IDTranscription[attributes];
    int* splicedID = spliceID(ID, attributes); //We will need to splice the ID as much as our attributes.
    //Options for the elements:
    string gender[2] = {"Male","Female"};
    string race[8] = {"White", "Hispanic/Latino", "Black", "Native American", "Asian", "Pacific Islander", "Middle Eastern", "Mixed"}; //Ethnicities are as classified by the BetaFace facial recognition system.
    string eyeColor[8] = {"Hazel", "Light brown", "Dark Brown", "Black", "Gray", "Green", "Light Blue", "Blue"};
    string hairColor[4] = {"Brown", "Black", "Blonde", "Red"};
    string chinSize[3] = {"Small", "Medium", "Large"};
    string eyebrowThickness[3] = {"Thin", "Normal", "Thick"};
    string eyeShape[3] = {"Small", "Normal", "Round"};
    string headSize[3] = {"Small", "Medium", "Large"};
    
    //Transcription process
    IDTranscription[0] = returnAttribute(splicedID[0] - 1, gender); //Gender is the unique exception, due to leading zeroes resulting in bad IDs
    IDTranscription[1] = returnAttribute(splicedID[1], race);
    IDTranscription[2] = returnAttribute(splicedID[2], eyeColor);
    IDTranscription[3] = returnAttribute(splicedID[3], hairColor);
    IDTranscription[4] = returnAttribute(splicedID[4], chinSize);
    IDTranscription[5] = returnAttribute(splicedID[5], eyebrowThickness);
    IDTranscription[6] = returnAttribute(splicedID[6], eyeShape);
    IDTranscription[7] = returnAttribute(splicedID[7], headSize);
    return IDTranscription;
}

//Return a person from a predetermined database.
Person readPerson(string name, int age, string occupation, string fact, int income, int ID){
    //read ID
    string* IDTranscript = readID(ID, 8); //Remember that there are 8 attributes
    Person personRead;
    personRead.name = name;
    personRead.age = age;
    personRead.income = income;
    personRead.occupation = occupation;
    personRead.fact = fact;
    personRead.gender = IDTranscript[0];
    personRead.race = IDTranscript[1];
    personRead.eyeColor = IDTranscript[2];
    personRead.hairColor = IDTranscript[3];
    personRead.chinSize = IDTranscript[4];
    personRead.eyebrowThickness = IDTranscript[5];
    personRead.eyeShape = IDTranscript[6];
    personRead.headSize = IDTranscript[7];
    
    //Return a person with person described
    return personRead;
}

//Search database for the entries, then get a "truncated Person"
tPerson readDatabase(int ID){
    tPerson personScanned;
    //First, try to find the exact value
    bool foundID = false;
    fin.open("database.txt");
    while(!foundID && fin.good()){
        //Check for id
        fin.ignore(1000,10); //Skip the ---------- separator
        fin >> currentRead;
        if(currentRead == ID){
            foundID = true;
            //Get the information
            fin.ignore(1000,10);
            fin >> currentRead;
            //That's the name:
            personScanned.name = currentRead;
            fin.ignore(1000,10);
            fin >> currentRead;
            //That's the fact:
            personScanned.fact = currentRead;
            fin.ignore(1000,10);
            fin >> currentRead;
            //That's the age:
            personScanned.age = currentRead;
            fin.ignore(1000,10);
            fin >> currentRead;
            //That's the occupation
            personScanned.occupation = currentRead;
            fin.ignore(1000,10);
            fin >> currentRead;
            //That's the income:
            personScanned.income = currentRead;
            //That's all we need, close shop.
            fin.close();
        }
        else{
            //Not the right ID, skip 7, to the next ID.
            for(int i = 0; i < 7; i++){
                fin.ignore(1000,10);
                linesIn++;
            }
        }
    }
    fin.close();
    //If the ID wasn't found, create one.  Backstory: We imported value from ctOS.
    if(!foundID){
        //Append to the database.
        ofstream fout;
        fout.open("database.txt", ios::app);
        int genderVal = ID / 10000000;
        int raceVal = (ID % 10000000) / 1000000;
        fout << "----------" << endl;
        //Write the ID
        fout << ID << endl;
        //Then: the Name
        string name = generateName(genderVal, raceVal);
        fout << name << endl;
        //Then: Fact
        string fact = generateFact();
        fout << fact << endl;
        //Then: Age
        int age = (rand() % 53 + 18);
        fout << age << endl; //Generates age ranging from 18 to 70.
        //Then: Occupation
        string occupation = generateOccupation();
        fout << occupation << endl;
        //Then: Income
        int income = (rand() % 315000 + 15080); 
        fout << income << endl;
        
        //Now, after all that is said and done, return the values.
        personScanned.name = name;
    }

}
//---------------------------------------------------------------------------------WRITING THE DATABASE:
//Generate a person's ID:
int generateID(int numAttributes, int idChoices[]){
    srand(time(NULL));
    int generatedID = 0;
    /*
    for(int i = 0; i < numAttributes; i++){
        int numberToAdd = ((rand() % idChoices[i]) * (pow(10,(numAttributes - i) - 1)));
        cout << "Digit " << i << ": " << numberToAdd << endl;
        generatedID += numberToAdd; //Will add digits to the array within parameters 
        cout <<"ID Now: " << generatedID << endl;
    }
    */
    //Do it manually, do to numerous glitches, including not enough digits being produced
    generatedID += (rand() % 2 + 1) * 10000000;
    generatedID += (rand() % 8) * 1000000;
    generatedID += (rand() % 8) * 100000;
    generatedID += (rand() % 4) * 10000;
    generatedID += (rand() % 3) * 1000;
    generatedID += (rand() % 3) * 100;
    generatedID += (rand() % 3) * 10;
    generatedID += (rand() % 3) * 1;
    return generatedID;
}
//Create the initial database
void createDatabase(){
    ofstream fout;
    fout.open("database.txt");
    fout.close();
}
//Generate people into the database.
//dbSize should be 318000000 when called.
void generateNewDatabase(int dbSize){
    //Initialize starter database
    createDatabase();
    //Get ready to add things
    ofstream fout;
    fout.open("database.txt", ios::app);
    //Create a new start link for ID list.
    IDGenerated* start = 0;
    int people = 0;
    while(people < dbSize){
        bool clear = true;
        int newID = generateID(ATTRIBUTE_SIZE, attributeChoices);
        //Compare to the linked list, to make sure that there is no repeat ID.
        //Note that the ID 07002211 is reserved for the creator of the program.
        IDGenerated* i;
        for(i = start; i; i = i -> next){
            if(i->id == newID || newID == 07002211){
                clear = false;
                //Don't allow it to continue
            }
        }
        //Now, if the ID was cleared, you can add that to the Database
        if(clear){
            //First, add to the linked list
            IDGenerated* thisID = new IDGenerated;
            thisID->id = newID;
            thisID->next = start;
            start = thisID;
            //cout << "ID generated: " << newID << endl;
            //Now, generate profile.
            //int newSplicedID = spliceID(newID, ATTRIBUTE_SIZE);
            //Generate manually due to glitches in spliceID.
            int genderVal = newID / 10000000;
            int raceVal = (newID % 10000000) / 1000000;
            //First: the ten dashes
            fout << "----------" << endl;
            //Then: the ID
            fout << newID << endl;
            //Then: the Name
            fout << generateName(genderVal, raceVal) << endl;
            //Then: Fact
            fout << generateFact() << endl;
            //Then: Age
            fout << (rand() % 53 + 18) << endl; //Generates age ranging from 18 to 70.
            //Then: Occupation
            fout << generateOccupation() << endl;
            //Then: Income
            fout << (rand() % 315000 + 15080) << endl;
        }
    }
}
//Add the Program's creator to the databse ;-)
void addCreator(){
    ofstream fout;
    fout.open("database.txt", ios::app);
    fout << "----------" << endl;
    fout << 17002211 << endl;
    fout << "Raymond Muller" << endl;
    fout << "Creator of the Program" << endl;
    fout << 14 << endl;
    fout << "Student" << endl;
    fout << "133747234" << endl;
}
