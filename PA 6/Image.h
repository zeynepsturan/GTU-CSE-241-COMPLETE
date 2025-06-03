#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include "Media.h"
#include "Visual.h"
#include "Non_playable.h"
using namespace std;

class Image:public Non_playable, Visual{
public:
    Image(); //no parameter constructor
    Image(string name, string dimension_inf, string other_inf); //constructor with info parameters
    void info() override; //prints the info about the image object
    mediatype getType() override{return mediatype::IMAGE;} //returns the media type of the object
private:
    string dimension_info; //stores the dimension info
    string other_info; //stores a different info
};
#endif