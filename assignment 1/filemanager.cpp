#include <fstream>
#include <sstream>
#include "headers/filemanager.h"
#include "headers/global.h"
using namespace std;

void FileManager::saveToFile(AnsiTerminal& terminal, vector<vector<Cell>>& table){
    ofstream file;
    string filename="";
    char c;

    //gets the file name
    terminal.printAtW(SHOWN_ROWS+6 , 0, " ", 50);
    terminal.printAt(SHOWN_ROWS+6, 0, "File name:");
    terminal.printAtW(SHOWN_ROWS+7 , 0, " ", 50);

    do{
        c=terminal.getSpecialKeyW();

        if(c=='\n') break; //leaves the loop when enter is pressed

        filename+=c; //adds new character to the file name
        terminal.printAt(SHOWN_ROWS + 6, 12, filename);

    }while(true);

    //adds .csv if the user didn't include it
    if (filename.size()>4 && filename.substr(filename.size()-4)!=".csv"){
        filename+=".csv";
    }

    //opening the file
    file.open(filename);

    if(file.is_open()){

        for(auto &row:table){

            bool firstCell=true; //we don't want to add a coma before the first cell

            for(auto &cell:row){
                
                if(!firstCell){
                    file<<",";
                }

                firstCell=false;

                string cellValue=cell.getValue();
                file<<cellValue; //writes cells to the file
            }

            //adds newline for the next row
            file<<'\n';
        }
        terminal.printAtW(SHOWN_ROWS+6 , 0, " ", 50);
        terminal.printAt(SHOWN_ROWS + 6, 0, "File saved successfully");
    }

    else{
        terminal.printAtW(SHOWN_ROWS+6 , 0, " ", 50);
        terminal.printAt(SHOWN_ROWS + 6, 0, "The file could not be opened");
    }

    file.close();
}

void FileManager::loadFromFile(AnsiTerminal& terminal, vector<vector<Cell>>& table){
    ifstream file;
    string filename="";
    string holdvalue;
    int i=0, j=0;
    char c;

    //gets the file name
    terminal.printAtW(SHOWN_ROWS+6 , 0, " ", 50);
    terminal.printAt(SHOWN_ROWS+6, 0, "File name:");
    terminal.printAtW(SHOWN_ROWS+7 , 0, " ", 50);

    do{
        c=terminal.getSpecialKeyW();

        if(c=='\n') break; //leaves the loop when enter is pressed

        filename+=c; //adds new character to the file name
        terminal.printAt(SHOWN_ROWS + 6, 12, filename);

    }while(true);

    //adds .csv if the user didn't include it
    if (filename.size()>4 && filename.substr(filename.size()-4)!=".csv"){
        filename+=".csv";
    }

    //opening the file
    file.open(filename);

    if(file.is_open()){
        
        while(getline(file,holdvalue) && i<MAX_ROWS){
            istringstream lineStream(holdvalue);
            string value;
            j = 0;

            while (getline(lineStream, value, ',') && j < MAX_COLUMNS){
                //sets the vector for rows
                if (table.size()<=i){
                    table.resize(i+1, vector<Cell>(table[0].size()));
                }

                //sets the vector for columns
                if(table[i].size()<=j){
                    for(auto &row:table){
                        row.resize(j+1, Cell());
                    }
                }

                if(value[0]=='='){
                    table[i][j].setDtype(FUNCTION);
                }
                table[i][j].setValue(value); //assigns values to cells
                
                j++;
                
            }
            i++;
        }

        file.close();
    }

    else{
        terminal.printAtW(SHOWN_ROWS+6 , 0, " ", 50);
        terminal.printAt(SHOWN_ROWS+6,0,"The file is not found");
    }
}