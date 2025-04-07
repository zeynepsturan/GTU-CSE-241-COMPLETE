#include "Sparse2D.h"

Sparse2D::Sparse2D(){ //default constructor
    max_row_index=-1; //the matrix is empty in default so max index is set to -1
}

Sparse2D::Sparse2D(string filename){
    ifstream file; //object for input file stream
    string s; //for storing file line by line
    int i; //for reading intigers from the string

    file.open(filename); //opening the file
    
    if(!file.is_open()){ //if file cannot be opened
        exit(1); //program ends
    }

    while(getline(file, s)){ //while the file isn't ended reads line by line
        istringstream ss(s); //string stream is used for Sparse1D constuctor

        ss>>i; //reads the rows index
        row_indices.push_back(i); //stores the index

        data.push_back(Sparse1D(ss)); //creates a Sparse1D object that reads the row then adds to the Sparse2D object
    }

    file.close(); //closes the file
    setMaxIndices(); //sets the max row index and each row's max index
}

ostream& operator<<(ostream& o, const Sparse2D& s){
    int size=s.row_indices.size(); //stores the number of rows

    if(size>0){ //if the matrix isn't empty

        for(int i=0; i<size; i++){ //iterates through the rows
            o<<s.row_indices[i]<<" "; //prints <row number> and a space
            o<<s.data[i]<<endl; //prints the whole row(using the Sparse1D << operator definition) and a new line
        }
    }

    return o; //returns the ostream object for chained << operations
}

Sparse2D operator+(const Sparse2D& s1, const Sparse2D& s2){ //has the same logic with Sparse1D + operation but does it row by row
    Sparse2D temp; //creates a temporary object to store the matrix sum
    int i=0; //for tracking s1
    int j=0; //for tracking s2

    while(i<s1.row_indices.size() && j<s2.row_indices.size()){ //iterates through the both matrices' rows until one is done
        
        if(s1.row_indices[i]==s2.row_indices[j]){ //if the row indices are the same

            if(!(s1.data[i]+s2.data[j]).getData().empty()){ //the sum matrix shouldn't be empty
                temp.row_indices.push_back(s1.row_indices[i]); //stores the row index
                temp.data.push_back(s1.data[i]+s2.data[j]); //sums the rows using Sparse1D + operator
            }

            i++; //goes to the next s1 row index
            j++; //goes to the next s2 row index
        }
    
        else if(s1.row_indices[i]<s2.row_indices[j]){ //s1 row index is lower so there can't be any addition, we store the s1 row[i] data
            temp.row_indices.push_back(s1.row_indices[i]); //stores the row index
            temp.data.push_back(s1.data[i]); //stores the whole row data
            i++; //goes to the next s1 row index
        }
    
        else{ //s2 row index is lower so there can't be any addition, we store the s2 row[i] data
            temp.row_indices.push_back(s2.row_indices[j]); //stores the row index
            temp.data.push_back(s2.data[j]); //stores the whole row data
            j++; //goes to the next s2 row index
        }

    }
    //if there are s1 rows remaining we just store them
    while(i<s1.row_indices.size()){ //iterates through the remaining s1 rows
        temp.row_indices.push_back(s1.row_indices[i]); //stores the row index
        temp.data.push_back(s1.data[i]); //stores the whole row
        i++; //goes to the next s1 row index
    }

    //if there are s2 rows remaining we just store them
    while(j<s2.row_indices.size()){ //iterates through the remaining s2 rows
        temp.row_indices.push_back(s2.row_indices[j]); //stores the row index
        temp.data.push_back(s2.data[j]); //stores the whole row
        j++; //goes to the next s2 row index
    }

    temp.setMaxIndices(); //sets the temp's max row index and each row's max index
    return temp; //returns the matrix sum
}

Sparse2D operator-(const Sparse2D& s){
    Sparse2D temp=s; //creates a temporary object to store negated matrix and assignes to the main matrix
    int size=s.data.size(); //stores the number of rows of the matrix

    for(int i=0; i<size; i++){ //iterates through the rows
        temp.data[i]=-temp.data[i]; //negates all the rows of the matrix using Sparse1D negation operator
    }

    return temp; //returns the negated matrix
}

Sparse2D operator-(const Sparse2D& s1, const Sparse2D& s2){
    Sparse2D temp=s1+(-s2); //does s1 sum negative s2 for efficiency

    temp.setMaxIndices(); //sets the temp's max row index and each row's max index
    return temp; //returns the result matrix
}

Sparse2D operator*(const Sparse2D& s1, const Sparse2D& s2){
    Sparse2D temp; //stores the matrix product
    double d; //stores dot products

    int col_size=s2.getColSize(); //stores the max num of cols s2 has
    
    vector<Sparse1D>columns(col_size); //stores the s2 column by column for efficiency

    for(int j=0; j<col_size; j++){ //iterates through each column
        columns[j]=s2.column(j); //creates the column and stores it
    }

    for(int i=0; i<s1.getRowIndices().size(); i++){ //iterates through s1's rows
        
        for(int j=0; j<col_size; j++){ //iterates through s2's columns
            
            d=s1.getData()[i].dot(columns[j]); //calculates the dot product and stores it

            if(d!=0){ //if the dot product is 0, it's ignored
                //std::cout<<s1.getRowIndices()[i]<<" "<<j<<" "<<d<<endl;
                temp.addElement(s1.getRowIndices()[i],j,d); //it adds the element
            }
        }
    }

    temp.setMaxIndices(); //sets the temp's max row index and each row's max index
    return temp; //returns the matrix product
}

