#include <iostream>
#include <string>
using namespace std;

class Student{
public:
    Student();
    Student(const Student& other);
    ~Student();

    void InputData();
    void OutputData()const;
    void ResetClasses();

    Student& operator=(const Student& other);

    string getName()const{return name;}
    int getNumClasses()const{return numClasses;}

private:
    string name;
    int numClasses;
    string* classList;
};

int main(){
    Student s1, s2;
    s1.InputData(); // Input data for student 1
    cout << "Student 1's data:" << endl;
    s1.OutputData(); // Output data for student 1
    cout << endl;
    s2 = s1;
    cout << "Student 2's data after assignment from student 1:" << endl;
    s2.OutputData(); // Should output same data as for student 1
    s1.ResetClasses();
    cout << "Student 1's data after reset:" << endl;
    s1.OutputData(); // Should have no classes
    cout << "Student 2's data, should still have original classes:" << endl;
    s2.OutputData(); // Should still have original classes
    cout << endl;
    return 0;
}

Student::Student(){
    name="";
    numClasses=0;
    classList=nullptr;
}

Student::Student(const Student& other){
    name=other.name;
    numClasses=other.numClasses;

    classList=new string[numClasses];

    for(int i=0; i<numClasses; i++){
        classList[i]=other.classList[i];
    }
}

Student& Student::operator=(const Student& other){

    name=other.name;
    numClasses=other.numClasses;

    delete[] classList;

    classList=new string[numClasses];

    for(int i=0; i<numClasses; i++){
        classList[i]=other.classList[i];
    }

    return *this;
}

Student::~Student(){
    delete[] classList;
}

void Student::ResetClasses(){
    numClasses=0;

    delete[] classList;
    classList=nullptr;
}

void Student::InputData(){

    cout<<"Name: ";
    cin>>name;

    cout<<"Number of classes: ";
    cin>>numClasses;

    classList=new string[numClasses];
    
    for(int i=0; i<numClasses; i++){
        cin>>classList[i];
    }

}

void Student::OutputData()const{

    cout<<"Name: "<<name<<endl;

    cout<<"Number of classes: "<<numClasses<<endl;
    
    for(int i=0; i<numClasses; i++){
        cout<<i+1<<". "<<classList[i]<<endl;
    }

}