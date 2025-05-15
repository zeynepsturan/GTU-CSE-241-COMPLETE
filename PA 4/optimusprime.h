#ifndef OPTIMUSPRIME_H
#define OPTIMUSPRIME_H
#include "humanic.h"
#include "world.h"

const int OPTIMUSPRIME_STRENGTH=100; //optimusprimes strength
const int OPTIMUSPRIME_HITPOINT=100; //optimusprimes hitpoint

class optimusprime:public humanic{
public:
    optimusprime(); //no parameter constructor
    optimusprime(int X, int Y, int newStrength, int newHit); //constructor

    int getDamage()override; //returns amount of damage this robot inflicts in one round of combat
    void fight(Robot* rival)override; //function to fight with the other robots in the grid
    string generateName()override; //generates an unique name for the robot
    static int count; //stores the number of optimusprimes created
};

#endif