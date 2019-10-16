#include <iostream>
#include "FileAnalyzer.h"

using namespace std;

int main(int argc, char **argv)
{
    string filename;
    //gets filename as paramter  
    filename = argv[1];
    FileAnalyzer* f1 = new FileAnalyzer(filename);
    while (true)
    {
        //try catch for findPairs()
        try{
            f1->findPairs();
            cout <<"no errors found" <<endl;
        }catch(runtime_error e)
        {
            cout<<e.what()<<endl;
        }
        //asks user if they want to quit or read another file
        cout << "Enter the file name to analyze another file (enter -1 to exit)" <<endl;
        cin >> filename;
        if (filename == "-1")
        {
            //quits the program
            break;
        }
        //sets the f1 pointer to a new fileanalyzer object with the new filename to analyze
        f1 = new FileAnalyzer(filename);
    }
}