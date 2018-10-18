#include <iostream>
using namespace std;

int main() {
    int k;
    cin >> k;
    for (int i = 1; i < 10; ++i) {
        cout << i * 100 + k * 10 + i << "\n";
    }
    return 0;
}