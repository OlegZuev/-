#include "pt4.h"
using namespace std;

void initArray(int* arr, int n);

void threeConsequentNumbersOfGreatSum(int* arr, int n, int& i1, int& i2, int& i3);

void Solve()
{
    Task("Massiv9");
    int n;
    pt >> n;
    int* arr = new int[n];
    initArray(arr, n);
    int i1 = arr[0], i2 = arr[1], i3 = arr[2];
    threeConsequentNumbersOfGreatSum(arr, n, i1, i2, i3);
    pt << i1 << i2 << i3;
}

void initArray(int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        pt >> arr[i];
    }
}

void threeConsequentNumbersOfGreatSum(int* arr, int n, int& i1, int& i2, int& i3)
{
    for (int i = 1; i < n - 2; ++i) {
        if (arr[i] + arr[i + 1] + arr[i + 2] > i1 + i2 + i3) {
            i1 = arr[i];
            i2 = arr[i + 1];
            i3 = arr[i + 2];
        }
    }
}