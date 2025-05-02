#include "WordString.h"

void WordString::fillArrays(){

    int size=raw.size(); //stores the size of raw string
    int i=0; //iteration for the index of raw string
    int j=0; //iteration for the number of words
    int flag; //flag for the last word

    while(i<size){ //iterates through the raw string again to determine words data

        if(raw[i]!=' '){ //found the word

            flag=0; //flag is set to 0
            indices[j]=i; //index of the word is stored
            i++; //i increased

            while(i<size){ //iterates through the raw string to find the end of the word

                if(raw[i]==' '){ //end of the word is found

                    flag=1; //end is found so flag is set to 1
                    lengths[j]=i-indices[j]; //length of the word is stored
                    break; //breaks the loop
                }
                i++; //i increased
            }

            if(!flag){ //end of the word couldn't be found (it's the last word and there is no space after)
                lengths[j]=size-indices[j]; //length of the last word is stored
            }
            j++; //j increased
        }

        i++; //i increased
    }

}

int countWords(string s){
    int numberOfWords=0;
    int size=s.size(); //stores the size of string

    for(int i=0; i<size-1; i++){ //iterates through the string

        if(s[i]!=' ' && s[i+1]==' '){ //if there is a nonspace character and a space after then it's a word
            numberOfWords++; //number of words is increased
        }
    }

    //previous loop can't check if there is a word at the end of the string so we check it individually
    if(s[size-1]!=' '){ //if the last character of the word is not space then there is a word we couldn't catch
        numberOfWords++; //number of words is increased
    }

    return numberOfWords; //returns the number of words
}

WordString::WordString(){
    raw.clear(); //clears the string
    numOfWords=0; //since the string is empty there are no words

    indices=nullptr; //indices is empty
    lengths=nullptr; //lengths is empty
    isStripped=false; //false because it's not stripped initially
}

WordString::WordString(const string& s){

    raw=s; //s is our raw string
    isStripped=false; //false because it's not stripped initially

    //determining the number of words
    numOfWords=countWords(raw);
    
    //number of words determines the dynamic array sizes
    indices = new int[numOfWords]; //creates the dynamic array for indices for each word
    lengths = new int[numOfWords]; //creates the dynamic array for lengths for each word

    fillArrays();
}

WordString::WordString(const char* c):WordString(static_cast<string>(c)){
    //empty body
}

WordString::WordString(const WordString& other){

    numOfWords=other.numOfWords; //number of words is copied
    raw=other.raw; //raw string is copied
    isStripped=other.isStripped; //isStripped is copied

    //number of words determines the dynamic array sizes
    indices = new int[numOfWords]; //creates the dynamic array for indices for each word
    lengths = new int[numOfWords]; //creates the dynamic array for lengths for each word

    for(int i=0; i<numOfWords; i++){ //iterates through the dynamic data(indices and lengths)
        indices[i]=other.indices[i]; //copies the indices one by one
        lengths[i]=other.lengths[i]; //copies the lengths one by one
    }
}

WordString& WordString::operator =(const WordString& other){

    if(this==&other){ //control for self assignment
        return *this;
    }

    numOfWords=other.numOfWords; //number of words is copied
    raw=other.raw; //raw string is copied
    isStripped=other.isStripped; //isStripped is copied

    delete[] indices; //deletes the current indices to store new ones
    delete[] lengths; //deletes the current lenghts to store new ones

    //number of words determines the dynamic array sizes
    indices = new int[numOfWords]; //creates the dynamic array for indices for each word
    lengths = new int[numOfWords]; //creates the dynamic array for lengths for each word

    for(int i=0; i<numOfWords; i++){ //iterates through the dynamic data(indices and lengths)
        indices[i]=other.indices[i]; //copies the indices one by one
        lengths[i]=other.lengths[i]; //copies the lengths one by one
    }

    return *this; //returns the current object for chain operations
}

WordString operator +(const WordString& ws1, const WordString& ws2){
    return WordString(ws1.raw+" "+ws2.raw); //creates a new object combining both raw strings and returns it
}

ostream& operator <<(ostream& o, const WordString& ws){
    o<<ws.raw; //extracts the raw string
    return o; //returns the ostream object for chain operations
}

istream& operator >>(istream& i, WordString& ws){
    string newraw; //stores the read raw string
    i>>newraw; //new raw string is read
    ws=WordString(newraw); //newraw is processed using the constructor call and assigned to ws
    return i; //returns the istream object for chain operations
}

string WordString::get(int index)const{

    if(index<0 || index>=numOfWords){ //if index is invalid
        exit(1); //exits program
    }

    string word=raw.substr(indices[index], lengths[index]); //gets the word and stores it
    return word; //returns the word
}

