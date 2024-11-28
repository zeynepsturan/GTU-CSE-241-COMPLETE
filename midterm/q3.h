#ifndef GTUINTSTACK_H
#define GTUINTSTACK_H
#include <iostream>
using namespace std;

class GTUIntStack{
public:
    void push(int num);
    friend ostream& operator<<(ostream& o, const GTUIntStack& g);
    int size() const;
    bool isEmpty() const;
    void pop();
    GTUIntStack();
    GTUIntStack(const GTUIntStack& cs); //copy constructor
    int operator[](int index) const;

private:
    int* stack;
    int cap;
    int top;
};

#endif