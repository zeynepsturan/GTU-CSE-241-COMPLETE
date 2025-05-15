#include "robocop.h"

int robocop::count=0; //initializes the count to 0

robocop::robocop():humanic(){
    //body left empty
}

robocop::robocop(int X, int Y, int newStrength, int newHit):humanic(X,Y,newStrength,newHit){
    type="robocop";
    name=generateName(); //generates an unique name and assigns it
    robocop::count++; //increases optimusprime count
}

void robocop::fight(Robot* rival){
    int damage=getDamage(); //creates the damage
    cout<<GetHitMessage1(rival,damage)<<endl; //prints the first hitmessage

    rival->setHitpoint(rival->getHitpoint()-damage); //the damage hits the aimed robot

    if(rival->getHitpoint()<0){ //if hitpoint is below 0
        rival->setHitpoint(0); //sets it to 0
    }
    
    cout<<GetHitMessage2(rival,damage)<<endl; //prints the second hitmessage
}

int robocop::getDamage(){
    int damage;//stores the random created damage
    damage=(rand()%strength)+1; //stores the random created damage

    return damage+humanic::getDamage(); //returns optimusprime damage + extra humanic damage
    
}

string robocop::generateName(){
    string name; //stores the name
    name=this->getType()+"_"+to_string(robocop::count); //<robocop>_<robocop>
    return name; //returns the name
}