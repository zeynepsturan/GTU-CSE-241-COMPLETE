#ifndef VIDEO_H
#define VIDEO_H
#include<iostream>
#include "Media.h"
#include "Visual.h"
#include "Playable.h"
using namespace std;

class Video:public Playable, Visual{
public:
    Video(); //no parameter constructor
    Video(string name, string dur, string other_inf); //constructor with info parameters
    void info() override; //prints the info about the video object
    mediatype getType() override{return mediatype::VIDEO;} //returns the media type of the object
private:
    string duration; //stores the duration info
    string other_info; //stores a different info
};
#endif