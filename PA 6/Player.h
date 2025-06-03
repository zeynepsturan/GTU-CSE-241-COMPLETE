#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Observer.h"
#include "Playable.h"
#include "Media.h"

class Player:public Observer{
public:
    Player(); //no parameter constructor
    void show_list() override; //shows the play list
    void delete_list() override; //deletes the play list
    void update_list(const vector<Media*>& medialist)override; //updates the player list

    void next(mediatype type); //plays the next object. does not return any object.
    void previous(mediatype type); //plays the previous object. does not return any object.

    Playable* currently_playing(); //this returns the current object
    observertype getType() override{return observertype::PLAYER;} //returns the type of the observer
    
private:
    vector<Playable*>list; //stores the media list that player can play from the dataset
    int current; //stores the index of the currently playing media object
};
#endif