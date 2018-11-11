#include <iostream>
#include "LongInteger.h"
using namespace std;

int main() {
    LongInteger M, Q;
    int N;
    cout << "M?>";
    cin >> M;
    cout << "Q?>";
    cin >> Q;
    cout << "N?>";
    cin >> N;
    for (int i = 0; i < N; ++i) {
        M = M * Q;
    }
    cout << M;
    return 0;
}