#ifndef PAIR_H
#define PAIR_H

template <class T,class K>
class Pair{
public:
    Pair(T new1, K new2);

    T getFirst();
    void setFirst(T new1);

    K getSecond();
    void setSecond(K new2);
private:
    T first;
    K second;
};
#endif