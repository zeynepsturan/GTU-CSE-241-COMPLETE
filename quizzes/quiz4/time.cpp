Time::Time(int h, int m){

    if(0<=h && h<24)
        hour=h;
    
    else
        hour=0;
    
    if(0<=m && m<60)
        minute=m;
    
    else
        minute=0;
}

bool Time::isEqual(Time t){

    if(t.hour==hour && t.minute==minute)
        return true;
    
    else
        return false;
}

bool Time::isEarlier(Time t){

    if(t.hour>hour){
        return true;
    }
    
    else if(t.hour==hour && minute <t.minute){
        return true;
    }
    
    return false;
}

void Time::printTime(){

    if(hour<10)
        cout<<"0";
    cout<<hour<<":";

    if(minute<10)
        cout<<"0";
    cout<<minute;

}

void Time::addMinutes(int m){

    int cary=0;

    if(minute+m>=60){
        cary=(minute+m)/60;
    }

    minute=(minute+m)%60;
    hour=(hour+cary)%24;
}

void Time::setMinutes(int m){
    if(m>=0 && m<60)
        minute=m;
}

void Time::setHours(int h){
    if(h>=0 && h<24)
        hour=h;
}

int Time::getMinutes(){
    return minute;
}
