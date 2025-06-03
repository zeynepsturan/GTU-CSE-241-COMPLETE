#ifndef AUDIO_H
#define AUDIO_H
#include<iostream>
#include "Media.h"
#include "Playable.h"
#include "Non_visual.h"
using namespace std;

class Audio:public Playable, Non_visual{
public:
    Audio(); //no parameter constructor
    Audio(string name, string duration, string other_info); //constructor with info parameters
    void info() override; //prints the info about the audio object
    mediatype getType() override{return mediatype::AUDIO;} //returns the media type of the object
private:
    string duration; //stores the duration info
    string other_info; //stores a different info
};

#endif