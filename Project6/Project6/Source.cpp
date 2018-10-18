#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    ifstream fin("Text.txt");
    int i = 0, sum = 0;
    char buf;
    for (; (buf = fin.get()) != -1; ++i) {
        char* b = new char[255];
        b[0] = buf;
        for (int j = 1; (buf = fin.get()) != 32 && buf != -1; ++j) {
            b[j] = buf;
        }
        sum += atoi(b);
        cout << double(sum) << endl;
    }
    cout << double(sum) / i;
    fin.close();
    return 0;
}

int get(ifstream fin) {
    int buf = fin.get();
    isdigit(buf);
}