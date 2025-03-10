#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int humanTurn(int humanTotalScore);
int computerTurn(int computerTotalScore);

int main(){
    srand(time(NULL));
    int player,computer;
    
    player=computer=0;
    cout<<"----------------------------------"<<endl;
    cout<<"         DICE ROLL GAME"<<endl;
    cout<<"----------------------------------"<<endl<<endl;
    while(true){

        player=humanTurn(player);
        if(player>=100){
            cout<<"Player won!"<<endl;
            break;
        }

        computer=computerTurn(computer);
        if(computer>=100){
            cout<<"Computer won!"<<endl;
            break;
        }

    }
    return 0;
}

int humanTurn(int humanTotalScore){
    int dice;
    char choice;
    int total=0;
    cout<<"Player's Turn"<<endl;
    cout<<"****************"<<endl;
    do{
        dice=rand()%6+1;
        cout<<"PLAYER ROLLED "<<dice<<"!"<<endl;

        if(dice==1){
            total=0;
            choice='h';
        }
    
        else{
            total+=dice;
            cout<<"Press r to roll/h to hold:";
            cin>>choice;
        }
    }while(choice!='h');

    
    humanTotalScore+=total;
    cout<<"Player's total score: "<<humanTotalScore<<endl;
    cout<<"-----------------------------------"<<endl;
    return humanTotalScore;
}

int computerTurn(int computerTotalScore){
    int dice;
    int total=0;
    cout<<"Computer's Turn"<<endl;
    cout<<"****************"<<endl;
    do{
        dice=rand()%6+1;
        cout<<"COMPUTER ROLLED "<<dice<<"!"<<endl;

        if(dice==1){
            total=0;
            break;
        }
    
        else{
            total+=dice;
            if(computerTotalScore+total>=100){
                break;
            }
        }
    }while(total<20);

    computerTotalScore+=total;
    cout<<"Computer's total score: "<<computerTotalScore<<endl;
    cout<<"-----------------------------------"<<endl;
    return computerTotalScore;
}
