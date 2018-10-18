#include <iostream>
#include "Main.h"
using namespace std;

int main()
{
    char sign;
    int number1, number2;
    double result;
    cout << "Калькулятор. Ver 0.1\n"
        "Введите знак арифметиеского действия: ";
    cin >> sign;
    cout << "Введите первое число: ";
    cin >> number1;
    cout << "Введите второе число: ";
    cin >> number2;
    result = calculate(number1, number2, sign);
    cout << result;
    return 0;
}

double calculate(int number1, int number2, char sign)
{
    double result = 0;
    switch (sign) {
    case '+':
        result = number1 + number2;
        break;
    case '-':
        result = number1 - number2;
        break;
    case '*':
        result = number1 * number2;
        break;
    case '/':
        result = double(number1) / number2;
        break;
    case '%':
        result = number1 % number2;
    }
    return result;
}