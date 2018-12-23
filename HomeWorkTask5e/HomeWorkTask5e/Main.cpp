#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void initMatrix(ifstream& fin, int** matrix, int n, int m);

void changeMatrix(int** matrix, int n, int& m);

void shiftLine(int** matrix, int n, int m, int j);

void writeMatrix(ofstream& fout, int** matrix, int n, int m);

void deleteMatrix(int** matrix, int n);

int main() {
    //cout << '\a';
    // string input, output;
    // cout << "ֲגוהטעו טלÿ פאיכא: ";
    // cin >> input;
    // ifstream fin(input);
    // int n, m;
    // fin >> n >> m;
    // int** matrix = new int*[n];
    // initMatrix(fin, matrix, n, m);
    // changeMatrix(matrix, n, m);
    // fin.close();
    // ofstream fout(input, ios::app);
    // writeMatrix(fout, matrix, n, m);
    return 0;
}

void initMatrix(ifstream& fin, int** matrix, int n, int m)
{
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m + 1];
        for (int j = 0; j < m; ++j) {
            fin >> matrix[i][j];
        }
    }
}

void changeMatrix(int** matrix, int n, int& m)
{
    bool flag = true;
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            if (matrix[i][j] < 0) {
                flag = false;
            }
        }
        if (flag) {
            shiftLine(matrix, n, m, j);
            m++;
            return;
        }
        flag = true;
    }
}

void shiftLine(int** matrix, int n, int m, int j)
{
    for (int k = m; k > j + 1; --k) {
        for (int i = 0; i < n; ++i) {
            matrix[i][k] = matrix[i][k - 1];
        }
    }
    for (int i = 0; i < n; ++i) {
        matrix[i][j + 1] = 0;
    }
}

void writeMatrix(ofstream& fout, int** matrix, int n, int m)
{
    fout << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fout << setw(3) << matrix[i][j];
        }
        fout << endl;
    }
}

void deleteMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}