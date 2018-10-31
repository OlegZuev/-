#include "pt4.h"
#include <fstream>
using namespace std;

void initArray(int* arr, int& n, ifstream& fin);

bool isPrimeNumber(int i);

void showArray(int* arr, int n, ofstream& fout);

void shiftRightArray(int* arr, int& n, int m);

void Solve()
{
    Task("Massiv33");
    int k, m;
    pt >> k >> m;
    int n = 1000;
    int* arr = new int[n];
    n = 0;
    ifstream fin("input.dat");
    initArray(arr, n, fin);
    ofstream fout("rez.dat");
    showArray(arr, n, fout);
    for (int i = 0; i < k; ++i) {
        shiftRightArray(arr, n, m);
        showArray(arr, n, fout);
    }
    fin.close();
    fout.close();
    delete[] arr;
}

void initArray(int* arr, int& n, ifstream& fin)
{
    int buf;
    while (!fin.eof()) {
        fin >> buf;
        if (!isPrimeNumber(buf)) {
            arr[n] = buf;
            n++;
        }
    }
}

bool isPrimeNumber(int i)
{
    if (i % 2 == 0 || i == 1) {
        return false;
    }
    for (int j = 3; j * j < i; j += 2) {
        if (i % j == 0) {
            return false;
        }
    }
    return true;
}

void showArray(int* arr, int n, ofstream& fout)
{
    for (int i = 0; i < n; ++i) {
        fout << arr[i] << " ";
    }
    fout << endl;
}

void shiftRightArray(int* arr, int &n, int m)
{
    for (int i = n - 1; i >= 0; --i) {
        if (i - m >= 0) {
            arr[i] = arr[i - m];
        } else {
            arr[i] = 0;
        }
    }
}