void WordString::remove(int index){

    if(index<0 || index>=numOfWords){ //if index is invalid
        exit(1); //exits program
    }

    if(numOfWords==1){ //if it's the only word
        //before the indexed word and after the indexed word are taken as substrings, then combined
        raw=raw.substr(0,indices[index]) + raw.substr(indices[index]+lengths[index]);
        
    }

    else if(index==0){ //if it's the first word but not the only word
        //before the indexed word and after the indexed word are taken as substrings, then combined
        raw=raw.substr(0,indices[index]) + raw.substr(indices[index]+lengths[index]+1); //+1 is for the space after the word
        
    }

    else{ //if it's not the first word and the string has multiple words
        //before the indexed word and after the indexed word are taken as substrings, then combined
        raw=raw.substr(0,indices[index]-1) + raw.substr(indices[index]+lengths[index]); //-1 is for the space before the word
    }

    numOfWords--; //number of words is decreased

    delete[] indices; //deletes the current indices to store new ones
    delete[] lengths; //deletes the current lenghts to store new ones
    
    if(numOfWords==0){ //there is no word left
        indices=nullptr; //indices is null
        lengths=nullptr; //lengths is null
    }

    else{ //there are words left
        //number of words determines the dynamic array sizes
        indices = new int[numOfWords]; //creates the dynamic array for indices for each word
        lengths = new int[numOfWords]; //creates the dynamic array for lengths for each word

        fillArrays(); //indices and lengths arrays are updated
    }

}

void WordString::strip(){

    if(!isStripped){ //if string is not already stripped

        int i=0; //for iteration

        while(i<raw.size()-1){ //iterates through the raw string

            if(raw[i]==' ' && raw[i+1]==' '){ //if there is a space following another space
                raw.erase(i,1); //removes it from the raw string
            }

            else{
                i++; //increases i
            }
        }

        if(raw[0]==' '){ //if there's a single space at the beginning
            raw.erase(0,1); //removes it from the raw string
        }

        if(raw[raw.size()-1]==' '){ //if there's a single space at the end
            raw.erase(raw.size()-1,1); //removes it from the raw string
        }

        isStripped=true; //stripped the string
        fillArrays(); //indices and lengths arrays are updated
    }
    
}

void WordString::insertAfter(int index, string newword){
    int newAdded; //stores the number of new added words

    if(index<0 || index>=numOfWords){ //if index is invalid
        exit(1); //exits program
    }

    newAdded=countWords(newword);

    if(index==numOfWords-1){ //if the word is added to the end
        raw=raw + " " + newword; //the raw string + a space + the new word
    }

    else{ //if it's not added to the end
        raw=raw.substr(0,indices[index]+lengths[index]+1) + newword + " " + raw.substr(indices[index]+lengths[index]);
        
    }

    numOfWords+=newAdded; //number of words is increased

    delete[] indices; //deletes the current indices to store new ones
    delete[] lengths; //deletes the current lenghts to store new ones

    indices = new int[numOfWords]; //creates the dynamic array for indices for each word
    lengths = new int[numOfWords]; //creates the dynamic array for lengths for each word

    isStripped=false; //can be stripped now
    fillArrays(); //indices and lengths arrays are updated
}

void WordString::insertBefore(int index, string newword){ //FIX
    int newAdded;
    if(index<0 || index>=numOfWords){ //if index is invalid
        exit(1); //exits program
    }

    newAdded=countWords(newword);

    if(index==0){ //if the word is added to the beginning
        raw=newword + " " + raw; //the new word + a space + the raw string
        
    }

    else{ //if it's not added to the beginning
        index--;
        raw=raw.substr(0,indices[index]+lengths[index]+1) + newword + " " + raw.substr(indices[index]+lengths[index]);
        
    }

    numOfWords+=newAdded; //number of words is increased

    delete[] indices; //deletes the current indices to store new ones
    delete[] lengths; //deletes the current lenghts to store new ones

    indices = new int[numOfWords]; //creates the dynamic array for indices for each word
    lengths = new int[numOfWords]; //creates the dynamic array for lengths for each word

    isStripped=false; //can be stripped now
    fillArrays(); //indices and lengths arrays are updated
}

void WordString::replace(int index, string newword){
    
    if(index<0 || index>=numOfWords){ //if index is invalid
        exit(1); //exits program
    }

    if(newword!=raw.substr(indices[index],lengths[index])){ //newword shouldn't be the same with the replaced one
        
        int newAdded;
        newAdded=countWords(newword);

        //before the indexed word and after the indexed word are taken as substrings, new word is put between them
        raw=raw.substr(0,indices[index]) + newword + raw.substr(indices[index]+lengths[index]);
        
        if(newAdded!=1){ //if the new string has more than one words, number of words is changed
            numOfWords+=newAdded-1; //updates the number of words

            //number of words is changed so we need to redo the dynamic allocation 
            delete[] indices; //deletes the current indices to store new ones
            delete[] lengths; //deletes the current lenghts to store new ones

            indices = new int[numOfWords]; //creates the dynamic array for indices for each word
            lengths = new int[numOfWords]; //creates the dynamic array for lengths for each word
        }
        
        isStripped=false; //can be stripped now
        fillArrays(); //indices and lengths arrays are updated
    }
}

bool operator ==(const WordString& ws1, const WordString& ws2){
    return (ws1.raw==ws2.raw); //returns if raw strings are equal
}

int WordString::numberOfWords()const{
    return numOfWords; //returns the number of words
}

string WordString::toString()const{
    return raw; //returns the raw string
}

WordString::~WordString(){
    delete[] indices; //frees the dynamic allocated memory for indices
    delete[] lengths; //frees the dynamic allocated memory for lengths
}