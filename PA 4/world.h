#ifndef WORLD_H
#define WORLD_H
#include <iostream>
using namespace std;
const int WORLDSIZE=10; //WORLDSIZE for the square world

class Robot;

class World{
public:
    World(); //no parameter constructor

    bool SimulateOneStep(); //simulates the program step by step

    void fightLoop(int x1, int y1, int x2, int y2); //fights 2 robots

    Robot* getAt(int x, int y); //gets the robot in [x][y]
    void setAt(int x, int y, Robot* r); //sets the grid[x][y]

    void setRobotCount(int x); //sets the robot count
    int getRobotCount()const{return robotcount;} //returns the robot count

    ~World(); //destructor
private:
    Robot* grid[WORLDSIZE][WORLDSIZE]; //grid where robots in it
    int robotcount; //stores the number of robots in the grid
};
#endif