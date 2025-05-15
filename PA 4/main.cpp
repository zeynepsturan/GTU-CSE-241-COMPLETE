#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "world.h"
#include "optimusprime.h"
#include "robocop.h"
#include "roomba.h"
#include "bulldozer.h"
#include "kamikaze.h"
using namespace std;

void randomCoordinates(int& x, int& y); //creates random [x][y] values

const int INITIAL_EACH_ROBOT_TYPE_COUNT=5; //determines the number for each robot in simulation

int main(){
    srand(time(NULL)); //random number generator seed
    
    string s; //stores the user input
    World w; //our simulation world

    // Randomly create 5 robots of each type
    int count=0; //stores the created robot count
    int x; //stores the randomly created row num
    int y; //stores the randomly created column num

    while(count<INITIAL_EACH_ROBOT_TYPE_COUNT){ //creates optimusprimes
        randomCoordinates(x,y);

        if(w.getAt(x,y)==nullptr){ //if the cell is empty

            count++; //increases the count
            optimusprime* o= new optimusprime(x,y,OPTIMUSPRIME_STRENGTH,OPTIMUSPRIME_HITPOINT); //creates the new optimusprime object
            w.setAt(x,y,o); //puts the new object in world
            w.setRobotCount(w.getRobotCount()+1);
            o=nullptr; //o doesn't point to anything now (in case of any dangling)
        }
    }
    
    count=0; //resets count
    while(count<INITIAL_EACH_ROBOT_TYPE_COUNT){ //creates robocops
        randomCoordinates(x,y);

        if(w.getAt(x,y)==nullptr){ //if the cell is empty
            count++; //increases the count
            robocop* r = new robocop(x,y,ROBOCOP_STRENGTH,ROBOCOP_HITPOINT); //creates the new robocop object
            w.setAt(x,y,r); //puts the new object in world
            w.setRobotCount(w.getRobotCount()+1);
            r=nullptr; //r doesn't point to anything now (in case of any dangling)
        }
    }

    count=0; //resets count
    while(count<INITIAL_EACH_ROBOT_TYPE_COUNT){ //creates roombas
        randomCoordinates(x,y);

        if(w.getAt(x,y)==nullptr){ //if the cell is empty
            count++; //increases the count
            roomba *r = new roomba(x,y,ROOMBA_STRENGTH,ROOMBA_HITPOINT); //creates the new roomba object
            w.setAt(x,y,r); //puts the new object in world
            w.setRobotCount(w.getRobotCount()+1);
            r=nullptr; //r doesn't point to anything now (in case of any dangling)
        }
    }

    count=0; //resets count
    while(count<INITIAL_EACH_ROBOT_TYPE_COUNT){ //creates bulldozers
        randomCoordinates(x,y);

        if(w.getAt(x,y)==nullptr){ //if the cell is empty
            count++; //increases the count
            bulldozer *b = new bulldozer(x,y,BULLDOZER_STRENGTH,BULLDOZER_HITPOINT); //creates the new bulldozer object
            w.setAt(x,y,b); //puts the new object in world
            w.setRobotCount(w.getRobotCount()+1);
            b=nullptr; //b doesn't point to anything now (in case of any dangling)
        }
    }

    count=0; //resets count
    while(count<INITIAL_EACH_ROBOT_TYPE_COUNT){ //creates kamikazes
        randomCoordinates(x,y);

        if(w.getAt(x,y)==nullptr){ //if the cell is empty
            count++; //increases the count
            kamikaze *k = new kamikaze(x,y,KAMIKAZE_STRENGTH,KAMIKAZE_HITPOINT); //creates the new kamikaze object
            w.setAt(x,y,k); //puts the new object in world
            w.setRobotCount(w.getRobotCount()+1);
            k=nullptr; //k doesn't point to anything now (in case of any dangling)
        }
    }

    while(true){//run simulation forever until it ends

        if(!(w.SimulateOneStep())){ //simulates one step
            break; //breaks the loop if it ended
        }
        
        getline(cin,s); //user input
    }
    return 0; //program ends
}

void randomCoordinates(int& x, int& y){
    x=rand()%WORLDSIZE; //creates number between 0-WORLDSIZE-1
    y=rand()%WORLDSIZE; //creates number between 0-WORLDSIZE-1
}
