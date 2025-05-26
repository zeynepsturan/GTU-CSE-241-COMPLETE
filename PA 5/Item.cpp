#include "Item.h"

Item::Item(){
    filled_field=0;
    data.clear(); //data is empty initially
}

Item::Item(const vector<BaseField*>& format){

    filled_field=0;
    for(BaseField* field:format){ //iterates through the format fields
        string name=field->getFieldName(); //stores the type of the field
        string type=field->getFieldType(); //stores the name of the field
        bool is_array = field->getIsArray(); //stores the array info of the field

        if(type==STRING){
            data.push_back(new Field<string>(name, type, is_array)); //new string field is created and added to data
        }

        else if(type==INTEGER){
            data.push_back(new Field<int>(name, type, is_array)); //new integer field is created and added to data
        }

        else if(type==DOUBLE){
            data.push_back(new Field<double>(name, type, is_array)); //new double field is created and added to data
        }

        else if(type==BOOL){
            data.push_back(new Field<bool>(name, type, is_array)); //new bool field is created and added to data
        }
    }
}

Item::~Item(){
    int size=data.size(); //stores the size of the data
    for(int i=0; i<size; i++){ //iterates through the data
        delete data[i]; //deletes data one by one
    }
}

void Item::setFilled(int i){
    filled_field=i; //filled_field is set
}

void Item::setValid(bool b){
    isValid=b; //isValid is set
}

string Item::getPrintable(){
    string printable; //stores the printable string

    if(filled_field>0){ //if data isn't empty
        printable+=data[0]->getDataAsString(); //adds the data as string to the printable string

        for(int i=1; i<filled_field; i++){ //iterates through the data
            printable+="|"+data[i]->getDataAsString(); //adds the data as string to the printable string
        }
    }
    
    return printable; //returns the printable string
}

void Item::addData(string raw, int index){
    BaseField* field=data[index]; //points to the field data will be added
    string type=field->getFieldType(); //stores the field type
    bool isArray=field->getIsArray(); //stores the array info

    vector<string> tokens; //vector that stores the data/s
    if(isArray){ //if the data is an array
        string token; //stores one single data
        istringstream ss(raw); //stringstream to parse the data
        while(getline(ss,token,':')){ //while there is data, it's stored
            tokens.push_back(token); //data is added to tokens vector
        }
    }
    
    else{ //if it's a single data
        tokens.push_back(raw); //data is added to tokens vector
    }

    if(type==STRING){
        Field<string>* f=dynamic_cast<Field<string>*>(field); //points to the field data will be added

        if(f){ //if f isn't null
            f->data.clear(); //clears the previous data
            for(const string& token:tokens){ //iterates through the tokens vector (our new data)
                f->data.push_back(token); //adds the data directly since the type is string
            }
        }

        filled_field++;
    }

    else if(type==INTEGER){
        Field<int>* f=dynamic_cast<Field<int>*>(field); //points to the field data will be added

        if(f){ //if f isn't null
            f->data.clear(); //clears the previous data
            for(const string& token:tokens){ //iterates through the tokens vector (our new data)
                int val; //stores the data in the correct type
                stringstream(token)>>val; //string is converted to int
                f->data.push_back(val); //adds the data
            }
        }
        filled_field++;
    }

    else if(type==DOUBLE){
        Field<double>* f=dynamic_cast<Field<double>*>(field); //points to the field data will be added

        if(f){ //if f isn't null
            f->data.clear(); //clears the previous data
            for(const string& token:tokens){ //iterates through the tokens vector (our new data)
                double val; //stores the data in the correct type
                stringstream(token)>>val; //string is converted to double
                f->data.push_back(val); //adds the data
            }
        }
        filled_field++;
    }

    else if(type==BOOL){ //if f isn't null
        Field<bool>* f=dynamic_cast<Field<bool>*>(field); //points to the field data will be added

        if(f){
            f->data.clear(); //clears the previous data
            for(const string& token:tokens){ //iterates through the tokens vector (our new data)
                bool val=(token=="multi" || token=="true" || token=="1"); //stores the data in the correct type
                f->data.push_back(val); //adds the data
            }
        }
        filled_field++;
    }
}