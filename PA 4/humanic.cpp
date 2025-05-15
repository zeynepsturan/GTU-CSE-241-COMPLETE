#include "humanic.h"

humanic::humanic():Robot(){
    //body left empty
}

humanic::humanic(int X, int Y, int newStrength, int newHit):Robot(X,Y, newStrength, newHit){
    //body left empty
}

void humanic::heal(){
    hitpoint++; //increases the hitpoint
}

int humanic::getDamage(){
    int random=rand()%100; //creates a random number between 0-99 for luck

    if(random<15){ //15% chance of extra damage
        return 40; //returns extra damage
    }

    return 0; //85% chance of no extra damage
}