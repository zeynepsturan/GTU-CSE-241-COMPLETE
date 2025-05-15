#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
using namespace std;

class World; //forward declaration of World class

class Robot{
public:
    Robot(); //no parameter constructor
    Robot(int X, int Y, int newStrength, int newHit); //constructor
    
    string getType(){return type;} //returns the robot type
    string getName()const{return name;} //returns the name of the robot
    
    int getStrength()const{return strength;} //returns the strength
    int getHitpoint()const{return hitpoint;} //returns the hitpoint

    void setHitpoint(int hp); //sets the hitpoint
    virtual void heal(); //heals the robot by increasing hitpoint (only for humanic robots)
    void move(World* w ,int& newposX, int& newposY); //function to move in the world

    string GetHitMessage1(Robot* rival, int damage); //creates the hit message and returns it
    string GetHitMessage2(Robot* rival, int damage); //creates the hit message and returns it

    //pure virtual functions since each robot type acts different
    virtual void fight(Robot* rival)=0; //function to fight with the other robots in the grid
    virtual string generateName()=0; //generates an unique name for the robot
    virtual int getDamage()=0; //returns amount of damage this robot inflicts in one round of combat

    void setMoved(bool b); //sets the moved flag
    bool getMoved()const{return moved;} //returns the moved flag

    virtual ~Robot(); //destructor

protected:
    bool moved; //bool to indicate if moved this turn
    string type; //type of the robot
    int strength; //strength of the robot
    int hitpoint; //hitpoint of the robot
    string name; //name of the robot
    int x; //row num of the robot in grid
    int y; //column num of the robot in grid
};
#endif