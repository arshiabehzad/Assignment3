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
Delimeter::Delimeter(int lineNum, char symbol)
{
    this->lineNum = lineNum;
    this->symbol = symbol;
    hasPair = false;
    determinePair();
}
Delimeter::~Delimeter()
{

}

void Delimeter::determinePair()
{
    if (symbol == '{')
        closeSymbol = '}';
    else if (symbol == '(')
        closeSymbol = ')';
    else if (symbol == '[')
        closeSymbol = ']';
}
