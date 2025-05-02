#ifndef WORDSTRING_H
#define WORDSTRING_H
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class WordString{
public:
    WordString(); //no parameter constructor
    WordString(const string& s); //constructor initializes parameter s as the raw string
    WordString(const char* s); //constructor takes a c string parameter
    WordString(const WordString& other); //copy constructor

    friend ostream& operator <<(ostream& o, const WordString& ws); //stream extraction operator
    friend istream& operator >>(istream& i, WordString& ws); //stream insertion operator

    friend WordString operator +(const WordString& ws1, const WordString& ws2); //combines two WordStrings
    friend bool operator ==(const WordString& ws1, const WordString& ws2); //is equal operator

    WordString& operator =(const WordString& other); //assignment operator

    string toString()const; //returns the raw string
    string get(int index)const; //returns the index*th word in the string

    int numberOfWords()const; //returns the number of words in the string

    void replace(int index, string newword); //replaces the index*th word with a new word
    void remove(int index); //removes the index*th word from the string

    void insertAfter(int index, string newword); //inserts a new string after the index*th word
    void insertBefore(int index, string newword); //inserts a new string before the index*th word

    void strip(); //strips the unnecessary spaces within the string

    ~WordString(); //deconstructor

private:
    string raw; //holds the raw string
    int numOfWords; //stores the # of words in the string
    bool isStripped; //flag for stripping

    int* indices; //dynamically allocates memory for storing word indices
    int* lengths; //dynamically allocates memory for storing word lengths

    void fillArrays(); //fills the indices and lengths arrays
};

#endif
