#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include "headers/cell.h"
#include "headers/functions.h"
#include "headers/global.h"
using namespace std;

void Functions::determineCells(vector<vector<Cell>>& table, string sc, string ec, int& startr, int& startc, int& endr, int& endc){

    string rownum="";
    string colname="";

    for(char i:sc){//stores the start cell's row and column info

        if(isalpha(i)){
            colname+=i;
        }

        else{
            rownum+=i;
        }
    }
    //converts row and column to intigers
    startr=stoi(rownum)-1;
    startc=col_to_int(colname)-1;

    rownum="";
    colname="";

    for(char i:ec){ //stores the end cell's row and column info

        if(isalpha(i)){
            colname+=i;
        }

        else{
            rownum+=i;
        }
    }

    //converts row and column to intigers
    endr=stoi(rownum)-1;
    endc=col_to_int(colname)-1;
}

double Functions::SUM(vector<vector<Cell>>& table, const string& startcell, const string& endcell){
    double sum=0.0;
    int startRow;
    int startCol;
    int endRow;
    int endCol;

    //converts startcell and endcell's row column infos to intigers
    determineCells(table, startcell, endcell, startRow, startCol, endRow, endCol);

    if(startRow==endRow){

        for(int i=startCol; i<=endCol; i++){
            sum+=table[startRow][i].getNum();
        }
    }

    else if(startCol==endCol){

        for(int i=startRow; i<=endRow; i++){
            sum+=table[i][startCol].getNum();
        }
    }

    return sum;
}

double Functions::AVER(vector<vector<Cell>>& table, const string& startcell, const string& endcell){
    double sum=0.0;
    int count=0;
    int startRow;
    int startCol;
    int endRow;
    int endCol;

    determineCells(table, startcell, endcell, startRow, startCol, endRow, endCol);
    
    for(int i=startRow; i<=endRow; i++){
        for(int j=startCol; j<=endCol; j++){
            sum+=table[i][j].getNum();
            count++;
        }
    }
    return sum/count;
}

double Functions::MAX(vector<vector<Cell>>& table, const string& startcell, const string& endcell){
    int startRow;
    int startCol;
    int endRow;
    int endCol;

    determineCells(table, startcell, endcell, startRow, startCol, endRow, endCol);
    int max=table[startRow][startCol].getNum();

    for(int i=startRow; i<=endRow; i++){
        for(int j=startCol; j<=endCol; j++){
            if(table[i][j].getNum()>max){
                max=table[i][j].getNum();
            }
        }
    }
    return max;
}

double Functions::MIN(vector<vector<Cell>>& table, const string& startcell, const string& endcell){
    int startRow;
    int startCol;
    int endRow;
    int endCol;

    determineCells(table, startcell, endcell, startRow, startCol, endRow, endCol);
    int min=table[startRow][startCol].getNum();

    for(int i=startRow; i<=endRow; i++){
        for(int j=startCol; j<=endCol; j++){
            if(table[i][j].getNum()<min){
                min=table[i][j].getNum();
            }
        }
    }
    return min;
}

double Functions::STDDEV(vector<vector<Cell>>& table, const string& startcell, const string& endcell){
    double sum=0.0;
    int count=0;
    int startRow, startCol, endRow, endCol;

    determineCells(table, startcell, endcell, startRow, startCol, endRow, endCol);
    
    //sums the cells and counts the # of cells
    for(int i=startRow; i<=endRow; i++){
        for(int j=startCol; j<=endCol; j++){
            sum+=table[i][j].getNum();
            count++;
        }
    }

    //average
    double mean=0.0;
    
    if(count>0){
        mean=sum/count;
    }

    //sum of squares of difference
    double varianceSum=0.0;
    for(int i=startRow; i<=endRow; i++){
        for(int j=startCol; j<=endCol; j++) {
            double diff=table[i][j].getNum()-mean;
            varianceSum+=diff*diff;
        }
    }

    // squareroot of variance is the stddev
    if(count>1){
       return sqrt(varianceSum/(count-1));
    }
    
    else{
        return 0.0;
    }
}

