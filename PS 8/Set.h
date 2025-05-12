#ifndef SET_H
#define SET_H
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Set{
public:
    Set();
    void add(T newItem);
    int getSize()const;
    T* getArray();
private:
    vector<T> data;
};
#endif
