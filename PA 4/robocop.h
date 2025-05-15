#ifndef ROBOCOP_H
#define ROBOCOP_H
#include "humanic.h"

const int ROBOCOP_STRENGTH=30; //robocops strength
const int ROBOCOP_HITPOINT=40; //robocops hitpoint

class robocop:public humanic{
public:
    robocop(); //no parameter constructor
    robocop(int X, int Y, int newStrength, int newHit); //constructor
    
    int getDamage()override; //returns amount of damage this robot inflicts in one round of combat
    void fight(Robot* rival)override; //function to fight with the other robots in the grid
    string generateName()override; //generates an unique name for the robot
    static int count; //stores the number of robocops created
};

#endif