#ifndef CATALOG_H
#define CATALOG_H
#include "Item.h"
#include "BaseField.h"
#include "constants.h"
#include "Field.h"
#include "exceptions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

class Catalog{
public:
    Catalog(string datafilename, string logfilename); //constructor with the data file

    Item* parse1entry(vector<BaseField*>& format); //parses entries one by one
    void parseentries(); //parses all the entries
    void parseformat(vector<BaseField*>& format); //parses and sets the format

    void readCommands(const string& filename); //reads and uses the commands
    void read1Command(string command); //reads 1 command and uses it

    template <typename T>
    void searchByValue(const T& value, const string& field_name); //searches the catalog for the wanted value

    void printentries(int& unique_entries); //prints the entries to a log file
    void print1entry(int index);
    void printformat(); //prints the format to a log file

    void sort(string field_name); //sorts the data according to field

    ~Catalog(); //deconstructor

private:
    vector<BaseField*>format; //stores the format
    vector<Item*> items; //stores the items
    ofstream logfile; //stream for the log file
    ifstream datafile; //stream for the data file
};

#endif