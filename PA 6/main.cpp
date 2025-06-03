#include "Observer.h"
#include "Dataset.h"
#include "Player.h"
#include "Viewer.h"
#include "Image.h"
#include "Audio.h"
#include "Video.h"
#include "Text.h"
#include "exceptions.h"
#include <iostream>
using namespace std;

int main(){

    //create a Dataset object
    Dataset* ds=new Dataset();

    //create Observer's
    Player* p1=new Player();
    Player* p2=new Player();
    Viewer* v1=new Viewer();
    Viewer* v2=new Viewer();

    //save them
    cout<<"Registering observers..."<<endl;
    ds->register_observer(p1);
    ds->register_observer(p2);
    ds->register_observer(v1);
    ds->register_observer(v2);
    cout<<endl;

    //add the madia objects
    cout<<"Adding media objects..."<<endl;
    ds->add(new Image("imagename1", "1920x1080", "Nature photo")); //images
    ds->add(new Image("imagename2", "1280x720", "City photo"));
    ds->add(new Image("imagename3", "2560x1440", "Portrait"));
    ds->add(new Image("imagename4", "3840x2160", "Landscape"));
    ds->add(new Image("imagename5", "800x600", "Thumbnail"));

    ds->add(new Audio("audioname1", "3:45", "Rock music")); //audios
    ds->add(new Audio("audioname2", "4:20", "Pop music"));
    ds->add(new Audio("audioname3", "5:15", "Classical"));

    ds->add(new Video("videoname1", "10:30", "Movie trailer")); //videos
    ds->add(new Video("videoname2", "5:45", "Tutorial"));
    ds->add(new Video("videoname3", "15:20", "Documentary"));

    ds->add(new Text("textname1", "Article about technology")); //texts
    ds->add(new Text("textname2", "News report"));
    ds->add(new Text("textname3", "Blog post"));
    cout<<endl;

    // player's tests
    try{
        cout<<"Testing Player 1:"<<endl;
        p1->show_list();
        cout<<endl;
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"Currently playing:"<<endl;
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nNext audio:"<<endl;
        p1->next(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nNext audio:"<<endl;
        p1->next(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nNext audio:"<<endl;
        p1->next(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nNext audio:"<<endl;
        p1->next(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nNext audio:"<<endl;
        p1->next(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nNext video:"<<endl;
        p1->next(mediatype::VIDEO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPrevious audio:"<<endl;
        p1->previous(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPrevious audio:"<<endl;
        p1->previous(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPrevious audio:"<<endl;
        p1->previous(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPrevious audio:"<<endl;
        p1->previous(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPrevious audio:"<<endl;
        p1->previous(mediatype::AUDIO);
        p1->currently_playing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPrevious audio:"<<endl;
        p1->previous(mediatype::AUDIO);
        p1->currently_playing()->info();
        cout<<endl;
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    //viewer's tests
    try{
        cout<<"Testing Viewer 1:"<<endl;
        v1->show_list();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"Currently viewing:"<<endl;
        v1->currently_viewing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nNext image:"<<endl;
        v1->next(mediatype::IMAGE);
        v1->currently_viewing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nNext text:"<<endl;
        v1->next(mediatype::TEXT);
        v1->currently_viewing()->info();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPrevious image:"<<endl;
        v1->previous(mediatype::IMAGE);
        v1->currently_viewing()->info();
        cout<<endl;
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    //deleting the object
    try{
        cout<<"Testing object removal:"<<endl;
        cout<<"Removing currently playing object:"<<endl;
        p1->currently_playing()->info();
        ds->remove(p1->currently_playing());
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPlayer 1's updated list:"<<endl;
        p1->show_list();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nViewer 1's updated list:"<<endl;
        v1->show_list();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    //deleting the observer's
    try{
        cout<<"Testing observer removal:"<<endl;
        cout<<"Removing Player 2..."<<endl;
        ds->remove_observer(p2);
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"Adding new audio after removing observer:"<<endl;
        ds->add(new Audio("audioname4", "6:30", "Jazz music"));
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPlayer 1's list (should have new audio):"<<endl;
        p1->show_list();
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    try{
        cout<<"\nPlayer 2's list (should not have new audio):"<<endl;
        p2->show_list();
        cout<<endl;
    }
    catch(runtime_error& r){
        cout<<r.what()<<endl;
    }

    return 0;
}
