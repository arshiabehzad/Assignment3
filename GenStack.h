#include <iostream>
using namespace std;

template <class T>
class GenStack
{
    public: 
    T * myArray;
    int size;
    int top;

    GenStack() //default constructor
    {
        //initializing default values
        myArray = new T[128];
        size = 128;
        top = -1;
    }

    GenStack(int maxSize)
    {
        myArray = new T[maxSize];
        size = maxSize;
        top = -1;
    }

    ~GenStack()
    {
        delete myArray;
    }

    void push(T d)
    {
        //error/boundary check
        myArray[++top] = d;
    }

    T pop()
    {
        if (isEmpty())
            throw runtime_error("The max size can't be less than 1");
        return myArray[top--];
    }

    void peek()
    {
        return myArray[top];
    }

    bool isFull()
    {
        return (top == size - 1);
    }

    bool isEmpty()
    {
        return (top == -1);
    }

    void resizeArray()
    {
        T * tempArray = new T[size*2];
        for(int i =0; i < size; i++)
        {
            tempArray[i] = myArray[i];
        }
        myArray = tempArray;
        this->size = this->size *2;
        
    }
};