#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "person.h"
using std::string;

namespace{

    bool isValid(double g){
        if(g>=0.0 && g<=4.0)
            return true;
        return false;
    }
}

namespace GTUSpace{

    class Student: public Person{
    public:
        Student(const string& n, double g, const string& m):Person(n){
            GPA=g;
            major=m;
        }

        double getGPA()const{
            return GPA;
        }

        void setGPA(double g){
            if(isValid(g)){
                GPA=g;
            }
        }

        string getMAjor()const{
            return major;
        }

        void setMajor(const string& m){
            major=m;
        }

    private:
        double GPA;
        string major;
    };
}

#endif
