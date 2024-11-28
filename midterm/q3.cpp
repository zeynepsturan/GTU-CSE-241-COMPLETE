#include <iostream>
using namespace std;

GTUIntStack::GTUIntStack(){
    stack=nullptr;
    cap=10;
    top=cap;
}

int operator[](int index) const{
    if(index>=top){
        return stack[index];
    }
}

ostream& operator<<(ostream& o, const GTUIntStack& g){
    int i;
    for(i=top;i<cap-1;i++){
        o<<stack[i]<<" ";
    }
    return o;
}

bool GTUIntStack::isEmpty() const{
    return (cap-top==0);
}

int GTUIntStack::size() const{
    return cap-top;
}

GTUIntStack::GTUIntStack(const GTUIntStack& cs){
    int size=cs.size();
    stack=new int[size+10];
    cap=size+10;
    top=cap-size;
    for(int i=top;i<cap-1;i++){
        stack[i]=cs[i];
    }
}

void GTUIntStack::push(int num){
    int size=cap-top;
    if(cap<=size+1){
        cap+=10;
    }
    int* a=new int[cap];
    for(int i=top;i<cap-1;i++){
        a[i]=stack[i];
    }
    a[top-1]=num;}
    delete[] stack;
    stack=a;
    top--;
}

void GTUIntStack::pop(){
    int* a=new int[cap];
    int size=cap-top;
    if(size>0){
        for(int i=top+1;i<cap-1;i++){
            a[i]=stack[i];
        }
        delete[] stack;
        stack=a;
        top++;
    }
}