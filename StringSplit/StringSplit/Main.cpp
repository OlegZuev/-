#include <iostream>
#include "split.h"
using namespace std;

int main() {
    string str;
    getline(cin, str, '\n');
    vector<string> v = split(str, ' ');
    for (string s : v) {
        cout << s << endl;
    }
    return 0;
}