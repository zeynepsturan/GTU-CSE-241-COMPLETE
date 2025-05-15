#include "world.h"
#include "robot.h"

World::World(){
    //sets thw whole grid to nullptr
    for(int i=0; i<WORLDSIZE; i++){ //iteration for rows
        for(int j=0; j<WORLDSIZE; j++){ //iteration for columns
            grid[i][j]=nullptr; //initializes all cells to nullptr
        }
    }
    robotcount=0; //robot count is initially 0
}

void World::setRobotCount(int x){
    robotcount=x; //robot count is set
}

Robot* World::getAt(int x, int y){
    return grid[x][y]; //returns the wanted object
}

void World::setAt(int x, int y, Robot* r){
    grid[x][y]=r; //sets the wanted cell to r
}

bool World::SimulateOneStep(){
    //sets all robots' moved flag to false
    robotcount=0; //sets to 0
    int newX, newY;
    for(int i=0; i<WORLDSIZE; i++){ //iteration for rows

        for(int j=0; j<WORLDSIZE; j++){ //iteration for columns

            if(grid[i][j]!=nullptr){ //if the cell isn't empty
                grid[i][j]->setMoved(false); //sets the flag
                robotcount++; //increases the robotcount
            }
        }
    }

    //moves all robots
    for(int i=0; i<WORLDSIZE; i++){ //iteration for rows

        for(int j=0; j<WORLDSIZE; j++){ //iteration for columns

            if(grid[i][j]!=nullptr){ //if there is a robot in the cell

                if(robotcount<=1){ //if there is only one robot or no robot at all
                    return false; //to end simulation, function returns false
                }
                
                grid[i][j]->move(this,newX,newY);//moves the robot THEN FIGHTS AND HEALS IT
                
                if(grid[newX][newY]->getHitpoint()==0){ //if the robot died
                    robotcount--; //decreases the robot count
                    delete grid[newX][newY]; //it's deleted from the grid
                    grid[newX][newY]=nullptr; //cell is set to nullptr
                }

                if(robotcount<=1){ //if there is only one robot or no robot at all
                    return false; //to end simulation, function returns false
                }
                
            }
        }
    }
    return true;
}

void World::fightLoop(int x1, int y1, int x2, int y2){

    bool flag=false; //flag for leaving the loop

    while(true){ //infinite loop until one robot dies

        grid[x1][y1]->fight(grid[x2][y2]); //first robot attacks to the second

        if(grid[x1][y1]->getHitpoint()==0){ //if the first robot died
            flag=true; //sets the flag
        }

        if(grid[x2][y2]->getHitpoint()==0){ //if the second robot died
            delete grid[x2][y2]; //deletes the second robot
            robotcount--;
            grid[x2][y2]=nullptr; //sets the cell to nullptr
            flag=true; //sets the flag
        }

        if(flag){ //if a robot or 2 died
            break; //leaves the loop
        }

        grid[x2][y2]->fight(grid[x1][y1]); //second robot attacks to the first

        if(grid[x1][y1]->getHitpoint()==0){ //if the first robot died
            flag=true;//sets the flag
        }

        if(grid[x2][y2]->getHitpoint()==0){ //if the second robot died

            delete grid[x2][y2]; //deletes the second robot
            robotcount--;
            grid[x2][y2]=nullptr; //sets the cell to nullptr
            flag=true; //sets the flag

        }

        if(flag){ //if a robot or 2 died
            break; //leaves the loop
        }
    }
    return;
}

World::~World(){

    for(int i=0; i<WORLDSIZE; i++){ //iteration for rows
        
        for(int j=0; j<WORLDSIZE; j++){ //iteration for columns

            if(grid[i][j]!=nullptr){ //if the cell isn't empty
                delete grid[i][j]; //deletes the robot object
            }
        }
    }
}