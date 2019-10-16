using namespace std;

class Delimeter
{
    public: 
        int lineNum;
        char symbol;
        char closeSymbol;
        bool hasPair;

        Delimeter();
        Delimeter(int lineNum, char symbol);
        ~Delimeter();

    private: 
        void determinePair();
};