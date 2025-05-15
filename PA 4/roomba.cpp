#include "roomba.h"

int roomba::count=0; //initializes the count to 0

roomba::roomba():Robot(){
    //body left empty
}

roomba::roomba(int X, int Y,int newStrength, int newHit):Robot(X,Y,newStrength,newHit){
    type="roomba";
    name=generateName(); //generates an unique name and assigns it
    roomba::count++; //increases optimusprime count
}

void roomba::fight(Robot* rival){
    
    for(int i=0; i<2; i++){ //roomba attacks 2 so there is this loop
        int damage=getDamage(); //creates the damage
        cout<<GetHitMessage1(rival,damage)<<endl; //prints the first hitmessage

        rival->setHitpoint(rival->getHitpoint()-damage); //the damage hits the aimed robot

        if(rival->getHitpoint()<0){ //if the rival robot is died
            rival->setHitpoint(0); //sets its hitpoint to 0
            return; //ends the loop and the function
        }
        
        cout<<GetHitMessage2(rival,damage)<<endl; //prints the second hitmessage
    }
}

string roomba::generateName(){
    string name; //stores the name
    name=this->getType()+"_"+to_string(roomba::count); //<roomba>_<roombacount>
    return name; //returns the name
}

int roomba::getDamage(){
    int damage; //stores the random created damage
    damage=(rand()%getStrength())+1; //stores the random created damage

    return damage; //returns the damage
}