#ifndef EXCEPTINOS_H
#define EXCEPTIONS_H
#include <iostream>
#include <exception>
using namespace std;

class EmptyListError:public runtime_error{
public:
    EmptyListError():runtime_error("The media list is empty."){}
};

class MissingTypeError:public runtime_error{
public:
    MissingTypeError():runtime_error("There is no media in this type."){}
};
#endif