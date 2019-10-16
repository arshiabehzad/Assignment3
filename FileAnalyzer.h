#include "GenStack.h"
#include "Delimeter.h"

using namespace std;

class FileAnalyzer
{
    
    public:
        FileAnalyzer();
        FileAnalyzer(string filename);
        ~FileAnalyzer();

        GenStack<Delimeter *> *delimiterStack;

        void readFile(string filename);
        void findPairs();
        

};