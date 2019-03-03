#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

void bruteForce(string s, int n, int indexOfSign, bool& flag);

int calculate(string s);

int takeOperand(string s);

bool isNumber(char c);

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string bill;
    int n;
    cout << "¬ведите номер автобусного билета и N: ";
    cin >> bill >> n;
    bool flag = false;
    bruteForce(bill, n, 1, flag);
    if (!flag) {
        cout << "–ешений не существует";
    }
}

void bruteForce(string s, int n, int indexOfSign, bool& flag) {
    if (indexOfSign > s.length()) {
        return;
    }

    int x = calculate(s);
    if (x == n) {
        flag = true;
        cout << s << "=" << n << endl;
        return;
    }

    bruteForce(s, n, indexOfSign + 1, flag);
    bruteForce(s.substr(0, indexOfSign) + '+' + s.substr(indexOfSign), n, indexOfSign + 2, flag);
    bruteForce(s.substr(0, indexOfSign) + '-' + s.substr(indexOfSign), n, indexOfSign + 2, flag);
}

int calculate(string s) {
    int x = takeOperand(s);
    if (s.length() == 1) {
        return x;
    }
    int indexOfSign = s.length() - 1;
    for (; indexOfSign >= 0; indexOfSign--) {
        if (s[indexOfSign] == '+' || s[indexOfSign] == '-') {
            break;
        }
    }
    if (indexOfSign < 0) {
        return x;
    }
    int left = calculate(s.substr(0, indexOfSign));
    char sign = s[indexOfSign];
    if (sign == '+') {
        return left + x;
    }
    return left - x;
}

int takeOperand(string s) {
    int indexStartOfNumber = s.length() - 1;
    for (; indexStartOfNumber > 0; indexStartOfNumber--) {
        if (!isNumber(s[indexStartOfNumber])) {
            indexStartOfNumber++;
            break;
        }
    }
    return stoi(s.substr(indexStartOfNumber));
}

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}