#include <iostream>
using namespace std;

class HotDogStand{
public:
    HotDogStand();
    HotDogStand(int id, int s);

    void justSold();
    int getNumSold();

    void setID(int id);
    int getID();

    static int getTotalSold();
private:
    static int total_sold;
    int ID;
    int sold;
};

int main(){
    HotDogStand myStand;
    HotDogStand otherStand(1,10);

    int myID;
    int sold;

    cout<<"Enter your stand ID:";
    cin>>myID;

    myStand.setID(myID);

    cout<<"Your Stand ID:"<<myStand.getID()<<endl;
    cout<<"Your Sold:"<<myStand.getNumSold()<<endl;

    cout<<"Other Stand ID:"<<otherStand.getID()<<endl;
    cout<<"Other Sold:"<<otherStand.getNumSold()<<endl;

    cout<<"Total sold:"<<HotDogStand::getTotalSold()<<endl;

    myStand.justSold();

    
    cout<<"Stand ID:"<<myStand.getID()<<endl;
    cout<<"Sold:"<<myStand.getNumSold()<<endl;

    cout<<"Stand ID:"<<otherStand.getID()<<endl;
    cout<<"Sold:"<<otherStand.getNumSold()<<endl;

    cout<<"Total sold:"<<HotDogStand::getTotalSold()<<endl;

    return 0;
}

int HotDogStand::total_sold=0;

HotDogStand::HotDogStand(){
    ID=0;
    sold=0;
}

HotDogStand::HotDogStand(int id, int s){
    ID=id;
    sold=s;
    total_sold+=s;
}

void HotDogStand::justSold(){
    cout<<"Sold one!"<<endl;
    total_sold++;
    sold++;
}

int HotDogStand::getID(){
    return ID;
}

void HotDogStand::setID(int id){
    ID=id;
}

int HotDogStand::getNumSold(){
    return sold;
}

int HotDogStand::getTotalSold(){
    return total_sold;
}
