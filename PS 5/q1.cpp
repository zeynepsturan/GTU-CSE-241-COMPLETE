#include <iostream>
#include <cmath>
using namespace std;

class Polynomial{
public:
    Polynomial();
    Polynomial(int deg);
    Polynomial(const Polynomial& other);
    Polynomial(double coeffs[],int deg);

    Polynomial& operator=(const Polynomial& other);
    Polynomial operator+(const Polynomial& other);
    Polynomial operator-(const Polynomial& other);
    Polynomial operator*(const Polynomial& other);

    int mySize()const{return degree;}

    double& operator[](int index);
    double operator[](int index)const;

    ~Polynomial();
private:
    int degree;
    double* coefficients;
};

double evaluate(const Polynomial& p,double d);

int main(){
    
    Polynomial empty;
    double one[] = {1};
    Polynomial One(one, 1);
    double quad[] = {3, 2, 1};
    double cubic[] = {1, 2, 0, 3};
    Polynomial q(quad, 3); // q is 3 + 2*x + x*x
    Polynomial c(cubic, 4);// c is 1 + 2*x + 0*x*x + 3*x*x*x
    Polynomial p = q; // test copy constructor
    Polynomial r;
    r = q; //test operator=
    r = c;
    cout << "Polynomial q " << endl;

    for(int i = 0; i < 3; i++){
        cout << "term with degree " << i << " has coefficient " << q[i] << endl;
    }

    cout << "Polynomial c " << endl;

    for(int i = 0; i < 4; i++){
        cout << "term with degree " << i << " has coefficient " << c[i] << endl;
    }

    cout << "value of q(2) is " << evaluate(q, 2) << endl;
    cout << "value of p(2) is " << evaluate(p, 2) << endl;
    cout << "value of r(2) is " << evaluate(r, 2) << endl;
    cout << "value of c(2) is " << evaluate(c, 2) << endl;
    
    r = q + c;
    cout << "value of (q + c)(2) is " << evaluate(r, 2) << endl;

    r = q - c;
    cout << "value of (q - c)(2) is " << evaluate(r, 2) << endl;

    r = q * c;
    cout << "size of q*c is " << r.mySize() << endl;

    cout << "Polynomial r (= q*c) " << endl;

    for(int i = 0; i < r.mySize(); i++){
        cout << "term with degree " << i << " has coefficient " << r[i] << endl;
    }

    cout << "value of (q * c)(2) is " << evaluate(r, 2) << endl;
    return 0;
}

double evaluate(const Polynomial& p,double d){
    double result=0;

    for(int i=0; i<p.mySize(); i++){
        result+=p[i]*pow(d,i);
    }

    return result;
}

Polynomial::Polynomial(){
    degree=0;
    coefficients=nullptr;
}

Polynomial::Polynomial(int deg){
    
    degree=deg;
    coefficients=new double[degree];

    for(int i=0; i<degree; i++){
        coefficients[i]=0;
    }
}

Polynomial::Polynomial(const Polynomial& other){
    degree=other.degree;
    coefficients=new double[degree];

    for(int i=0; i<degree; i++){
        coefficients[i]=other.coefficients[i];
    }
}

Polynomial& Polynomial::operator=(const Polynomial& other){

    delete[] coefficients;
    degree=other.degree;
    coefficients=new double[degree];

    for(int i=0; i<degree; i++){
        coefficients[i]=other.coefficients[i];
    }
    return *this;
}

Polynomial::Polynomial(double coeffs[],int deg){
    degree=deg;
    coefficients=new double[degree];

    for(int i=0; i<degree; i++){
        coefficients[i]=coeffs[i];
    }
}

Polynomial::~Polynomial(){
    delete[] coefficients;
}

Polynomial Polynomial::operator+(const Polynomial& other){
    int deg;
    double d1,d2;
    if(degree>other.degree) deg=degree;
    else deg=other.degree;

    Polynomial sum(deg);
    
    for(int i=0; i<deg; i++){
        if(i<degree) d1=coefficients[i]; else d1=0.0;
        if(i<other.degree) d2=other.coefficients[i]; else d2=0.0;
        sum[i]=d1+d2;
    }

    return sum;
}

Polynomial Polynomial::operator-(const Polynomial& other){
    int deg;
    double d1,d2;
    if(degree>other.degree) deg=degree;
    else deg=other.degree;

    Polynomial difference(deg);
    
    for(int i=0; i<deg; i++){
        if(i<degree) d1=coefficients[i]; else d1=0.0;
        if(i<other.degree) d2=other.coefficients[i]; else d2=0.0;
        difference[i]=d1-d2;
    }

    return difference;
}

Polynomial Polynomial::operator*(const Polynomial& other){
    int deg;
    double d1,d2;
    if(degree>other.degree) deg=degree;
    else deg=other.degree;

    Polynomial product(degree+other.degree);
    
    for(int i=0; i<deg; i++){

        for(int j=0; j<deg; j++){

            if(i<degree) d1=coefficients[i]; else d1=0.0;
            if(j<other.degree) d2=other.coefficients[j]; else d2=0.0;

            product[i+j]+=d1*d2;
        }
        
    }

    return product;
}

double& Polynomial::operator[](int index){
    if(index>=degree) exit(1);
    return coefficients[index];
}

double Polynomial::operator[](int index)const{
    if(index>=degree) exit(1);
    return coefficients[index];
}
