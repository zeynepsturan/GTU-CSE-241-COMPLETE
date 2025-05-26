#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "BaseField.h"
#include "constants.h"
#include "Item.h"
#include "exceptions.h"
using namespace std;

template <class T>
class Field:public BaseField{
public:
    friend class Item; //Item is declared as a friend class for practical reasons
    Field(); //no parameter constructor
    Field(string name, string type, bool isarray); //constructor with field info parameters

    void setFieldName(string name); //sets the field name
    string getFieldName()const override{return fieldname;} //returns the field name

    bool getIsArray()const override{return is_array_or_not;} //returns if the data is an array

    void setFieldType(string type); //sets the field type
    string getFieldType()const override{return fieldtype;} //returns the field type

    string getDataAsString()const; //returns the stored data as string
    const vector<T> getData()const{return data;} //returns the data vector
private:
    string fieldname; //stores the field name
    string fieldtype; //stores the field type
    bool is_array_or_not; //stores that if the data is an array
    vector<T> data; //stores the field data
};

template <class T>
Field<T>::Field():BaseField(){
    fieldname=""; //fieldname is empty in default
    fieldtype=""; //fieldtype is empty in default
    is_array_or_not=false; //array info is false in default
    data.clear(); //data is cleared initially
}

template <class T>
Field<T>::Field(string name, string type, bool isarray){
    data.clear(); //data is cleared initially
    fieldname=name; //fieldname is assigned
    fieldtype=type; //fieldtype is assigned
    is_array_or_not=isarray; //array info is assigned
}

template <class T>
void Field<T>::setFieldName(string name){
    fieldname=name; //fieldname is assigned
}

template <class T>
void Field<T>::setFieldType(string type){
    fieldtype=type; //fieldtype is assigned
}

template <class T>
string Field<T>::getDataAsString()const{
    ostringstream oss; //ostream object is used for not to deal with data types and just get the data

    if(data.empty()){ //if there is no data
        return ""; //returns an empty string
    }

    oss<<data[0]; //adds first data to the ostringstream object
    for(int i=1; i<data.size(); i++){ //iterates through the data
        oss<<":"<<data[i]; //adds the rest of the data to the ostringstream object
    }

    return oss.str(); //returns the ostringstream object data as string
}

#endif