#ifndef MEDIA_H
#define MEDIA_H
#include <string>
using namespace std;

enum class mediatype{TEXT, IMAGE, AUDIO ,VIDEO};

class Media{
public:
    Media(); //no parameter constructor
    Media(string n); //constructor with a name parameter
    void setName(string n); //sets the name
    string getName()const; //returns the name
    virtual void info()=0; //pure virtual function to print the info of the object
    virtual mediatype getType()=0; //pure virtual function to get the media type
    virtual ~Media(){}; //destructor

private:
    string name; //stores the name of the media
};
#endif