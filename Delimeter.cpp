#include "Delimeter.h"
#include <fstream>

using namespace std;

int lineNum;
char symbol;
char closeSymbol;
bool hasPair;

Delimeter::Delimeter()
{

}

//constructor creates a Delimeter object 
Delimeter::Delimeter(int lineNum, char symbol)
{
    this->lineNum = lineNum;
    this->symbol = symbol;
    hasPair = false;
    //determines what the close symbol is 
    determinePair();
}
Delimeter::~Delimeter()
{

}

void Delimeter::determinePair()
{
    //based of symbol determines what the close symbol is
    if (symbol == '{')
        closeSymbol = '}';
    else if (symbol == '(')
        closeSymbol = ')';
    else if (symbol == '[')
        closeSymbol = ']';
}
