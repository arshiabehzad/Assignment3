#include "FileAnalyzer.h"
#include <fstream>
#include <iostream>

GenStack<Delimeter *> *delimiterStack;
FileAnalyzer::FileAnalyzer()
{

}

FileAnalyzer::FileAnalyzer(string filename)
{
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
    while (getline(file, line))
    {
        lineCounter++;
        for(int i =0; i < line.length(); ++i)
        {
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
    file.close();
}
void FileAnalyzer::findPairs()
{
    GenStack<Delimeter *> *forwardStack = new GenStack<Delimeter *>();
    while(delimiterStack->isEmpty() == false)
    {
        forwardStack->push(delimiterStack->pop());
    }
    while (forwardStack->isEmpty() == false)
    {
        int counter = 0;
        Delimeter *curDelim = forwardStack->pop();
        if ((curDelim->symbol == ')' || curDelim->symbol == '}' || curDelim->symbol == ']') && curDelim->hasPair == false)
        {
            throw runtime_error("Unpaired symbol at line: " + to_string(curDelim->lineNum));
        }
        if (curDelim->symbol == '(' || curDelim->symbol == '{' || curDelim->symbol == '[')
        {
            bool found = false;
            for (int i = forwardStack->top; i >= 0; i--)
            {
                if (forwardStack->myArray[i]->symbol == '(' || forwardStack->myArray[i]->symbol == '{' || forwardStack->myArray[i]->symbol == '[')
                {
                    counter++;
                }
                else if (forwardStack->myArray[i]->symbol != curDelim->closeSymbol)
                {
                    counter--;
                }
                else if (forwardStack->myArray[i]->symbol == curDelim->closeSymbol)
                {
                    if (counter == 0)
                    {
                        forwardStack->myArray[i]->hasPair = true;
                        found = true;
                        break;
                    }
                    else
                    {
                        counter--;
                    }
                }
            }
            if (found == false)
            {
                throw runtime_error("Unpaired symbol at line: " + to_string(curDelim->lineNum));
            }
        }
        }
    
}