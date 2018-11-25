#include <iostream>
#include "LongInteger.h"
using namespace std;

void initArray(int* arr, int n);

void showArray(int* arr, int n);

void counting(int* result, LongInteger sum);

LongInteger sumOfGeometricProgression(LongInteger M, LongInteger Q, int N);

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

void initArray(int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
}

void showArray(int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        cout << i << " встречается " << arr[i] << " раз" << endl;
    }
}

void counting(int* result, LongInteger sum)
{
    for (int i = 0; i < sum.getLength(); ++i) {
        result[sum.getArr()[i]]++;
    }
}

LongInteger sumOfGeometricProgression(LongInteger M, LongInteger Q, int N)
{
    LongInteger sum(0);
    for (int i = 0; i < N; ++i) {
        sum = sum + M;
        M = M * Q;
    }
    return sum;
}