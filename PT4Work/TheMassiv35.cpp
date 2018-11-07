#include "pt4.h"
#include <fstream>
using namespace std;

void initArray(int* arr, int n, ifstream& fin);

void deleteSectionOfValues(int* arr, int& n, int k1, int k2);

void deleteElemFromArray(int* arr, int& n, int i);

void showArray(int* arr, int n, ofstream& fout);

void Solve()
{
    Task("TheMassiv35");
    string input, output;
    pt >> input >> output;
    ifstream fin(input);
    ofstream fout(output);
    int n, k1, k2;
    fin >> n >> k1 >> k2;
    int* arr = new int[n];
    initArray(arr, n, fin);
    showArray(arr, n, fout);
    deleteSectionOfValues(arr, n, k1, k2);
    fout << endl << endl;
    showArray(arr, n, fout);
}

void initArray(int* arr, int n, ifstream& fin)
{
    for (int i = 0; i < n; ++i) {
        fin >> arr[i];
    }
}

void deleteSectionOfValues(int* arr, int& n, int k1, int k2)
{
    for (int i = 0; i < n;) {
        if (arr[i] >= k1 && arr[i] <= k2) {
            deleteElemFromArray(arr, n, i);
        } else {
            i++;
        }
    }
}

void deleteElemFromArray(int* arr, int& n, int i)
{
    for (; i < n; ++i) {
        arr[i] = arr[i + 1];
    }
    n--;
}

void showArray(int* arr, int n, ofstream& fout)
{
    for (int i = 0; i < n; ++i) {
        fout << arr[i] << " ";
    }
}