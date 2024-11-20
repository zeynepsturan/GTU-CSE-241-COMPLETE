#ifndef PERSON_H
#define PERSON_H
#include <string>
using std::string;

namespace GTUSpace{
    class Person{
    public:
        Person(const string& n){
            name=n;
        }
        void setName(const string& n){
            name=n;
        }

        string getName()const{
            return name;
        }

    private:
        string name;
    };
}

#endif
