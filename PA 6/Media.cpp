#include "Media.h"
#include <iostream>
using namespace std;

Media::Media(){
    name=""; //set to empty string
}

Media::Media(string n){
    name=n; //name is set
}

void Media::setName(string n){
    name=n; //name is set
}

string Media::getName()const{
    return name; //returns the name
}