#include "LongInteger.h"

/**
 * Процедура инициализирует массив нулями.
 * @param arr - входной массив, n - размер массива
 */
static void initArray(int* arr, const int n)
{
    for (int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
}

/**
 * Процедура показывает содержимое массива в отформатированном формате.
 * @param arr - входной массив, n - размер массива
 */
static void showArray(int* arr, const int n)
{
    for (int i = 0; i < n; ++i) {
        std::cout << i << " встречается " << arr[i] << " раз" << std::endl;
    }
}

/**
 * Процедура процедура подсчитывает количество нулей, единиц и тд. до девяток числа.
 * @param result - входной массив, являющийся результирующим; sum - подсчитываемое число 
 */
static void counting(int* result, const LongInteger& sum)
{
    for (int i = 0; i < sum.getLength(); ++i) {
        result[sum.getArr()[i]]++;
    }
}

/**
 * Функция, вычисляющая сумму геометрической прогрессии.
 * @param M - первый элемент, Q - множитель, N - номер суммы геометрической прогрессии
 * @return sum - сумма геометрической прогрессии
 */
static LongInteger sumOfGeometricProgression(LongInteger M, const LongInteger& Q, const int N)
{
    LongInteger sum = 0;
    for (int i = 0; i < N; ++i) {
        sum = sum + M;
        M = M * Q;
    }
    return sum;
}

/**
 * Процедура проверяет входные данные.
 * @param n - введённое число 
 */
static void checkValue(std::string& n)
{
    for (char i : n) {
        if (i - '0' < 0 || i - '0' > 9) {
            std::cout << "Ошибка ввода. Пожалуйста, введите значение заново: ";
            std::cin >> n;
            checkValue(n);
            break;
        }
    }
}