#ifndef ROOMBA_H 
#define ROOMBA_H
#include "robot.h"

const int ROOMBA_STRENGTH=3; //roombas strength
const int ROOMBA_HITPOINT=10; //roombas hitpoint

class roomba:public Robot{
public:
    roomba(); //no parameter constructor
    roomba(int X, int Y, int newStrength, int newHit); //constructor

    int getDamage()override; //returns amount of damage this robot inflicts in one round of combat
    void fight(Robot* rival)override; //function to fight with the other robots in the grid
    string generateName()override; //generates an unique name for the robot
    static int count; //stores the number of roombas created
};
#endif