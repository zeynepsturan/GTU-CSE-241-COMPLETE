#include <iostream>
#include "pfarrayd.h"


using namespace std;

OutOfRange::OutOfRange(string thisMessage, int thisIndex) : message(thisMessage), index(thisIndex) {}

string OutOfRange::getMessage() const {
    return message;
}

int OutOfRange::getIndex() const {
    return index;
}

PFArrayD::PFArrayD() : capacity(50), used(0) {
    a = new double[capacity];
}

PFArrayD::PFArrayD(int capacityValue) : capacity(capacityValue), used(0) {
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaObject) : capacity(pfaObject.getCapacity()), used(pfaObject.getNumberUsed()) {
    a = new double[capacity];

    for (int i = 0; i < used; i++){
        a[i] = pfaObject.a[i];
    }
}

void PFArrayD::addElement(double element) {
    if (used >= capacity)
        throw OutOfRange("Outofrange exception, attempt insert beyond declared size", used);

    a[used] = element;
    used++;
}


double& PFArrayD::operator[](int index) throw (OutOfRange){
    if (index >= used || index < 0)
        throw OutOfRange("Outofrange exception, index value", index);

    return a[index];
}


PFArrayD& PFArrayD::operator=(const PFArrayD& rightSide) {
    
    
    if (this == &rightSide)
        return *this;

    if (capacity != rightSide.capacity){
        delete[] a;
        a = new double[rightSide.capacity];
    }

    capacity = rightSide.getCapacity();
    used = rightSide.getNumberUsed();

    for (int i = 0; i < used; i++)
        a[i] = rightSide.a[i];

    return *this;
}



PFArrayD::~PFArrayD() {
    delete[] a;
}