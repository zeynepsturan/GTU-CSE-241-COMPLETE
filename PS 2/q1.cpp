#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void AaronsShot(bool& isAaronAlive, bool& isBobAlive, bool& isCharlieAlive);
void BobsShot(bool& isAaronAlive, bool& isBobAlive, bool& isCharlieAlive);
void CharliesShot(bool& isAaronAlive, bool& isBobAlive, bool& isCharlieAlive);

int main(){
  
    srand(time(NULL));
    const int NUMBER_OF_DUELS=10000;

    bool isAaronAlive;
    bool isBobAlive;
    bool isCharlieAlive;

    int aaronWin=0;
    int bobWin=0;
    int charlieWin=0;

    for(int i=0; i<NUMBER_OF_DUELS; i++){

        isAaronAlive=true;
        isBobAlive=true;
        isCharlieAlive=true;

        do{
            AaronsShot(isAaronAlive, isBobAlive, isCharlieAlive);

            BobsShot(isAaronAlive, isBobAlive, isCharlieAlive);

            CharliesShot(isAaronAlive, isBobAlive, isCharlieAlive);

        }while((isAaronAlive && isBobAlive) || (isAaronAlive && isCharlieAlive) || (isBobAlive && isCharlieAlive));

        if(isAaronAlive){
            aaronWin++;
        }

        if(isBobAlive){
            bobWin++;
        }

        if(isCharlieAlive){
            charlieWin++;
        }

    }

    cout<<"Aaron won "<<aaronWin<<"/"<<NUMBER_OF_DUELS<<" duels or "<<
    static_cast<double>(aaronWin)/static_cast<double>(NUMBER_OF_DUELS)*100<<"%"<<endl;

    cout<<"Bob won "<<bobWin<<"/"<<NUMBER_OF_DUELS<<" duels or "<<
    static_cast<double>(bobWin)/static_cast<double>(NUMBER_OF_DUELS)*100<<"%"<<endl;

    cout<<"Charlie won "<<charlieWin<<"/"<<NUMBER_OF_DUELS<<" duels or "<<
    static_cast<double>(charlieWin)/static_cast<double>(NUMBER_OF_DUELS)*100<<"%"<<endl;

    return 0;
}

void AaronsShot(bool& isAaronAlive, bool& isBobAlive, bool& isCharlieAlive){

    if(isAaronAlive){
        int random=rand()%3;

        if(random==0){

            if(isCharlieAlive){
                isCharlieAlive=false;
            }

            else{
                isBobAlive=false;
            }
        }
    }

}

void BobsShot(bool& isAaronAlive, bool& isBobAlive, bool& isCharlieAlive){

    if(isBobAlive){
        int random=rand()%2;

        if(random==0){

            if(isCharlieAlive){
                isCharlieAlive=false;
            }

            else{
                isAaronAlive=false;
            }
        }
    }

}

void CharliesShot(bool& isAaronAlive, bool& isBobAlive, bool& isCharlieAlive){

    if(isCharlieAlive){

        if(isBobAlive){
            isBobAlive=false;
        }

        else{
            isAaronAlive=false;
        }
    }

}
