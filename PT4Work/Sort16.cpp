#include "pt4.h"
#include <fstream>
using namespace std;

void initArray(int* arr, int& n, ifstream& fin);

int binarySearchLeft(int* arr, int n, int x);

int binarySearchRight(int* arr, int n, int x);

void Solve()
{
    Task("Sort16");
    int x, n = 200;
    string fileName;
    pt >> fileName >> x;
    ifstream fin(fileName);
    int* arr = new int[n];
    n = 0;
    initArray(arr, n, fin);
    int result = binarySearchRight(arr, n, x) - binarySearchLeft(arr, n, x);
    pt << (result != 0 ? result + 1 : 0);
}

void initArray(int* arr, int& n, ifstream& fin)
{
    while (!fin.eof()) {
        fin >> arr[n];
        n++;
    }
}

int binarySearchLeft(int* arr, int n, int x)
{
    int start = -1, end = n - 1;
    while (end - start > 1) {
        int pivot = start + (end - start) / 2;
        if (x < arr[pivot]) {
            start = pivot;
        } else {
            end = pivot;
        }
    }
    return x == arr[end] ? end : -1;
}

int binarySearchRight(int* arr, int n, int x)
{
    int start = 0, end = n;
    while (end - start > 1) {
        int pivot = start + (end - start) / 2;
        if (x > arr[pivot]) {
            end = pivot;
        } else {
            start = pivot;
        }
    }
    return x == arr[start] ? start : -1;
}