void Functions::handleFunction(vector<vector<Cell>>& table, int r, int c){ //only asked the token parts to ChatGPT

    string func=table[r][c].getValue();
    double numvalue=0.0;
    int sign=1;
    char currentOp='+';  //default is +
    char nextOp;//holds the next operator for next use

    //deletes the = sign first
    if(func[0]=='='){
        func=func.substr(1);
    }

    istringstream stream(func);
    string token;
    double currentValue=0.0;
    size_t opPos; //holds the position of the operator

    while(!func.empty()){
        //finds the operation and splits the function
        opPos=func.find_first_of("+*/");

        if(opPos!=string::npos){ //if the operation has found
            token=func.substr(0, opPos); //stores the part before the operation
            nextOp=func[opPos];
            func=func.substr(opPos+1); //updates the function
        }

        else{ //if there is no operation
            token=func; //stores the rest of the function
            func="";
        }

        //checks the value(cell or number)
        if(token[0]=='-'){
            currentOp='+';
            sign*=-1;
            token=token.substr(1);

            while(token[0]=='-'){
                sign*=-1;
                token=token.substr(1);
            }
            
        }

        if(token.find("SUM")==0){
            size_t dotdotPos=token.find("..");
            string startCell=token.substr(3, dotdotPos-3);
            string endCell=token.substr(dotdotPos + 2);
            currentValue=SUM(table, startCell, endCell);
        }

        else if(token.find("AVER")==0){
            size_t dotdotPos=token.find("..");
            string startCell=token.substr(4, dotdotPos-4);
            string endCell=token.substr(dotdotPos + 2);
            currentValue=AVER(table, startCell, endCell);
        }

        else if(token.find("MAX")==0){
            size_t dotdotPos=token.find("..");
            string startCell=token.substr(3, dotdotPos-3);
            string endCell=token.substr(dotdotPos + 2);
            currentValue=MAX(table, startCell, endCell);
        }

        else if(token.find("MIN")==0){
            size_t dotdotPos=token.find("..");
            string startCell=token.substr(3, dotdotPos-3);
            string endCell=token.substr(dotdotPos + 2);
            currentValue=MIN(table, startCell, endCell);
        }

        else if(token.find("STDDEV")==0){
            size_t dotdotPos=token.find("..");
            string startCell=token.substr(6, dotdotPos-6);
            string endCell=token.substr(dotdotPos + 2);
            currentValue=STDDEV(table, startCell, endCell);
        }

        else if(isalpha(token[0])){ //cell reference
            string colname="";
            string rowname="";
            int i=0;

            //holds the column name
            while(i<token.size() && isalpha(token[i])){
                colname+=token[i];
                i++;
            }

            //holds the row number
            while(i<token.size() && isdigit(token[i])){
                rowname+=token[i];
                i++;
            }

            //converting row and column strings to integer
            int ref_row=stoi(rowname)-1;
            int ref_col=col_to_int(colname)-1;

            if(ref_row>=table.size() || ref_col>=table[0].size()){ //if the memory for that cell is not allocated yet
                currentValue=0.0;
            }

            else if(table[ref_row][ref_col].getValue()!=""){ //if the cell is emty

                if(table[ref_row][ref_col].getDtype()==VALUE){
                    currentValue=stod(table[ref_row][ref_col].getValue());
                }

                else if(table[ref_row][ref_col].getDtype()==FUNCTION){
                    currentValue=table[ref_row][ref_col].getNum();
                }

                else{
                    currentValue=0.0;
                }
            }

            else{
                currentValue=0.0;
            }
        }
        
        else if(isdigit(token[0])){ //number 
            currentValue=stod(token);
        }

        if(sign==-1){
            currentValue*=-1;
        }

        //does the operation
        switch(currentOp){

            case '+':
                numvalue+=currentValue;
                break;

            case '-':
                numvalue-=currentValue;
                break;

            case '*':
                numvalue*=currentValue;
                break;

            case '/':
                if(currentValue!=0){
                    numvalue/=currentValue;
                }

                else{
                    table[r][c].setError(true);
                    return;
                }
                break;
        }
        currentOp=nextOp;
        sign=1;
    }
    //saves the result
    table[r][c].setNum(numvalue);
}

