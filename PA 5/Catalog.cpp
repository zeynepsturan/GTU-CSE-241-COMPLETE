#include "Catalog.h"

Catalog::Catalog(string datafilename, string logfilename){
    int unique_entries=0;

    datafile.open(datafilename); //opens the datafile
    if(!datafile.is_open()){ //if the file couldn't be opened
        throw FileOpeningError(datafilename); //throws an exception
    }
    
    logfile.open(logfilename); //opens the logfile
    if(!logfile.is_open()){ //if the file couldn't be opened
        throw FileOpeningError(datafilename); //throws an exception
    }

    parseformat(this->format); //parses the format first
    parseentries(); //then parses the entries

    printformat(); //prints the format
    logfile<<endl;
    printentries(unique_entries); //prints the entries and calculates the number of unique entries
    logfile<<endl<<unique_entries<<" unique entries"<<endl; //prints the number of unique entries
}

void Catalog::parseentries(){
    Item* i; //stores the parsed item

    while(true){ //parses thw whole file
        i=parse1entry(format); //parses the item and stores it

        if(i==nullptr){ //if there is no item left
            break; //breaks the loop
        }

        else{
            if(i->getFilled()!=format.size()){ //if all the fields of the new item i are not filled
                i->setValid(false); //set to invalid
            }

            else{ //if all the fields of the new item i are filled
                i->setValid(true); //set to valid
            }
            items.push_back(i); //items are added to the catalog
        }
    }
}

Item* Catalog::parse1entry(vector<BaseField*>& format){
    string line; //gets a line from the file

    string field; //stores the field
    string name, type, isArray; //stores the field name, type and array info

    if(!getline(datafile,line)){ //if there is nothing to parse
        return nullptr;
    }

    Item* newitem; //stores the parsed item
    newitem=new Item(format); //creates an item object suitable with the format
    istringstream formatinfo(line); //line is used as stringstream

    int i=0; //stores index

    while(getline(formatinfo, field, '|') && i<format.size()){ //while there is data
        newitem->addData(field, i); //adds the new data
        i++; //i increases
    }

    newitem->setFilled(i); //sets the number of fields filled
    return newitem; //returns the new item
}

Catalog::~Catalog(){
    for(auto item:items){ //iterates through the items
        delete item; //deletes the items one by one
    }
    items.clear(); //clears the vector

    for(auto field:format){ //iterates through the format
        delete field; //deletes the fields one by one
    }
    format.clear(); //clears the vector
}

void Catalog::parseformat(vector<BaseField*>& format){
    string firstline; //stores the first line(format line) of the datafile
    getline(datafile,firstline); //gets the first line

    istringstream formatinfo(firstline); //uses the first line as stringstream

    string field; //stores the fields
    string name, type, isArray; //stores the field name, type and array info

    while(getline(formatinfo, field, '|')){ //gets the fields
        istringstream fieldinfo(field); ////uses the field as stringstream
        BaseField* newfield;

        if(getline(fieldinfo, name, ':') && getline(fieldinfo, type, ':') && getline(fieldinfo, isArray)){
            bool arrayinfo; //stores the array info

            if(isArray==SINGLE){ //if it's not an array
                arrayinfo=false; //array info is set
            }
            
            else if(isArray==ARRAY){ //if it's an array
                arrayinfo=true; //array info is set
            }
            
            if(type==STRING){
                newfield=new Field<string>(name, type, arrayinfo); //new string field is created
            }

            else if(type==INTEGER){
                newfield=new Field<int>(name, type, arrayinfo); //new integer field is created
            }
            else if(type==DOUBLE){
                newfield=new Field<double>(name, type, arrayinfo); //new double field is created
            }

            else if(type==BOOL){
                newfield=new Field<bool>(name, type, arrayinfo); //new bool field is created
            }
        }
        
        format.push_back(newfield); //adds the newfield to the format
        newfield=nullptr; //frees the pointer
    }
}

