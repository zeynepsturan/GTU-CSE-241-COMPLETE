#ifndef TEXT_H
#define TEXT_H
#include <string>
#include "Media.h"
#include "Non_playable.h"
#include "Non_visual.h"
using namespace std;

class Text:public Non_playable, Non_visual{
public:
    Text(); //no parameter constructor
    Text(string name, string other_inf); //constructor with info parameters
    void info() override; //prints the info about the text object
    mediatype getType() override{return mediatype::TEXT;} //returns the media type of the object

private:
    string other_info; //stores a different info
};
#endif