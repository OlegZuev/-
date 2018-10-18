#include <iostream>
using namespace std;

void main()
{
    int n;
    double sum = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int multiplier = i;
        for (int k = 1; k < i; ++k) {
            multiplier *= i;
        }
        sum += double(multiplier) / (i * (i + 1));
    }
    cout << sum;
}