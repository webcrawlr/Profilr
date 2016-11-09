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
#include <time.h>

using namespace std;

struct Person{
	//Displayed attributes
	string name;
	int age; //Not included in the code, to further simulate a facial recognition system.
    int income;
	string gender; //0 = male, 1 = female.  First digit of identifier.
	string race; //White = 0, Hispanic/Latino = 1, Black = 2, Native American = 3, Asian = 4, Islander = 5, Mixed = 6.
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
//---------------------------------------------------------------------------------READING THE DATABASE:
//Function that returns attributes of an ID in a neat array
//Note that IDSize is always 8.
int* spliceID(int ID, int IDSize){
    int splicedID[IDSize] = {0};
    for(int i = IDSize; i > 0; i--){
        splicedID[i] = ID % pow(10,(IDSize-i) + 1)
    }
    return splicedID;
}
string returnAttribute(int number, string choices[]){
    return choices[number]
}
//Attributes should be 8.
string* readID(int ID, int attributes){
    //Elements: Gender(0), race(1), eyecolor(2), haircolor(3).  Hidden attributes, read anyway: chin size(4), eyebrow thickness(5), eye shape(6, and head size(7).
    string IDTranscription[attributes];
    int* splicedID = spliceID(ID, attributes); //We will need to splice the ID as much as our attributes.
    //Options for the elements:
    string gender[2] = {"Male","Female"};
    string race[7] = {"White", "Hispanic/Latino", "Black", "Native American", "Asian", "Pacific Islander", "Mixed"};
    string eyeColor[8] = {"Hazel", "Light brown", "Dark Brown", "Black", "Gray", "Green", "Light Blue", "Blue"};
    string hairColor[4] = {"Brown", "Black", "Blonde", "Red"};
    string chinSize[3] = {"Small", "Medium", "Large"};
    string eyebrowThickness[3] = {"Thin", "Normal", "Thick"};
    string eyeShape[3] = {"Small", "Normal", "Round"};
    string headSize[3] = {"Small", "Medium", "Large"};
    
    //Transcription process
    IDTranscription[0] = returnAttribute(splicedID[0], gender);
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
    
    //Return a person with person described(PROTO)
    return personRead;
}

//---------------------------------------------------------------------------------WRITING THE DATABASE: