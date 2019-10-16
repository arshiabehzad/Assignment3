#include <iostream>
#include "FileAnalyzer.h"

using namespace std;

int main(int argc, char **argv)
{
    string filename;
    filename = argv[1];
    FileAnalyzer* f1 = new FileAnalyzer(filename);
    while (true)
    {
        try{
            f1->findPairs();
            cout <<"no errors found" <<endl;
        }catch(runtime_error e)
        {
            cout<<e.what()<<endl;
        }
        cout << "Enter the file name to analyze another file (enter -1 to exit)" <<endl;
        cin >> filename;
        if (filename == "-1")
        {
            break;
        }
        f1 = new FileAnalyzer(filename);
    }
}