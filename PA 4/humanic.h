#ifndef HUMANIC_H
#define HUMANIC_H
#include <iostream>
#include <string>
#include "robot.h"
using namespace std;

class humanic:public Robot{
public:
    humanic(); //no parameter constructor
    humanic(int X, int Y, int newStrength, int newHit); //constructor

    int getDamage(); //returns amount of  extra damage humanic robots inflict in one round of combat
    void heal()override; //heals the robot by increasing hitpoint

    //pure virtual functions since each robot type acts different
    virtual string generateName()=0; //generates an unique name for the robot
};

#endif