Sparse2D Sparse2D::transpose()const{
    Sparse2D temp; //stores the transpose matrix
    int col_size=(*this).getColSize(); //stores the max num of cols s2 has

    for(int i=0; i<col_size; i++){ //iterates through the columns
        
        Sparse1D column=(*this).column(i); //stores the columns
        Sparse1D newrow; //holds the column but with right indices

        if(column.getMaxIndex()!=-1){ //if the current column is not empty
            for(int i=0;i<column.getIndices().size() ;i++){ //iterates through the column object
                newrow.addElement(column.getIndices()[i],column.getData()[i]); //adds the column element with right indices to newrow object
            }

            temp.addRow(i,newrow); //adds the new row to the temp object
        }
        
    }
    
    temp.setMaxIndices(); //sets the temp's max row index and each row's max index
    return temp; //returns the transpoze
}

bool Sparse2D::addRow(int newrowindex, Sparse1D& row){

    if(newrowindex>max_row_index){ //if the matrix is empty or new row index is greater than the max row index
        row_indices.push_back(newrowindex); //adds the new index
        data.push_back(row); //creates an empty Sparse1D object and adds it to the data

        max_row_index=newrowindex; //updates the new row index
        return true;
    }

    return false; //row couldn't be added so returns false
}

bool Sparse2D::addElement(int rowindex, int newindex, double newdata){

    int size=row_indices.size(); //stores the number of rows

    //matrix is in ascending order so it must check before adding elements
    if(rowindex>max_row_index){ //if the matrix is empty or new row index is greater than the max row index
        row_indices.push_back(rowindex); //adds the new row index
        data.push_back(Sparse1D()); //creates an empty Sparse1D object and adds it to the data

        data[size].addElement(newindex, newdata); //adds the new data and the index using Sparse1D addElement function
        max_row_index=rowindex; //updates the new row index

        return true; //row is added succesfully so it returns true
    }

    else{ //row already exists so it only adds the element to the row

        for(int i=0; i<row_indices.size();i++){ //searches for the asked row

            if(row_indices[i]==rowindex){ //if the row is found
                return data[i].addElement(newindex, newdata); //returns if the element is added otherwise returns false
            }
        }
    }

    return false; //element couldn't be added so returns false
}

int Sparse2D::getColSize()const{
    int col_size=0; //holds the column size
    int size; //temporary variable to hold number of current row's elements

    for(int i=0; i<data.size(); i++){ //iterates through s2 rows
        size=data[i].getMaxIndex()+1; //stores the current row's number of elements

        if(size>col_size){ //if current row's element count is greater stores it
            col_size=size;
        }
    }
    return col_size; //returns the column size
}

Sparse1D Sparse2D::column(int column_index)const{
    Sparse1D temp; //stores the column
    int size=row_indices.size(); //stores the number of rows

    for(int i=0; i<size; i++){ //iterates through the rows

        if(data[i].getMaxIndex()>=column_index){ //if the column_index cannot appear in the row we don't search for it

            for(int j=0; j<data[i].getIndices().size(); j++){ //iterates through the current rows elements

                if(data[i].getIndices()[j]==column_index){ //if the row has the #column_index element
                    temp.addElement(row_indices[i], data[i].getData()[j]); //adds the element to the column object
                    break; //breaks the loop
                }
            }
        }
    }

    temp.setMaxIndex(); //sets the temp's max index
    return temp; //returns the column object
}

Sparse1D& Sparse2D::row(int row_index){
    int size=row_indices.size();//stores the number of rows

    if(row_index<=max_row_index){ //checks if row_index might be valid

        for(int i=0; i<size; i++){ //iterates through row indices
            if(row_indices[i]==row_index){ //if the row is found
                return data[i]; //returns the 2D matrix's #row_index row(Sparse1D matrix)
            }
        }
    }
    
    static Sparse1D empty; //creates an empty Sparse1D object
    return empty; //returns the empty matrix
}

const vector<Sparse1D>& Sparse2D::getData()const{
    return data; //returns a constant reference to the data
}

const vector<int>& Sparse2D::getRowIndices()const{
    return row_indices; //returns a constant reference to the row indices
}

int Sparse2D::getMaxRowIndex()const{
    return max_row_index; //returns the max row index
}

void Sparse2D::setMaxIndices(){

    if(row_indices.empty()){ //if the matrix is empty
        max_row_index=-1; //sets max row index to -1
    }

    else{ //if it's not empty
        max_row_index=row_indices.back(); //finds the last added row index and assigns to max index

        for(auto& i:data){ //iterates through the rows
            i.setMaxIndex(); //sets each row's max index
        }
    }
}