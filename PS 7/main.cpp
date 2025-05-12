#include <iostream>
#include "World.h"
#include "Ant.h"
#include "Doodlebug.h"
using namespace std;
int main(){
  
  srand(time(NULL)); // Seed random number generator
  World w;
  string s;
  
  // Randomly create 100 ants
  int antcount = 0;
  while(antcount<INITIALANTS){
    int x=rand()%WORLDSIZE;
    int y=rand()%WORLDSIZE;
    if(w.getAt(x,y)==NULL){ // Only put ant in empty spot
      antcount++;
      Ant *a1 = new Ant(&w,x,y);
    }
  }
  
  // Randomly create 5 doodlebugs
  int doodlecount=0;
  while (doodlecount<INITIALBUGS){
    int x=rand()%WORLDSIZE;
    int y=rand()%WORLDSIZE;
    if (w.getAt(x,y)==NULL){ // Only put doodlebug in empty spot
      doodlecount++;
      Doodlebug *d1 = new Doodlebug(&w,x,y);
    }
  }
  
  // Run simulation forever, until user cancels
  while (true){
    w.Display();
    w.SimulateOneStep();
    cout<<endl<<"Press enter for next step"<<endl;
    getline(cin,s);
  }
  return 0;
}
