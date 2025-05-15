#ifndef ORGANISM_H
#define ORGANISM_H
#include "World.h"
#include <iostream>
using namespace std;

class Organism{
    friend class World; // Allow world to affect organism
    public:
    Organism();
    Organism(World *world, int x, int y);
    ~Organism();
    virtual void breed() = 0; // Whether or not to breed
    virtual void move() = 0; // Rules to move the critter
    virtual int getType() =0; // Return if ant or doodlebug
    virtual bool starve() = 0; // Determine if organism starves
    protected:
    int x,y; // Position in the world
    bool moved; // Bool to indicate if moved this turn
    int breedTicks; // Number of ticks since breeding
    World *world;
};
#endif