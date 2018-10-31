#include <iostream>
#include "Fraction.h"
using namespace std;

int main() {
    long long num, dem;
    cin >> num >> dem;
    Fraction fr(num, dem);
    for (int i = 0; i < 4; ++i)
    {
        cin >> num >> dem;
        fr.add(Fraction(num, dem));
        //cout << fr << endl;
    }
    cout << fr.divide(Fraction(5, 1));
    return 0;
}