#include <iostream>
using namespace std;

int main() {
    int n;
    double x, sum = 0, divider = 1;
    cin >> n >> x;
    double multiplier = x;
    for (int i = 1; i <= n; ++i) {
        sum += multiplier / divider;
        multiplier *= -x * x;
        divider *= (2 * i) * (2 * i + 1);
    }
    cout << sum << "\n" << sin(x);
    return 0;
}