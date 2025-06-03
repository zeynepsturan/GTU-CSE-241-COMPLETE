#include "Image.h"

Image::Image():Media(""){
    dimension_info=""; //set to empty string
    other_info=""; //set to empty string
}

Image::Image(string name, string dimension_inf, string other_inf):Media(name){
    dimension_info=dimension_inf; //dimension is set
    other_info=other_inf; //other info is set
}

void Image::info(){
    cout<<getName()<<", "<<dimension_info<<", "<<other_info<<endl; //prints the image name and infos
}