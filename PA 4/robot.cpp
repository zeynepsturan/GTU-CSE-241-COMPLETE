#include "robot.h"
#include "world.h"

Robot::Robot(int X, int Y, int newStrength, int newHit){
    x=X;    //all assignments are done
    y=Y;
    strength=newStrength;
    hitpoint=newHit;
}

Robot::Robot(){
    type="unknown"; //assigns unvalid values for each data member
    strength=-1;
    hitpoint=-1;
    name="";
    x=-1;
    y=-1;
}

string Robot::GetHitMessage1(Robot* rival, int damage){
    string message=
        name + "(" + to_string(hitpoint) + ") hits "+rival->getName() + "(" +
        to_string(rival->getHitpoint()) + ") with " + to_string(damage); //message is set

    return message; //returns the message
}

string Robot::GetHitMessage2(Robot* rival, int damage){
    string message="The new hitpoints of " + rival->getName() + " is " + to_string(rival->getHitpoint()); //message is set
    return message; //returns the message
}

void Robot::setHitpoint(int hp){
    hitpoint=hp; //hitpoint is assigned
}

void Robot::heal(){
    //body left empty
}

void Robot::setMoved(bool b){
    moved=b; //moved is set
}

void Robot::move(World* w, int& newposX, int& newposY){
    bool flag=false; //flag to check if we entered the loop
    if(!moved) flag=true; //it'll enter the loop so flag is true now

    while(!moved){
        // Pick random direction to move
        int dir=rand()%4; //random direction (up,down,right,left)

        if(dir==0){ //try to move up
            
            if(y>0){ //boundry control

                if(w->getAt(x,y-1)!=nullptr){ //if there is a robot in the cell
                    moved=true; //sets the moved
                    w->fightLoop(x,y,x,y-1); //robots fight with each other
                }

                else{
                    w->setAt(x,y-1,this); //move to new spot
                    w->setAt(x,y,nullptr); //set current spot to empty
                    y--; //updates the position
                }
            }
        }

        else if(dir==1){ //try to move down

            if(y<WORLDSIZE-1){ //boundry control
                
                if(w->getAt(x,y+1)!=nullptr){ //if there is a robot in the cell
                    moved=true; //sets the moved
                    w->fightLoop(x,y,x,y+1); //robots fight with each other
                }

                else{
                    w->setAt(x,y+1,w->getAt(x,y)); //move to new spot
                    w->setAt(x,y,nullptr); //set current spot to empty
                    y++; //updates the position
                }
            }
        }

        else if(dir==2){ //try to move left

            if(x>0){ //boundry control

                if(w->getAt(x-1,y)!=nullptr){ //if there is a robot in the cell
                    moved=true; //sets the moved
                    w->fightLoop(x,y,x-1,y); //robots fight with each other

                }

                else{
                    w->setAt(x-1,y,w->getAt(x,y)); //move to new spot
                    w->setAt(x,y,nullptr); //set current spot to empty
                    x--; //updates the position
                }
            }
        }

        else{ //try to move right

            if(x<WORLDSIZE-1){ //boundry control

                if(w->getAt(x+1,y)!=nullptr){ //if there is a robot in the cell
                    moved=true; //sets the moved
                    w->fightLoop(x,y,x+1,y); //robots fight with each other
                }

                else{
                    w->setAt(x+1,y,w->getAt(x,y)); //move to new spot
                    w->setAt(x,y,nullptr); //set current spot to empty
                    x++; //updates the position
                }
            }

        }
    }
    newposX=x; //updated x is assigned to be returned
    newposY=y; //updated y is assigned to be returned

    if(flag && hitpoint>0){ //the robot is alive and entered the loop
        this->heal(); //it's healed (if it's humanic)
    }
}

Robot::~Robot(){
    //body left empty
}