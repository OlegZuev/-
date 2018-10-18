#include <iostream>
using namespace std;

double arth(double x, double e);

int main() {
    double x, e;
    cin >> x >> e;
    cout << "1) arth(x) = " << arth(x, e) << " при e = " << e << endl;
    cout << "2) arth(x) = " << log(sqrt(1 - x * x) / (1 - x));
    return 0;
}

double arth (double x, double e) {
    double number = x, sum = 0, multiplier = x;
    for (int i = 1; abs(number) > e; ++i) {
        sum += number;
        multiplier *= x * x;
        number = multiplier / (2 * i + 1);
    }
    return sum;
}