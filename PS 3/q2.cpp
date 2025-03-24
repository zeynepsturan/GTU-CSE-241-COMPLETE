#include <iostream>
#include <vector>

using namespace std;

int findSuitor(int n){
    vector<int> suitors;
    for(int i=1; i<=n; i++){
        suitors.push_back(i);
    }
    
    int index=0;
    while(suitors.size()>1){
        index=(index+2)%suitors.size();
        suitors.erase(suitors.begin()+index);
    }
    
    return suitors[0];
}

int main(){
    int n;
    cout<<"Enter the number of suitors:";
    cin>>n;
    
    int winner=findSuitor(n);
    cout<<"The suitor that Princess is going to marry:"<<winner<<endl;
    return 0;
}