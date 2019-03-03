#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

const int maxCountPrimeNumbers = 1000000;
const int CODE_PAGE = 1251;

void searchPrimeNumbers(int n, int* arr, int& length);

int main() {
    SetConsoleCP(CODE_PAGE);
    SetConsoleOutputCP(CODE_PAGE);
    cout << "¬ведите n: ";
    int n;
    cin >> n;
    int* primeNumbers = new int[maxCountPrimeNumbers];
    primeNumbers[0] = 2;
    int length = 1;
    searchPrimeNumbers(n, primeNumbers, length);
    ofstream fout("result.dat", ios::binary);
    fout.write((char*)&length, sizeof(int));
    for (int i = 0; i < length; ++i) {
        fout.write((char*)&primeNumbers[i], sizeof(int));
    }
    delete[] primeNumbers;
    fout.close();
    return 0;
}

void searchPrimeNumbers(int n, int* arr, int& length)
{
    for (int i = 3; i < n; ++i) {
        bool flag = true;
        for (int j = 0; j < length; ++j) {
            if (i % arr[j] == 0) {
                flag = false;
                break;
            }
            if (i < arr[j] * arr[j]) {
                break;
            }
        }
        if (flag) {
            arr[length++] = i;
        }
    }
}