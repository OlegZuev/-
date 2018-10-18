#include <iostream>
#include <string>

using namespace std;

int main() {
    int count;
    cin >> count;
    bool isPalindrom;
    int strLength;
    string str;
    string result[50];
    for (int i = 0; i < count; ++i) {
        isPalindrom = true;
        cin >> strLength >> str;
        for (int j = 0; j < strLength / 2; ++j) {
            if (abs(str[j] - str[strLength - j - 1]) != 2 &&
                abs(str[j] - str[strLength - j - 1]) != 0) {
                result[i] = "NO";
                isPalindrom = false;
                break;
            }
        }
        if (isPalindrom) {
            result[i] = "YES";
        }
    }
    for (int k = 0; k < count; ++k) {
        cout << result[k] << endl;
    }
    return 0;
}