void Catalog::read1Command(string command){
    command.erase(remove(command.begin(), command.end(), '\r'), command.end()); //erases if there is any \r's

    istringstream commandstream(command); //stream to parse the command
    string commandword; //stores the command word
    string value_str; //stores the value in the command
    string field_name; //stores the field name
    string in; //stores extras

    commandstream>>commandword; //gets the command word

    if(commandword=="search"){ //if the command is search
        commandstream>>value_str>>in>>field_name; //stores value and field name

        if(command!="search "+value_str+" in "+field_name){ //if the command isn't exactly in the correct format
            throw WrongCommandError(); //throws an exception
        }

        field_name=field_name.substr(1,field_name.size()-2); //deletes the quotes in the field name
        value_str=value_str.substr(1,value_str.size()-2); //deletes the quotes in the data value

        BaseField* targetField=nullptr; //pointer for pointing to fields
        for(auto f:format){ //iterates through the format
            if(f->getFieldName()==field_name){ //if the correct field is found
                targetField=f; //field is stored
                break; //breaks the loop
            }
        }

        if(!targetField){ //if the field couldn't be found
            throw WrongCommandError(); //throws an exception
        }
        logfile<<command<<endl; //prints it to the logfile

        string type=targetField->getFieldType(); //gets the field type

        if(type==STRING){
            searchByValue<string>(value_str, field_name); //search function is called
        }

        else if(type==INTEGER){
            searchByValue<int>(stoi(value_str), field_name); //search function is called
        }

        else if(type==DOUBLE){
            searchByValue<double>(stod(value_str), field_name); //search function is called
        }

        else if(type==BOOL){
            bool b=(value_str == "true" || value_str == "1");
            searchByValue<bool>(b, field_name); //search function is called
        }

        else{ //if the type is invalid
            cout<<"Unknown type: "<<type<<endl;
        }
    }

    else if(commandword=="sort"){ //if the command is sort
        commandstream>>field_name; //gets the fieldname for sorting

        if(command!="sort "+field_name){ //if the command isn't exactly in the correct format
            throw WrongCommandError(); //throws an exception
        }

        field_name=field_name.substr(1,field_name.size()-2); //deletes the quotes in the fieldname

        BaseField* targetField=nullptr; //pointer for pointing to fields
        for(auto f:format){ //iterates through the format

            if(f->getFieldName()==field_name){ //if the correct field is found
                targetField=f; //field is stored
                break; //breaks the loop
            }
        }

        if(!targetField){ //if the field couldn't be found
            throw WrongCommandError(); //throws an exception
        }
        logfile<<command<<endl; //prints it to the logfile

        sort(field_name); //sort function is called
    }
}

void Catalog::readCommands(const string& filename){
    ifstream commandfile(filename); //stream for the commandfile
    string command; //stores the each command

    while(getline(commandfile, command)){ //gets the each command in the file line by line

        try{
            read1Command(command); //reads and uses each command
        }
        
        catch(runtime_error& r){ //catches exceptions
            logfile<<r.what()<<endl; //prints them to the log file
            logfile<<command<<endl;
        }
    }
}

void Catalog::printformat(){
    int size=format.size(); //stores the number of fields in the format

    if(size>0){ //if format isn't empty
        logfile<<format[0]->getFieldName(); //prints the first field name to the logfile

        for(int i=1; i<size; i++){ //iterates through the format
            logfile<<"|"<<format[i]->getFieldName(); //prints the rest of the field names to the logfile
        }
    }
}

void Catalog::printentries(int& unique_entries){
    int size=items.size(); //stores the number of items

    for(int i=0; i<size; i++){ //iterates through the items

        try{
            print1entry(i); //prints entries one by one
        }

        catch(MissingFieldError& m){ //catches missing field exceptions
            logfile<<m.what()<<endl; //prints the exception to the logfile
            logfile<<items[i]->getPrintable(); //prints the item to the logfile
        }

        catch(DuplicateEntryError &d){//catches duplicate entry exceptions
            logfile<<d.what()<<endl; //prints the exception to the logfile
            logfile<<items[i]->getPrintable(); //prints the item to the logfile
        }

        bool flag=false;
        for(int j=0; j<i; j++){ //iterates through the previous items to check repetition

            Field<string>* f1=dynamic_cast<Field<string>*>(items[i]->getData()[0]); //pointer for the first fields data
            Field<string>* f2=dynamic_cast<Field<string>*>(items[j]->getData()[0]); //pointer for the first fields data

            if(f1 && f2 && f1->getData()[0]==f2->getData()[0] && items[j]->getValid()){ //if they are the same, there is repetition
                flag=true; //flag is set
                break; //breaks the loop
            }
        }

        if(!flag && items[i]->getValid()){ //if no repetition and item is valid
            unique_entries++; //unique entries increases
        }
        
    }
}

void Catalog::print1entry(int index){
    bool flag; //flag to check repetition

    if(items[index]->getFilled()!=format.size()){ //if the item is not fully filled
        throw MissingFieldError(); //throws an exception
    }
    
    for(int i=0; i<index; i++){ //iterates through the previous items
        flag=false; //flag is false in default

        Field<string>* f1=dynamic_cast<Field<string>*>(items[i]->getData()[0]); //pointer for the first fields data
        Field<string>* f2=dynamic_cast<Field<string>*>(items[index]->getData()[0]); //pointer for the first fields data

        if(f1 && f2 && f1->getData()[0]==f2->getData()[0] && items[i]->getValid()){ //if they are the same, there is repetition
            flag=true; //flag is set
            break; //breaks the loop
        }
    }

    if(flag){ //if there is repetition
        throw DuplicateEntryError(); //throws an exception
    }
}

