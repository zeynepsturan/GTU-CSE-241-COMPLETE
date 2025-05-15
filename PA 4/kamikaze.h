#ifndef KAMIKAZE_H
#define KAMIKAZE_H
#include "robot.h"

const int KAMIKAZE_STRENGTH=10; //kamikazes strength
const int KAMIKAZE_HITPOINT=10; //kamikazes hitpoint

class kamikaze:public Robot{
public:
    kamikaze(); //no parameter constructor
    kamikaze(int X, int Y, int newStrength, int newHit); //constructor

    int getDamage()override; //returns amount of damage this robot inflicts in one round of combat
    void fight(Robot* rival)override; //function to fight with the other robots in the grid
    string generateName()override; //generates an unique name for the robot
    static int count; //stores the number of kamikazes created
};

#endif