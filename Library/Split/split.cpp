#include "split.h"
using namespace std;

vector<string> split(string text, char delimeter) {
    vector<string> strings;
    string buffer;
    for (char i : text)
    {
        if (i != delimeter) {
            buffer += i;
        } else {
            strings.push_back(buffer);
            buffer = "";
        }
    }
    strings.push_back(buffer);
    return strings;
}