#include "Video.h"

Video::Video():Media(""){
    duration=""; //set to empty string
    other_info=""; //set to empty string
}

Video::Video(string name, string dur, string other_inf):Media(name){
    other_info=other_inf; //other info is set
    duration=dur; //duration is set
}

void Video::info(){
    cout<<getName()<<", "<<duration<<", "<<other_info<<endl; //prints the video name and infos
}