#include "Sparse1D.h"

Sparse1D::Sparse1D(string filename){
    ifstream file; //object for input file stream
    file.open(filename); //opening the file
    char c; //for reading chars from the file
    double d; //for reading doubles from the file
    int i; //for reading intigers from the file
    
    if(!file.is_open()){ //if file cannot be opened
        exit(1); //program ends
    }

    while(file>>i){ //while the file isn't ended, reads the index first

        indices.push_back(i); //stores the index
        file>>c; //reads |
        file>>d; //reads the data
        data.push_back(d); //stores the data 
    }
    file.close(); //closes the file
    setMaxIndex(); //uploads the max index
}

Sparse1D::Sparse1D(istringstream& ss){
    
    char c; //for reading chars from the file
    double d; //for reading doubles from the file
    int i; //for reading intigers from the file

    while(ss>>i){ //while the file isn't ended, reads the index first

        indices.push_back(i); //stores the index
        ss>>c; //reads |
        ss>>d; //reads the data
        data.push_back(d); //stores the data 
    }

    setMaxIndex(); //uploads the max index
}

Sparse1D::Sparse1D(){ //default constructor
    max_index=-1; //the matrix is empty in default so max index is set to -1
}

ostream& operator<<(ostream& o, const Sparse1D& s){
    int size=s.indices.size(); //holds the size of the matrix s

    if(size>0){ //if the matrix isn't empty
        o<<s.indices[0]<<"|"<<s.data[0]; //prints the first element of the matrix
        for(int i=1; i<size; i++){ //iterates through the remaining matrix
            o<<" "<<s.indices[i]<<"|"<<s.data[i]; //prints the remaining elements seperated by a space
        }
    }

    return o; //returns the ostream object for chained << operations
}

Sparse1D operator-(const Sparse1D& s){
    Sparse1D temp=s; //creates a temporary object to store negated matrix and assignes to the main matrix
    int size=s.data.size(); //stores the size of the matrix

    for(int i=0; i<size; i++){ //iterates through the matrix
        temp.data[i]=-temp.data[i]; //negates all the elements of the matrix
    }

    return temp; //returns the negated matrix
}

Sparse1D operator+(const Sparse1D& s1, const Sparse1D& s2){
    Sparse1D temp; //creates a temporary object to store the matrix sum
    int i=0; //for tracking s1
    int j=0; //for tracking s2

    while(i<s1.indices.size() && j<s2.indices.size()){ //iterates through the both matrices until one is done
        
        if(s1.indices[i]==s2.indices[j]){ //if the indices are the same

            if(s1.data[i]+s2.data[j]!=0){ //if the sum is 0 we won't store that
                temp.indices.push_back(s1.indices[i]); //stores the index
                temp.data.push_back(s1.data[i]+s2.data[j]); //stores the sum
            }
            i++; //goes to the next s1 index
            j++; //goes to the next s2 index
        }
    
        else if(s1.indices[i]<s2.indices[j]){ //s1 index is lower so there can't be any addition, we store the s1 data
            temp.indices.push_back(s1.indices[i]); //stores the index
            temp.data.push_back(s1.data[i]); //stores the data
            i++; //goes to the next s1 index
        }
    
        else{ //s2 index is lower so there can't be any addition, we store the s2 data
            temp.indices.push_back(s2.indices[j]); //stores the index
            temp.data.push_back(s2.data[j]); //stores the data
            j++; //goes to the next s2 index
        }

    }
    //if there are s1 values remaining we just store them
    while(i<s1.indices.size()){ //iterates through the remaining s1 elements
        temp.indices.push_back(s1.indices[i]); //stores the index
        temp.data.push_back(s1.data[i]); //stores the data
        i++; //goes to the next s1 index
    }

    //if there are s2 values remaining we just store them
    while(j<s2.indices.size()){ //iterates through the remaining s2 elements
        temp.indices.push_back(s2.indices[j]); //stores the index
        temp.data.push_back(s2.data[j]); //stores the data
        j++; //goes to the next s2 index
    }
    temp.setMaxIndex(); //sets the max index of temp
    return temp; //returns the matrix sum
}

Sparse1D operator-(const Sparse1D& s1, const Sparse1D& s2){
    Sparse1D temp=s1+(-s2); //does s1 sum negative s2 for efficiency
    temp.setMaxIndex(); //sets the max index of temp
    return temp; //returns the result matrix 
}

double Sparse1D::dot(const Sparse1D& other)const{
    int i=0; //for tracking member
    int j=0; //for tracking other
    double result=0.0; //holds the dot product result

    while(i<indices.size() && j<other.getIndices().size()){ //iterates through the both matrices until one is done
        
        if(indices[i]==other.indices[j]){ //if the indices are the same
            result+=(data[i])*(other.data[j]); //multiplies the datas and adds to the result
            i++; //goes to the next member index
            j++; //goes to the next other index
        }
    
        else if(indices[i]<other.indices[j]){ //member index is lower so there can't be any multiplication, we iterate
            i++; //goes to the next member index
        }
    
        else{ //other index is lower so there can't be any multiplication, we iterate
            j++; //goes to the next other index
        }

    }
    return result; //returns the dot product
}

bool Sparse1D::addElement(int newindex, double newdata){

    //matrix is in ascending order so it must check before adding elements
    if(newindex>max_index){ //if the matrix is empty or new index is greater than the max index
        indices.push_back(newindex); //adds the new index
        data.push_back(newdata); //adds the new data

        max_index=newindex; //max index is the new index now
        return true; //element is added succesfully so it returns true 
    }
    return false; //element couldn't be added so returns false
}

const vector<double>& Sparse1D::getData()const{
    return data; //returns a constant reference to the data
}

const vector<int>& Sparse1D::getIndices()const{
    return indices; //returns a constant reference to the indices
}

int Sparse1D::getMaxIndex()const{
    return max_index; //returns the max index
}

void Sparse1D::setMaxIndex(){
    if(indices.empty()){ //if the matrix is empty
        max_index=-1; //sets max index to -1
    }

    else{ //if it's not empty
        max_index=indices.back(); //finds the last added index and assigns to max index
    }
}