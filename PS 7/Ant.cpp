#include "Ant.h"
#include "World.h"

Ant::Ant() : Organism(){

}

Ant::Ant(World *world, int x, int y):Organism(world,x,y){

}

void Ant::move(){
    // Pick random direction to move
    int dir=rand()%4;

    // Try to move up, if not at an edge and empty spot
    if(dir==0){
        if((y>0) && (world->getAt(x,y-1)==NULL)){
            world->setAt(x,y-1,world->getAt(x,y)); // Move to new spot
            world->setAt(x,y,NULL);
            y--;
        }
    }
    // Try to move down
    else if(dir==1){
        if((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL)){
            world->setAt(x,y+1,world->getAt(x,y)); // Move to new spot
            world->setAt(x,y,NULL); // Set current spot to empty
            y++;
        }
    }
    // Try to move left
    else if(dir==2){
        if((x>0) && (world->getAt(x-1,y)==NULL)){
            world->setAt(x-1,y,world->getAt(x,y)); // Move to new spot
            world->setAt(x,y,NULL); // Set current spot to empty
            x--;
        }
    }
    // Try to move right
    else{
        if((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL)){
            world->setAt(x+1,y,world->getAt(x,y)); // Move to new spot
            world->setAt(x,y,NULL); // Set current spot to empty
            x++;
        }
    }
}

int Ant::getType(){
    return ANT;
}

void Ant::breed(){
    breedTicks++;

    if (breedTicks == ANTBREED){
        breedTicks = 0;

        // Try to make a new ant either above, left, right, or down
        if ((y>0) && (world->getAt(x,y-1)==NULL)){
            Ant *newAnt = new Ant(world, x, y-1);
        }

        else if((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL)){
            Ant *newAnt = new Ant(world, x, y+1);
        }

        else if ((x>0) && (world->getAt(x-1,y)==NULL)){
            Ant *newAnt = new Ant(world, x-1, y);
        }

        else if((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL)){
        Ant *newAnt = new Ant(world, x+1, y);
        }
    }
}