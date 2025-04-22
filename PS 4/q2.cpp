#include <iostream>
#include <cmath>
using namespace std;

class MyInteger{
public:
    MyInteger(int i);
    MyInteger();
    void setInteger(int i);
    int getInteger()const;
    int operator[](int index)const;
private:
    int integer;
};

int main(){
    MyInteger num(418);
    cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
    cout<<num[3]<<endl;
    cout<<num[-1]<<endl;
    return 0;
}

MyInteger::MyInteger(int i):integer(i){}
MyInteger::MyInteger():integer(0){}

int MyInteger::operator[](int index)const{
    int i;
    if(index<0){
        return -1;
    }

    else{
        if(pow(10,index)>integer){
            return -1;
        }

        else{
            i=(int)(integer/pow(10,index));
            return i%10;
        }
    }
}

void MyInteger::setInteger(int i){
    integer=i;
}

int MyInteger::getInteger()const{
    return integer;
}