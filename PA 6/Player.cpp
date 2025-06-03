#include "Player.h"
#include "exceptions.h"

Player::Player(){
    current=0; //default value for current index
}

Playable* Player::currently_playing(){

    if(list.size()<1){ //if the list is empty
        throw EmptyListError(); //throws an exception
    }
    
    return list[current]; //returns the current media object
}

void Player::previous(mediatype type){
    int size=list.size(); //stores the number of media objects in the list
    int backup_current=current; //stores the current
    bool isFound=false; //flag to check if the media is found

    if(size<1){ //if the list is empty
        throw EmptyListError(); //throws an exception
    }

    int j=1;
    for(int i=0; i<size; i++){ //iterates through the media list in circle once

        if(current-j<0){ //if we get to the beginning
            current=size-1; //returns to the end
            j=0; //returns to the end
        }

        Media* pmedia=dynamic_cast<Media*>(list[current-j]); // casts the previous object to media type

        if(pmedia->getType()==type){ // if they have the same type
            current-=j; // current is updated
            isFound=true;
            break; // breaks the loop
        }

        j++; //j increases
    }

    if(!isFound){ //if an object with the requested type can't be found
        current=backup_current; //current is set to original
        throw MissingTypeError(); //throws an exception
    }
}

void Player::next(mediatype type){
    int size=list.size(); //stores the number of media objects in the list
    int backup_current=current; //stores the current
    bool isFound=false; //flag to check if the media is found

    if(size<1){ //if the list is empty
        throw EmptyListError(); //throws an exception
    }
    
    int j=1;
    for(int i=0; i<size; i++){ //iterates through the media list in circle once

        if(current+j==size){ //if we get to the end
            current=0; //returns to the beginning
            j=0; //returns to the beginning
        }

        Media* nmedia=dynamic_cast<Media*>(list[current+j]); //casts the next object to media type

        if(nmedia->getType()==type){ //if they have the same type
            current+=j; //current is updated
            isFound=true;
            break; //breaks the loop
        }

        j++; //j increases
    }

    if(!isFound){ //if an object with the requested type can't be found
        current=backup_current; //current is set to original
        throw MissingTypeError(); //throws an exception
    }
}

void Player::delete_list(){
    list.clear(); //clears the media list
}

void Player::show_list(){
    int size=list.size(); //stores the list size

    if(size<1){ //if the list is empty
        throw EmptyListError(); //throws an exception
    }
    
    cout<<"Player List:"<<endl; //prints a header

    for(int i=0; i<size; i++){ //iterates through the list
        cout<<i<<". ";
        list[i]->info(); //prints the info of the object
    }
}

void Player::update_list(const vector<Media*>& medialist){
    list.clear(); //deletes the list
    int size=medialist.size(); //stores the number of media objects in the given list

    for(int i=0; i<size; i++){ //iterates through the medias
        
        if(medialist[i]->getType()==mediatype::AUDIO || medialist[i]->getType()==mediatype::VIDEO){ //if the media with the right type is found
            
            Playable* n=dynamic_cast<Playable*>(medialist[i]); //casts it to a playable object
            list.push_back(n); //adds it to the list
            
        }
    }
}