#ifndef ITEM_H 
#define ITEM_H
#include "Field.h"
#include "constants.h"
#include "exceptions.h"
#include <iostream>
#include <vector>
using namespace std;

class Item{
public:
    Item(); //no parameter constructor
    Item(const vector<BaseField*>& format); //constructor with the format
    void addData(string data, int index); //adds data to the indexed field

    void setFilled(int i); //sets the number of filled fields
    int getFilled()const{return filled_field;} //gets the number of filled fields

    void setValid(bool b); //sets the validation
    bool getValid()const{return isValid;} //returns the validation

    virtual string getPrintable(); //returns the item data as string
    const vector<BaseField*>& getData()const{return data;} //returns the data vector

    virtual ~Item(); //destructor

private:
    int filled_field; //stores the number of filled fields
    bool isValid; //stores if the item is valid(if all the fields are filled)
    vector<BaseField*> data; //stores the data
};
#endif