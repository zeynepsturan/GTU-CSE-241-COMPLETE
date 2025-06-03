#include "Text.h"
#include <iostream>

Text::Text():Media(""){
    other_info=""; //set to empty string
}

Text::Text(string name, string other_inf):Media(name){
    other_info=other_inf; //other info is set
}

void Text::info(){
    cout<<getName()<<", "<<other_info<<endl; //prints the text name and infos
}