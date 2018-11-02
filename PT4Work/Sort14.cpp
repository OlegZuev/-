#include "pt4.h"
#include <fstream>
using namespace std;

void initArray(int* arr, int& n, ifstream& fin);

int binarySearchLeft(int* arr, int n, int x);

void Solve()
{
    Task("Sort14");
    int x, n = 200;
    string fileName;
    pt >> fileName >> x;
    ifstream fin(fileName);
    int* arr = new int[n];
    n = 0;
    initArray(arr, n, fin);
    pt << binarySearchLeft(arr, n, x);
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
    if (x < arr[0] || x > arr[n - 1]) {
        return -1;
    }
    int start = 0, end = n;
    while (start < end - 1) {
        int pivot = start + (end - start) / 2;
        if (x <= arr[pivot]) {
            end = pivot;
        } else {
            start = pivot;
        } 
    }
    return x == arr[start] ? start : (x == arr[start + 1] ? start + 1 : -1);
}