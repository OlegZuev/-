#include "pt4.h"
#include <fstream>
using namespace std;

void initArray(int* arr, int& n, ifstream& fin);

int find(int* arr, int n, int x);

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
    pt << find(arr, n, x);
}

void initArray(int* arr, int& n, ifstream& fin)
{
    while (!fin.eof()) {
        fin >> arr[n];
        n++;
    }
}

int find(int* arr, int n, int x)
{
    int index = -1;
    int start = 0, end = n;
    while (start < end) {
        if (end - start == 1) {
            end = start;
        }
        int pivot = start + (end - start) / 2;
        if (x == arr[pivot]) {
            index = pivot;
        }
        if (x <= arr[pivot]) {
            end = pivot;
        } else {
            start = pivot;
        } 
    }
    return index;
}