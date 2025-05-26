#include <iostream>
#include <fstream>
#include "Catalog.h"
using namespace std;

int main(){

    try{
        Catalog catalog("data.txt","output.txt"); //creates the catalog object
        catalog.readCommands("commands.txt"); //reads and uses the commands
    }

    catch(FileOpeningError& f){
        cout<<f.what()<<endl;
    }
    
    return 0;
}
