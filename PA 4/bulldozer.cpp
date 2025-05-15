#include "bulldozer.h"

int bulldozer::count=0; //initializes the count to 0

bulldozer::bulldozer():Robot(){
    //body left empty
}

bulldozer::bulldozer(int X, int Y,int newStrength, int newHit):Robot(X,Y,newStrength,newHit){
    type="bulldozer";
    name=generateName(); //generates an unique name and assigns it
    bulldozer::count++; //increases bulldozer count
}

void bulldozer::fight(Robot* rival){
    int damage=getDamage(); //creates the damage
    cout<<GetHitMessage1(rival,damage)<<endl; //prints the first hitmessage

    rival->setHitpoint(rival->getHitpoint()-damage); //the damage hits the aimed robot

    if(rival->getHitpoint()<0){ //if hitpoint is below 0
        rival->setHitpoint(0); //sets it to 0
    }
    
    cout<<GetHitMessage2(rival,damage)<<endl; //prints the second hitmessage
}

int bulldozer::getDamage(){
    int damage; //stores the random created damage
    // All robots inflict damage
    damage=(rand()%getStrength())+1; //damage is randomly chosen

    return damage; //returns the damage
}

string bulldozer::generateName(){
    string name; //stores the name
    name=this->getType()+"_"+to_string(bulldozer::count); //<bulldozer>_<bulldozercount>
    return name; //returns the name
}