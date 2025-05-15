#include "World.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

World::World(){
    //initialize world to empty spaces
    int i,j;
    for (i=0; i<WORLDSIZE; i++){
        for (j=0; j<WORLDSIZE; j++){
            grid[i][j]=NULL;
        }
    }
}
World::~World(){
    //release any allocated memory
    int i,j;
    for (i=0; i<WORLDSIZE; i++){
        for (j=0; j<WORLDSIZE; j++){
            if (grid[i][j]!=NULL) delete (grid[i][j]);
        }
    }
}

Organism* World::getAt(int x, int y){
    if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE))
        return grid[x][y];
    return NULL;
}

void World::setAt(int x, int y, Organism *org){
    if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE)){
        grid[x][y] = org;
    }
}

void World::Display(){
    int i,j;
    cout << endl << endl;
    for (j=0; j<WORLDSIZE; j++){
        for (i=0; i<WORLDSIZE; i++){
            if (grid[i][j]==NULL)
                cout << ".";
            else if (grid[i][j]->getType()==ANT)
                cout << "o";
            else cout << "X";
        }
        cout << endl;
    }
}

void World::SimulateOneStep(){

    // First reset all organisms to not moved
    for(int i=0; i<WORLDSIZE; i++){

        for(int j=0; j<WORLDSIZE; j++){

            if(grid[i][j]!=NULL){
                grid[i][j]->moved = false;
            }
        }
    }
    
    // Loop through cells in order and move if it's a Doodlebug
    for(int i=0; i<WORLDSIZE; i++){

        for(int j=0; j<WORLDSIZE; j++){

            if((grid[i][j]!=NULL) && (grid[i][j]->getType()==DOODLEBUG)){

                if(grid[i][j]->moved == false){
                    grid[i][j]->moved = true; // Mark as moved
                    grid[i][j]->move();
                }
            }
        }
    }

    // Loop through cells in order and move if it's an Ant
    for(int i=0; i<WORLDSIZE; i++){

        for(int j=0; j<WORLDSIZE; j++){

            if((grid[i][j]!=NULL) && (grid[i][j]->getType()==ANT)){
                
                if(grid[i][j]->moved==false){
                    grid[i][j]->moved=true; //mark as moved
                    grid[i][j]->move();
                }
            }
        }
    }
    // Loop through cells in order and check if we should breed
    for(int i=0; i<WORLDSIZE; i++){

        for(int j=0; j<WORLDSIZE; j++){

            // Kill off any doodlebugs that haven't eaten recently
            if((grid[i][j]!=NULL) && (grid[i][j]->getType()==DOODLEBUG)){
                if (grid[i][j]->starve()){
                    delete (grid[i][j]);
                    grid[i][j] = NULL;
                }
            }
        }
    }
    
    // Loop through cells in order and check if we should breed
    for(int i=0; i<WORLDSIZE; i++){
        
        for(int j=0; j<WORLDSIZE; j++){
            // Only breed organisms that have moved, since
            // breeding places new organisms on the map we
            // don't want to try and breed those
            if ((grid[i][j]!=NULL) && (grid[i][j]->moved==true)){
                grid[i][j]->breed();
            }
        }
    }
}