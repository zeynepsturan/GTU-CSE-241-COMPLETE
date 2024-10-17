class Time{

public:
    Time(int h=0, int m=0);

    bool isEqual(Time t);
    bool isEarlier(Time t);

    void printTime();
    void addMinutes(int m);
    void setMinutes(int m);
    void setHours(int h);
    
    int getMinutes();

private:
    int hour;
    int minute;
};
