#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

const int WORLDSIZE=20;
const int INITIALANTS=100;
const int INITIALBUGS=5;
const int DOODLEBUG=1;
const int ANT=2;
const int ANTBREED=3;
const int DOODLEBREED=8;
const int DOODLESTARVE=3;

//forward declaration of Organism classes so we can reference it
//in the World class
class Organism;
class Doodlebug;
class Ant;

class World{
    friend class Organism; //allow Organism to access grid
    friend class Doodlebug; //allow Organism to access grid
    friend class Ant; //allow Organism to access grid
    public:
    World();
    ~World();
    Organism* getAt(int x, int y);
    void setAt(int x, int y, Organism *org);
    void Display();
    void SimulateOneStep();
    private:
    Organism* grid[WORLDSIZE][WORLDSIZE];
};
#endif