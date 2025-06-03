#ifndef DATASET_H
#define DATASET_H
#include <vector>
#include "Observer.h"
#include "Media.h"

class Dataset{
public:
    Dataset(); //no parameter constructor
    ~Dataset(); //destructor
    void register_observer(Observer* o); //adds the new observer to the dataset
    void remove_observer(Observer* o); //removes an observer from the dataset
    void remove(Media* m); //removes a media object from the dataset
    void add(Media* m); //adds the new media object to the dataset
private:
    void notify(mediatype mtype); //helper function to notify all the observers by spesific type
    vector<Observer*> observers; //stores the observers
    vector<Media*> medias; //stores the media objects
};
#endif