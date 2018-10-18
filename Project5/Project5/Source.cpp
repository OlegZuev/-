#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    long* val = new long[b + 1];
    val[a] = 1;
    for (int i = a; i <= b; ++i) {
        if (a == i) {
            continue;
        }
        if (i % 2 == 0 && i / 2 >= a) {
            val[i] = 0;
            val[i] += val[i / 2] + val[i - 1];
        } else {
            val[i] = val[i - 1];
        }
    }
    cout << val[b];
    return 0;
}