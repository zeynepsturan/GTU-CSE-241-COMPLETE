#include "Doodlebug.h"
#include "World.h"

Doodlebug::Doodlebug():Organism(){
    starveTicks=0;
}

Doodlebug::Doodlebug(World *world, int x, int y) : Organism(world,x,y){
    starveTicks=0;
}

void Doodlebug::move(){
    
    if((y>0) && (world->getAt(x,y-1)!=NULL) && (world->getAt(x,y-1)->getType() == ANT)){
        delete (world->grid[x][y-1]); // Kill ant
        world->grid[x][y-1] = this; // Move to spot
        world->setAt(x,y,NULL);
        
        starveTicks=0; // Reset hunger
        y--;
        return;
    }
    else if((y<WORLDSIZE-1) && (world->getAt(x,y+1)!=NULL) &&(world->getAt(x,y+1)->getType() == ANT)){
        delete (world->grid[x][y+1]); // Kill ant
        world->grid[x][y+1] = this; // Move to spot
        world->setAt(x,y,NULL);

        starveTicks=0; // Reset hunger
        y++;
        return;
    }

    else if((x>0) && (world->getAt(x-1,y)!=NULL) &&(world->getAt(x-1,y)->getType() == ANT)){
        delete (world->grid[x-1][y]); // Kill ant
        world->grid[x-1][y] = this; // Move to spot
        world->setAt(x,y,NULL);

        starveTicks=0; // Reset hunger
        x--;
        return;
    }

    else if((x<WORLDSIZE-1) && (world->getAt(x+1,y)!=NULL) &&(world->getAt(x+1,y)->getType() == ANT)){
        delete (world->grid[x+1][y]); // Kill ant
        world->grid[x+1][y] = this; // Move to spot
        world->setAt(x,y,NULL);

        starveTicks=0; // Reset hunger
        x++;
        return;
    }

    // If we got here, then we didn't find food. Move
    // to a random spot if we can find one.
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
        if ((x>0) && (world->getAt(x-1,y)==NULL)){
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

    starveTicks++; // Increment starve tick since we didn't
    // eat on this turn
}

int Doodlebug::getType(){
    return DOODLEBUG;
}

void Doodlebug::breed(){
    breedTicks++;
    if(breedTicks==DOODLEBREED){
        breedTicks=0;

        // Try to make a new ant either above, left, right, or down
        if((y>0) && (world->getAt(x,y-1)==NULL)){
            Doodlebug *newDoodle = new Doodlebug(world, x, y-1);
        }

        else if((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL)){
            Doodlebug *newDoodle = new Doodlebug(world, x, y+1);
        }

        else if((x>0) && (world->getAt(x-1,y)==NULL)){
            Doodlebug *newDoodle = new Doodlebug(world, x-1, y);
        }

        else if((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL)){
            Doodlebug *newDoodle = new Doodlebug(world, x+1, y);
        }
    }
}

bool Doodlebug::starve(){
    // Starve if no food eaten in last DOODLESTARVE time ticks
    if(starveTicks>DOODLESTARVE){
        return true;
    }
    return false;
}