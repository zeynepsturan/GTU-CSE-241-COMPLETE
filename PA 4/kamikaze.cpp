#include "kamikaze.h"

int kamikaze::count=0; //initializes the count to 0

kamikaze::kamikaze():Robot(){
    //body left empty
}

kamikaze::kamikaze(int X, int Y,int newStrength, int newHit):Robot(X,Y,newStrength,newHit){
    type="kamikaze";
    name=generateName(); //generates an unique name and assigns it
    kamikaze::count++; //increases kamikaze count
}

void kamikaze::fight(Robot* rival){
    int damage=getDamage(); //creates the damage
    cout<<GetHitMessage1(rival,damage)<<endl; //prints the first hitmessage

    rival->setHitpoint(rival->getHitpoint()-damage); //the damage hits the aimed robot

    if(rival->getHitpoint()<0){ //if hitpoint is below 0
        rival->setHitpoint(0); //sets it to 0
    }
    setHitpoint(0); //kamikaze dies after it attacks
    cout<<GetHitMessage2(rival,damage)<<endl; //prints the second hitmessage
}

string kamikaze::generateName(){
    string name; //stores the name
    name=this->getType()+"_"+to_string(kamikaze::count); //<kamikaze>_<kamikazecount>
    return name; //returns the name
}

int kamikaze::getDamage(){
    return getHitpoint(); //returns the damage. kamikaze damages as much as its hitpoint
}