void Catalog::sort(string field_name){

    int index=-1; //index is initially -1
    int size=format.size(); //stores the number of fields in the format

    for(int i=0; i<size; i++){ //iterates through the format to determine the wanted field's index

        if(format[i]->getFieldName()==field_name){ //if the field is found
            index=i; //index is stored;
            break; //breaks the loop
        }
    }

    if(index==-1){ //if the field couldn't be found
        throw MissingFieldError(); //throws an exception
    }

    std::sort(items.begin(), items.end(), [index](Item* a, Item* b){ //lambda function definition:

        if(a->getValid() && b->getValid()){ //a and b must be valid to sort
            BaseField* fa=a->getData()[index]; //gets the field at the specified index from the first item
            BaseField* fb=b->getData()[index]; //gets the field at the specified index from the second item

            if(auto f1 = dynamic_cast<Field<int>*>(fa)){ //tries to cast the first field to Field<int>
                auto f2 = dynamic_cast<Field<int>*>(fb); //tries to cast the second field to Field<int>
                if(f1 && f2) return f1->getData()<f2->getData(); //compares data vectors
            }

            if(auto f1=dynamic_cast<Field<string>*>(fa)){ //tries to cast the first field to Field<string>
                auto f2=dynamic_cast<Field<string>*>(fb); //tries to cast the second field to Field<string>
                if(f1 && f2) return f1->getData()<f2->getData(); //compares data vectors
            }

            if(auto f1=dynamic_cast<Field<double>*>(fa)){ //tries to cast the first field to Field<double>
                auto f2=dynamic_cast<Field<double>*>(fb); //tries to cast the second field to Field<double>
                if(f1 && f2) return f1->getData()<f2->getData(); //compares data vectors
            }

            if(auto f1=dynamic_cast<Field<bool>*>(fa)){ //tries to cast the first field to Field<bool>
                auto f2=dynamic_cast<Field<bool>*>(fb); //tries to cast the second field to Field<bool>
                if(f1 && f2) return f1->getData()<f2->getData(); //compares data vectors
            }

            return false; //if none of the types matched, consider them equal (no sorting)
        }
        return false; //if none of the types matched, consider them equal (no sorting)
    });
    
    int isize=items.size(); //stores the number of items

    if(isize>0){
        logfile<<items[0]->getPrintable(); //prints the first item

        for(int i=1; i<isize; i++){ //iterates through the items

            bool flag=false; //flag to check repetition
            for(int j=0; j<i; j++){ //iterates through the previous items

                Field<string>* f1=dynamic_cast<Field<string>*>(items[i]->getData()[0]); //pointer for the first fields data
                Field<string>* f2=dynamic_cast<Field<string>*>(items[j]->getData()[0]); //pointer for the first fields data

                if(f1 && f2 && f1->getData()[0]==f2->getData()[0] && items[j]->getValid()){ //if they are the same, there is repetition
                    flag=true; //flag is set
                    break; //breaks the loop
                }
            }

            if(!flag){ //if there is no repetition

                if(items[i]->getValid()){ //if the item is valid (if all the fields of the item are filled)
                    logfile<<endl<<items[i]->getPrintable(); //prints the item to the logfile
                }
            }
        }
        logfile<<endl;
    } 
}

//comparision for type string
template<typename T>
typename enable_if<is_same<T,string>::value, bool>::type
matches(const T& field_value, const T& target){
    return field_value.find(target)!=string::npos;
}

//comparision for the other types
template<typename T>
typename enable_if<!is_same<T, string>::value, bool>::type
matches(const T& field_value, const T& target){
    return field_value == target;
}


template <typename T>
void Catalog::searchByValue(const T& value, const string& field_name){
    int index=-1; //index is -1 initially
    int size=format.size(); //stores the number of fields in the format

    for(int i=0; i<size; i++){ //iterates through the format fields

        if(format[i]->getFieldName()==field_name){ //if the field is found
            index=i; //it's index is stored
            break; //breaks the loop
        }
    }

    int i=0;
    for(auto item:items){ //iterates through the items
        
        if(!(item->getValid())){ //if item is not valid, contiunes to the next item
            i++;
            continue;
        }

        Field<T>* f=dynamic_cast<Field<T>*>(item->getData()[index]); //f points to the item's data

        if(!f){ //if f is empty
            continue; //passes to the next item
        }

        const auto& vec=f->getData(); //vec points to the field data

        for(const auto& element:vec){ //iterates through the data elements

            if(matches(element,value)){ //if the value is found
                bool flag=false; //flag for repetition
                for(int j=0; j<i; j++){

                    Field<string>* f1=dynamic_cast<Field<string>*>(items[i]->getData()[0]); //pointer for the first fields data
                    Field<string>* f2=dynamic_cast<Field<string>*>(items[j]->getData()[0]); //pointer for the first fields data


                    if(f1 && f2 && f1->getData()[0]==f2->getData()[0] && items[j]->getValid()){ //if they are the same, there is repetition
                        flag=true; //flag is set
                        break; //breaks the loop
                    }
                }

                if(!flag){
                    logfile<<items[i]->getPrintable(); //prints the item to the logfile
                }
                break; //breaks the loop
            }
        }
        i++; //i is increased
    }
}