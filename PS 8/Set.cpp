#include <iostream>
#include <string>
#include "Set.h"
using namespace std;

int main(){
    Set<int> s1;
    Set<string> s2;

    int* intArray=nullptr;
    string* stringArray=nullptr;

    s1.add(10);
    s1.add(20);
    s1.add(15);
    s1.add(20);

    intArray=s1.getArray();
    cout<<"Set one has "<<s1.getSize()<<" items. Here they are: "<<endl;

    for (int i=0; i<s1.getSize(); i++){
        cout<<intArray[i]<<endl;
    }

    if(intArray!=nullptr){
        delete[] intArray;
    }

    s2.add("butter");
    s2.add("hamburgers");
    s2.add("pizza");
    s2.add("hotdogs");
    s2.add("pizza");

    stringArray=s2.getArray();
    cout<<"Set two has "<<s2.getSize()<<" items. Here they are: "<<endl;

    for(int i=0; i<s2.getSize(); i++){
        cout<<stringArray[i]<<endl;
    }

    if(stringArray!=nullptr){
        delete [] stringArray;
    }
    
    return 0 ;
}

template <class T>
Set<T>::Set(){
    data.clear();
}

template <class T>
int Set<T>::getSize()const{
    return data.size();
}

template <class T>
void Set<T>::add(T newItem){
    int size=data.size();

    for(int i=0; i<size; i++){
        if(data[i]==newItem){
            return;
        }
    }

    data.push_back(newItem);
}

template <class T>
T* Set<T>::getArray(){
    int size=data.size();

    T* array=new T[size];

    for(int i=0; i<size; i++){
        array[i]=data[i];
    }

    return array;
}