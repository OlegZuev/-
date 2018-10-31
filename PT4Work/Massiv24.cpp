#include "pt4.h"
#include <fstream>
#include <iomanip>
using namespace std;

void initArray(double* arr, int n);

void reverseArray(double* arr, int n);

void writeArray(double* arr, int n, ofstream& fout);

void Solve()
{
    Task("Massiv24");
    int n;
    pt >> n;
    double* arr = new double[n];
    initArray(arr, n);
    reverseArray(arr, n);
    ofstream fout("result.tst");
    writeArray(arr, n, fout);
    fout.close();
    delete[] arr;
}

void initArray(double* arr, int n)
{
    long long divider = 2;
    arr[0] = 1;
    for (int i = 1; i < n; ++i) {
        arr[i] = 1. / divider;
        divider *= divider;
    }
}

void reverseArray(double* arr, int n)
{
    int start = 0;
    int end = n - 1;
    double buf;
    while (start < end) {
        buf = arr[start];
        arr[start] = arr[end];
        arr[end] = buf;
        start++;
        end--;
    }
}

void writeArray(double* arr, int n, ofstream& fout)
{
    fout << fixed << setprecision(20);
    for (int i = 0; i < n; ++i) {
        fout << arr[i] << endl;
    }
}
