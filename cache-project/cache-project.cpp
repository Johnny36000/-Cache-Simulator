#include "cache.h"
#include "global.h"
#include<fstream>
#include<sstream>
using namespace std;
int bin_Decimal(string value)
{
    int result = 0;
    for (int i = value.size(); i >= 0; i--)
    {
        if (value[i] == '1') {

            result += pow(2, value.size() - i - 1);

        }
    }
    return result;
}
void readInputFile()
{
    int choice;
    cout << "which test case would you like to run:" << endl << "1" << endl << "2" << endl<<"3" << endl;
    cout << "your choice:" << endl;
    cin >> choice;
    string s = "input.txt";
   
    if (choice == 2) {
        s = "input1.txt";
    }
    if (choice == 3) {
        s = "input3.txt";
    }
    std::ifstream inputFile(s);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file " << 1 << std::endl;
        return;
    }

    std::string line;

    
    if (std::getline(inputFile, line))
    {
        
        std::stringstream ss(line);
        std::string token;

        
        while (std::getline(ss, token, ','))
        {
            v1.push_back(token);
        }
    }


    inputFile.close();
}
void simulate_cache() 
{
    readInputFile();

    cache::getinstance(stoi(v1[0]), stoi(v1[1]), stoi(v1[2]));
    
    for (int i = 3; i < v1.size(); i++) 
    {
        cout << "Searching for:" << v1[i] << endl;
        cache::Search(bitset<24>(stoi(v1[i])).to_string());
         cache::print();
    }
   
}


int main()
{
   simulate_cache();
  
 
}



