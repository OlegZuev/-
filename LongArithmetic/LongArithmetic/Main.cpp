#include "Utilities.cpp"
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
    int result[10];
    initArray(result, 10);
    const LongInteger sum = sumOfGeometricProgression(M, Q, N);
    counting(result, sum);
    showArray(result, 10);
    return 0;
}