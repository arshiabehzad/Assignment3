#include <iostream>
#include "FileAnalyzer.h"

using namespace std;

int main(int argc, char **argv)
{
    string filename = argv[1];
    FileAnalyzer* f1 = new FileAnalyzer(filename);
    try{
        f1->findPairs();
        cout <<"no errors found" <<endl;
    }catch(runtime_error e)
    {
        cout<<e.what()<<endl;
    }
    
}