#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>
#include "Media.h"
using namespace std;

enum class observertype{PLAYER, VIEWER};

class Observer{
public:
    virtual void show_list()=0; //pure virtual function to print the media list of the observer
    virtual void delete_list()=0; //pure virtual function to delete the media list of the observer
    virtual void update_list(const vector<Media*>& medialist)=0; //pure virtual function to update the media list of the observer
    virtual observertype getType()=0; //pure virtual function to return the type of the observer
    virtual ~Observer(){}; //destructor
};
#endif