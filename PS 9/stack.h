//stack .h //
//A template−based class for a stack based on StackSavitch // from chapter 17.2 of Absolute C++.
#ifndef STACK_H 
#define STACK_H
//∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// Exception class for popping // an empty stack
//∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
class PopEmptyStackException {
};
template<class T> class Node
{
public :
    Node(T theData, Node<T>* theLink) : data(theData), link(theLink) {}
    Node<T>* getLink() const { return link; } const T getData () const { return data ; }
    void setData ( const T& theData ) { data = theData ; } void setLink(Node<T>* pointer) { link = pointer; }
private :
    T data;
    Node<T> *link;
};



template<class T>
class Stack {
public : 
    Stack ();
    Stack ( const Stack<T>& aStack ) ;
    Stack<T>& operator =(const Stack<T>& rightSide) ;
    virtual  ~Stack ();
    void push (T stackFrame ) ;
    T pop ( ) throw ( PopEmptyStackException ) ; 
    bool isEmpty ( ) const ;
private :
    Node<T> *top;
};

#endif