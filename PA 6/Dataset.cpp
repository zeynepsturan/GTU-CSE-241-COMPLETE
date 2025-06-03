#include "Dataset.h"
#include <iostream>
using namespace std;

Dataset::Dataset(){
    observers.clear(); //clears the observer list initially
    medias.clear(); //clears the media list initially
}

Dataset::~Dataset(){

    for(auto o:observers){ //iterates through the observers
        delete o; //deletes them one by one
    }

    for(auto m:medias){ //iterates through the media objects
        delete m; //deletes them one by one
    }
}

void Dataset::register_observer(Observer* o){
    bool doesExist=false; //flag to check repetition
    
    for(auto observer:observers){ //iterates through the observers

        if(observer==o){ //if there is repetition
            doesExist=true; //flag is set
            break; //breaks the loop
        }
    }

    if(!doesExist){ //if there is no repetition
        observers.push_back(o); //observer is added to the list
        o->update_list(medias); //updates the added observers media list
    }
}

void Dataset::remove_observer(Observer* o){
    int size=observers.size(); //stores the number of observers

    for(int i=0; i<size; i++){ //iterates through the observers

        if(observers[i]==o){
            observers.erase(observers.begin()+i); //deletes the observer from the list
            break; //breaks the loop
        }
    }
}

void Dataset::remove(Media* m){
    int size=medias.size(); //stores the number of media objects

    for(int i=0; i<size; i++){ //iterates through the media objects

        if(medias[i]==m){ //finds the media
            medias.erase(medias.begin()+i); //deletes it

            mediatype type=m->getType(); //stores the type of the media
            notify(type); //notifies the observers
            break; //breaks the loop
        }
    }
}

void Dataset::notify(mediatype mtype){
    int osize=observers.size(); //stores the number of observers

    if(mtype==mediatype::AUDIO || mtype==mediatype::VIDEO){ //if the change is done in playable objects

        for(int i=0; i<osize; i++){ //iterates through the observers
            
            if(observers[i]->getType()==observertype::PLAYER){ //finds the player type observers
                observers[i]->update_list(medias); //updates it's media list
            }
        }
    }

    else if(mtype==mediatype::TEXT || mtype==mediatype::IMAGE){ //if the change is done in non-playable objects

        for(int i=0; i<osize; i++){ //iterates through the observers
            
            if(observers[i]->getType()==observertype::VIEWER){ //finds the viewer type observers
                observers[i]->update_list(medias);  //updates it's media list
            }
        }
    }
}

void Dataset::add(Media* m){
    bool doesExist=false; //flag to check repetition
    
    for(auto media:medias){ //iterates through the media objects

        if(media==m){ //if there is repetition
            doesExist=true; //flag is set
            break; //breaks the loop
        }
    }

    if(!doesExist){ //if there is no repetition
        medias.push_back(m); //media object is added to the list

        mediatype type=m->getType(); //stores the type of media
        notify(type); //notifies the observers
    }
}