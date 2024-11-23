#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>
using namespace std;

#define SHOWN_ROWS 21
#define SHOWN_COLUMS 8
#define MAX_ROWS 256
#define MAX_COLUMNS 63

string col_to_str(int num); //converts numbers to column letters
int col_to_int(string str); //converts column letters to numvers

#endif