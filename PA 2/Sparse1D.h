#ifndef SPARSE1D_H
#define SPARSE1D_H
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Sparse1D{
public:
    Sparse1D(string filename); //constructor that reads from a file to fill the matrix
    Sparse1D(istringstream& ss); //constructor that reads from a string stream to fill the matrix
    Sparse1D(); //default constructor

    friend Sparse1D operator+(const Sparse1D& s1, const Sparse1D& s2); //binary addition operator
    friend Sparse1D operator-(const Sparse1D& s1, const Sparse1D& s2); //binary subtraction operator

    friend Sparse1D operator-(const Sparse1D& s); //unary negation operator
    friend ostream& operator<<(ostream& o, const Sparse1D& s); //stream extraction operator

    double dot(const Sparse1D& other)const; //function for matrix dot product

    const vector<double>& getData()const; //returns a constant reference to the data vector
    const vector<int>& getIndices()const; //returns a constant reference to the indices vector

    bool addElement(int newindex, double newdata); //adds a new element to the matrix
    int getMaxIndex()const; //gets the max index
    void setMaxIndex(); //sets the max index

private:
    vector<int> indices; //vector that holds indices of the data
    vector<double> data; //vector that holds contents of the data
    int max_index; //holds the max index the matrix stores
};
#endif
