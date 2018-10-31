#include "pt4.h"
using namespace std;

void initArray(int* arr, int n);

int multiplication(int* arr, int n);

int averageValue(int* arr, int n);

int countAboveAverage(int* arr, int n);

void Solve()
{
    Task("Massiv2");
    int n;
    pt >> n;
    int* arr = new int[n];
    initArray(arr, n);
    pt << multiplication(arr, n) << countAboveAverage(arr, n);
    delete[] arr;
}

void initArray(int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        pt >> arr[i];
    }
}

int multiplication(int* arr, int n)
{
    int exp = 1;
    for (int i = 0; i < n; ++i) {
        if (arr[i] != 0) {
            exp *= arr[i];
        }
    }
    return exp;
}

int averageValue(int* arr, int n)
{
    int avg = 0;
    for (int i = 0; i < n; ++i) {
        avg += arr[i];
    }
    return avg / n;
}

int countAboveAverage(int* arr, int n)
{
    int avg = averageValue(arr, n);
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > avg) {
            count++;
        }
    }
    return count;
}