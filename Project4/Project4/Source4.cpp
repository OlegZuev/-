#include <iostream>
#include "../../StringSplit/StringSplit/Split.h" 
#include "../../StringSplit/StringSplit/Split.cpp" 
using namespace std;

int main()
{
    cout << "text" << endl;;
    string text;
    cin >> text;
    vector<string> lines = split(text, '-');
    for (const string& s : lines) {
        cout << s << endl;
    }
}