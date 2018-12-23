#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void initMatrix(int** arr, int& n, int& m);

void showMatrix(int** arr, int n, int m);

void deleteMatrix(int** arr, int n);

int main()
{
    int** arr = new int*[100];
    int n = 0;
    int m = 0;
    initMatrix(arr, n, m);
    showMatrix(arr, n, m);
    return 0;
}

void initMatrix(int** arr, int& n, int& m)
{
    ifstream fin("input.txt");
    string buff;
    getline(fin, buff);
    for (int i = buff.find(' '); i != -1; i = buff.find(' ', i + 1)) {
        m++;
    }
    m++;
    stringstream ss(buff);
    arr[n] = new int[m];
    for (int i = 0; i < m; ++i) {
        ss >> arr[n][i];
    }
    n++;
    for (; !fin.eof(); ++n) {
        arr[n] = new int[m];
        for (int i = 0; i < m; ++i) {
            fin >> arr[n][i]; 
        }
    }
    fin.close();
}

void showMatrix(int** arr, int n, int m)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void deleteMatrix(int** arr, int n)
{
    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}