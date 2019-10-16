#include "FileAnalyzer.h"
#include <fstream>
#include <iostream>

GenStack<Delimeter *> *delimiterStack;
FileAnalyzer::FileAnalyzer()
{

}

FileAnalyzer::FileAnalyzer(string filename)
{
    //creates a new stack of Delimeter objects and calls the readfile function
    delimiterStack = new GenStack<Delimeter*>();
    readFile(filename);
    
}

FileAnalyzer::~FileAnalyzer()
{

}


void FileAnalyzer::readFile(string filename)
{
    string line;
    ifstream file;
    file.open(filename);
    int lineCounter =0;
    //goes through the file line by line 
    while (getline(file, line))
    {
        //increments line counter by 1
        lineCounter++;
        for(int i =0; i < line.length(); ++i)
        {
            /* series of if statements that checks for a certain delimeter, if found it adds a delimeter object
            to the stack with the line it was and the proper symbol */
            if (line[i] == '(')
            {
                Delimeter *d = new Delimeter(lineCounter, '(');
                delimiterStack->push(d);
            }
            else if (line[i] == '{')
            {
                Delimeter *d = new Delimeter(lineCounter, '{');
                delimiterStack->push(d);
            }
            else if (line[i] == '[')
            {
                Delimeter *d = new Delimeter(lineCounter, '[');
                delimiterStack->push(d);
            }
            else if (line[i] == ')')
            {
                Delimeter *d = new Delimeter(lineCounter, ')');
                delimiterStack->push(d);
            }
            else if (line[i] == '}')
            {
                Delimeter *d = new Delimeter(lineCounter, '}');
                delimiterStack->push(d);
            }
            else if (line[i] == ']')
            {
                Delimeter *d = new Delimeter(lineCounter, ']');
                delimiterStack->push(d);
            }
        }
    }
    //closes file
    file.close();
}
void FileAnalyzer::findPairs()
{
    /*goes through the delimeter stack and adds it to a new stack so that the first delimeter in the file
      is at the top of the stack (makes it easier to conceptualize)*/
    GenStack<Delimeter *> *forwardStack = new GenStack<Delimeter *>();
    while(delimiterStack->isEmpty() == false)
    {
        forwardStack->push(delimiterStack->pop());
    }
    //continues to loop untill the stack is empty
    while (forwardStack->isEmpty() == false)
    {
        /*this counter is used to find the proper closing pair for the current delimeter*/
        int counter = 0;
        //pops the top of the stack off and sets it the curDelim pointer
        Delimeter *curDelim = forwardStack->pop();
        //if it is a closing symbol, and it has not already been paired, this means it must be an extra one 
        if ((curDelim->symbol == ')' || curDelim->symbol == '}' || curDelim->symbol == ']') && curDelim->hasPair == false)
        {
            //throws exception
            throw runtime_error("Unpaired symbol at line: " + to_string(curDelim->lineNum));
        }
        //checks to see if the curDelim is an opening delimeter
        if (curDelim->symbol == '(' || curDelim->symbol == '{' || curDelim->symbol == '[')
        {
            //used to check if loop finds a pair for current delimeter
            bool found = false;
            //iterates through the stack like an array to check it against the curr delim
            for (int i = forwardStack->top; i >= 0; i--)
            {
                /*if we come across another opening delimeter while iterating through the array we know we must 
                skip a closing delimeter so we add one to the counter*/
                if (forwardStack->myArray[i]->symbol == '(' || forwardStack->myArray[i]->symbol == '{' || forwardStack->myArray[i]->symbol == '[')
                {
                    counter++;
                }
                /*if we come across a closing delimeter thats not the closing symbol for the array while iterating 
                through the array we have closed one set of delims so we can minus one from the counter*/
                else if (forwardStack->myArray[i]->symbol != curDelim->closeSymbol)
                {
                    counter--;
                }
                //checks to see if we come across a correct closing delimeter 
                else if (forwardStack->myArray[i]->symbol == curDelim->closeSymbol)
                {
                    /*if the counter is = 0 then we know that the correct pair has been found so we can
                    stop iterating through the array and change the forwardStacks hasPair value to true*/
                    if (counter == 0)
                    {
                        forwardStack->myArray[i]->hasPair = true;
                        //sets found to true since we have found a pair
                        found = true;
                        break;
                    }
                    /* if not then we still must continue but we have closed another set of delims so we
                    minus the counter*/
                    else 
                    {
                        counter--;
                    }
                }
            }
            /*if we go through the whole loop and dont find a pair that means we must have an unpaired symbol
            so we throw an exception*/
            if (found == false)
            {
                throw runtime_error("Unpaired symbol at line: " + to_string(curDelim->lineNum));
            }
        }
        }
    
}