#include "Organism.h"
#include "World.h"

Organism::Organism(){
    world=NULL;
    moved=false;
    breedTicks=0;
    x=0;
    y=0;
}

Organism::Organism(World *wrld, int x, int y){
    this->world=wrld;
    moved=false;
    breedTicks=0;
    this->x=x;
    this->y=y;
    wrld->setAt(x,y,this);
}

Organism::~Organism(){

}