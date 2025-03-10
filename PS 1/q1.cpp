#include <iostream>
#include <cmath>
using namespace std;

int main(){
    for(int i=3;i<=100;i++){
        bool flag=false;

        for(int j=2;j<=sqrt(i);j++){
            
            if(i%j==0){
                flag=true;
                break;
            }
        }
        if(!flag)
            cout<<i<<endl;
    }
    return 0;
}
