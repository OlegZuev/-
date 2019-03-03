#include <fstream>
#include <iostream>
#include <string>
#include "windows.h"
using namespace std;

const int CODE_PAGE = 1251;

void showPrimeNumbers(ifstream& fin, int n);

void showPrimeNumbersWithMultiplication(ifstream& fin, int n, int k);

int multiplicationNumbers(int n);

bool isNumber(string n);

void showNumber(ifstream& fin, int n);

int main()
{
    SetConsoleCP(CODE_PAGE);
    SetConsoleOutputCP(CODE_PAGE);
    ifstream fin("result.dat", ios::binary);

    int n;
    fin.read((char*)&n, sizeof(int));
    showPrimeNumbers(fin, n);

    cout << "¬ведите k: ";
    int k;
    cin >> k;
    fin.seekg(0, ios::beg);
    showPrimeNumbersWithMultiplication(fin, n, k);

    cout << "¬ведите m: ";
    string _m;
    cin >> _m;
    while (!isNumber(_m) || stoi(_m) > n || stoi(_m) < 1) {
        cout << "„исло некорректное или выходит за пределы. ¬ведите m заново: ";
        cin >> _m;
    }
    int m = stoi(_m);

    showNumber(fin, m);
    showNumber(fin, 3);
    showNumber(fin, n - 1);
    fin.close();
    return 0;
}

void showPrimeNumbers(ifstream& fin, int n)
{
    int a;
    for (int i = 0; i < n; ++i) {
        fin.read((char*)&a, sizeof(a));
        cout << a << " ";
    }
    cout << endl;
}

void showPrimeNumbersWithMultiplication(ifstream& fin, int n, int k)
{
    int a;
    for (int i = 0; i < n; ++i) {
        fin.read((char*)&a, sizeof(a));
        if (multiplicationNumbers(a) == k) {
            cout << a << " ";
        }
    }
    cout << endl;
}

int multiplicationNumbers(int n)
{
    if (n < 10) {
        return n;
    }
    return multiplicationNumbers(n / 10) * (n % 10);
}

bool isNumber(string n) {
    int i = 0;
    if (n[0] == '-') {
        i++;
    }
    for (; i < n.length(); ++i) {
        if (n[i] > '9' || n[i] < '0') {
            return false;
        }
    }
    return !(n.length() == 1 && n[0] == '-');
}

void showNumber(ifstream& fin, int n) {
    int temp;
    fin.seekg(sizeof(int) * n, ios::beg);
    fin.read((char*)&temp, sizeof(temp));
    cout << temp << " ";
}