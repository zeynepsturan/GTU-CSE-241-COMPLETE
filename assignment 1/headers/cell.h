#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum dtype{
    NONE,VALUE,LABEL,FUNCTION
};

class Cell{
public:
    Cell();
    
    string getValue();
    void setValue(string text);

    void setDtype(dtype t);
    dtype getDtype();

    void setNum(double d);
    double getNum();
    
    void setError(bool e);
    bool getError();

private:
    string value;
    enum dtype type;
    double num;
    bool error;
};

#endif