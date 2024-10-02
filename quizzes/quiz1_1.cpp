#include <iostream>
#include <string>
using namespace std;

int main(){

    string str1="Hello", str2="World", str3;
    str3=str1;

    cout<<"Str1: "<<str1<<endl;
    cout<<"Str2: "<<str2<<endl;
    cout<<"Str3: "<<str3<<endl;

    if(str2<str1)
        cout<<"Str 2 is less than Str1\n";

    return 0;
}
