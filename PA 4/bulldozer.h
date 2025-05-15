#ifndef BULLDOZER_H
#define BULLDOZER_H
#include "robot.h"

const int BULLDOZER_STRENGTH=50; //bulldozers strength
const int BULLDOZER_HITPOINT=200; //bulldozers hitpoint

class bulldozer:public Robot{
public:
    bulldozer(); //no parameter constructor
    bulldozer(int X, int Y, int newStrength, int newHit); //constructor

    int getDamage() override; //returns amount of damage this robot inflicts in one round of combat
    void fight(Robot* rival)override; //function to fight with the other robots in the grid
    string generateName() override; //generates an unique name for the robot
    static int count; //stores the number of bulldozers created
};

#endif