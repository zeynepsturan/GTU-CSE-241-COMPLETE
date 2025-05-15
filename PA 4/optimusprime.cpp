#include "optimusprime.h"

int optimusprime::count=0; //initializes the count to 0

optimusprime::optimusprime():humanic(){
    //body left empty
}

optimusprime::optimusprime(int X, int Y,int newStrength, int newHit):humanic(X,Y,newStrength,newHit){
    type="optimusprime";
    name=generateName(); //generates an unique name and assigns it
    optimusprime::count++; //increases optimusprime count
}

int optimusprime::getDamage(){
    int damage; //stores the damage
    int random; //stores a random number

    damage=(rand()%strength)+1; //random damage
    random=rand()%100; //creates a random number between 0-99 for luck

    if(random<20){ //20% chance of double damage
        damage*=2; //doubles the damage
    }

    return damage+humanic::getDamage(); //returns optimusprime damage + extra humanic damage
}

void optimusprime::fight(Robot* rival){

    int damage=getDamage(); //creates the damage
    cout<<GetHitMessage1(rival,damage)<<endl; //prints the first hitmessage

    rival->setHitpoint(rival->getHitpoint()-damage); //the damage hits the aimed robot

    if(rival->getHitpoint()<0){ //if hitpoint is below 0
        rival->setHitpoint(0); //sets it to 0
    }
    
    cout<<GetHitMessage2(rival,damage)<<endl; //prints the second hitmessage
}

string optimusprime::generateName(){
    string name; //stores the name
    name=type+"_"+to_string(optimusprime::count); //<optimusprime>_<optimusprimecount>
    return name; //returns the name
}