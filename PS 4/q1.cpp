#include <iostream>
using namespace std;

class Vector2D{
public:
    Vector2D(int X, int Y);
    Vector2D();

    int getX()const;
    int getY()const;

    void set(int X, int Y);
    int operator*(const Vector2D& other)const;

private:
    int x;
    int y;
};

int main(){
    Vector2D v1(10,0), v2(0,10), v3(10,10), v4(5,4);
    
    cout<<"("<<v1.getX()<<","<<v1.getY()<<")*("<<v2.getX()<<","<<v2.getY()<<")="<<v1*v2<<endl;
    cout<<"("<<v2.getX()<<","<<v2.getY()<<")*("<<v3.getX()<<","<<v3.getY()<<")="<<v2*v3<<endl;
    cout<<"("<<v3.getX()<<","<<v3.getY()<<")*("<<v4.getX()<<","<<v4.getY()<<")="<<v3*v4<<endl;
    return 0;
}

Vector2D::Vector2D(int X, int Y):x(X),y(Y){}

Vector2D::Vector2D():x(0),y(0){}

void Vector2D::set(int X, int Y){
    x=X;
    y=Y;
}

int Vector2D::getX()const{
    return x;
}

int Vector2D::getY()const{
    return y;
}

int Vector2D::operator*(const Vector2D& other)const{
    return (x*other.x) + (y*other.y);

}
