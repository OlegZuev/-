#include "Utilities.cpp"
#include "windows.h"
#include <cstdlib>
using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    LongInteger M, Q;
    int N;
    cout << "M?>";
    cin >> M;
    cout << "Q?>";
    cin >> Q;
    cout << "N?>";
    string temp;
    cin >> temp;
    checkValue(temp);
    N = stoi(temp);
    int result[10];
    initArray(result, 10);
    const LongInteger sum = sumOfGeometricProgression(M, Q, N);
    counting(result, sum);
    showArray(result, 10);
    cout << sum << endl;
    cout << (sum == LongInteger("-5473582175058386357330851085890915718275")) << endl;
    return 0;
}