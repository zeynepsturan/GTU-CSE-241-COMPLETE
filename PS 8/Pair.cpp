#include <iostream>
#include "Pair.h"
using namespace std;

int main(){
    
    Pair<char,char>p('A','B');
    cout<<"First is "<<p.getFirst()<<endl;

    p.setFirst('Z');
    cout<<"First changed to "<<p.getFirst()<<endl;

    cout<<"The pair is: "<<p.getFirst()<<" , "<<p.getSecond()<<endl;

    Pair<int,string> p2(34,"Bill");
    Pair<string,int> p3("Bill",34);
    cout<<"The pair is: "<<p2.getFirst()<<" , "<<p2.getSecond()<<endl;
    return 0;
}

template<class T, class K>
Pair<T,K>::Pair(T new1, K new2){
    first=new1;
    second=new2;
}

template<class T, class K>
T Pair<T,K>::getFirst(){
    return first;
}

template <class T, class K>
void Pair<T,K>::setFirst(T new1){
    first=new1;
}

template<class T, class K>
K Pair<T,K>::getSecond(){
    return second;
}

template <class T, class K>
void Pair<T,K>::setSecond(K new2){
    second=new2;
}