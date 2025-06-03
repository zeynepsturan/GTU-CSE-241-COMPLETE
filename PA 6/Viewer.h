#ifndef VIEWER_H
#define VIEWER_H
#include "Media.h"
#include "Non_playable.h"
#include "Observer.h"

class Viewer:public Observer{
public:
    Viewer();
    void show_list() override; //shows the view list
    void delete_list() override; //deletes the view list
    void update_list(const vector<Media*>& medialist)override; //updates the viewer list

    void next(mediatype); //views the next object. does not return any object.
    void previous(mediatype); //views the previous object. does not return any object.

    Non_playable* currently_viewing(); //this returns the current object
    observertype getType() override{return observertype::VIEWER;} //returns the type of the observer
    
private:
    vector<Non_playable*>list; //stores the media list that viewer can view from the dataset
    int current; //stores the index of the currently viewed media object
};
#endif