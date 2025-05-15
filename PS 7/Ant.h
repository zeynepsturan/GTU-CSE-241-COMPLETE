#ifndef ANT_H
#define ANT_H
#include "Organism.h"
#include "World.h"
#include <iostream>
using namespace std;

class Ant:public Organism{
    friend class World;
    public:
    Ant();
    Ant(World *world, int x, int y);
    void breed(); //must define this since virtual
    void move(); //must define this since virtual
    int getType(); //must define this since virtual
    bool starve(){return false;} //return false, ant never starves
};
#endif