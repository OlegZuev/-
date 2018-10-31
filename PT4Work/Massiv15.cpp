#include "pt4.h"
using namespace std;

void initArray(int* arr, int n);

void showArray(int* arr, int n);

void swapElementsInArray(int* arr, int n, int k, int l);

void Solve()
{
    Task("Massiv15");
    int n, k, l;
    pt >> n >> k >> l;
    int* arr = new int[n];
    for (int i = 0; i < 4; ++i) {
        initArray(arr, n);
        swapElementsInArray(arr, n, k, l);
        showArray(arr, n);
    }
    delete[] arr;
}

void initArray(int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        pt >> arr[i];
    }
}

void showArray(int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        pt << arr[i];
    }
}

void swapElementsInArray(int* arr, int n, int k, int l)
{
    int buf;
    k++;
    l--;
    while (k < l) {
        buf = arr[k];
        arr[k] = arr[l];
        arr[l] = buf;
        k++;
        l--;
    }
}