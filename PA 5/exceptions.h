#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <iostream>
using namespace std;

class FileOpeningError:public runtime_error{
public:
    FileOpeningError():runtime_error("The file cannot be opened."){}
    FileOpeningError(const string& filename):runtime_error(filename +" cannot be opened."){}
};

class MissingFieldError:public runtime_error{
public:
    MissingFieldError():runtime_error("Exception: missing field"){}
};

class DuplicateEntryError:public runtime_error{
public:
    DuplicateEntryError():runtime_error("Exception: duplicate entry"){}
};

class WrongCommandError:public runtime_error{
public:
    WrongCommandError():runtime_error("Exception: command is wrong"){}
};
#endif