#ifndef BASEFIELD_H
#define BASEFIELD_H
#include <string>
using namespace std;

class BaseField{ //abstract class so all functions are pure virtual
public:
    BaseField(){} //no parameter constructor
    virtual ~BaseField(){} //deconstructor
    virtual string getFieldType()const=0; //returns the field type
    virtual string getFieldName()const=0; //returns the field name
    virtual bool getIsArray()const=0; //returns if the data is an array
    virtual string getDataAsString()const=0; //returns the stored data as string
private:
};

#endif