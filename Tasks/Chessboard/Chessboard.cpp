#include <iostream>

using namespace std;

int main() {
    long long n;
    int q;
    cin >> n >> q;
    long long x, y, *result = new long long[q];
    for (int i = 0; i < q; ++i) {
        cin >> y >> x;
        if ((x + y) % 2 == 0) {
            result[i] = ((y - 1) * n + x + 1) / 2;
        } else {
            result[i] = (n * n + 1) / 2 + ((y - 1) * n + x + 1) / 2;
        }
    }
    for (int j = 0; j < q; ++j) {
        cout << result[j] << endl;
    }
    delete[] result;
    return 0;
}