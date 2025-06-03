#include "Audio.h"

Audio::Audio():Media(""){
    duration=""; //set to empty string
    other_info=""; //set to empty string
}

Audio::Audio(string name, string dur, string other_inf):Media(name){
    other_info=other_inf; //other info is set
    duration=dur; //duration is set
}

void Audio::info(){
    cout<<getName()<<", "<<duration<<", "<<other_info<<endl; //prints the audio name and infos
}