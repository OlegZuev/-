#include <iostream>
#include "LongInteger.h"

static void initArray(int* arr, const int n)
{
    for (int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
}

static void showArray(int* arr, const int n)
{
    for (int i = 0; i < n; ++i) {
        std::cout << i << " встречается " << arr[i] << " раз" << std::endl;
    }
}

static void counting(int* result, const LongInteger& sum)
{
    for (int i = 0; i < sum.getLength(); ++i) {
        result[sum.getArr()[i]]++;
    }
}

static LongInteger sumOfGeometricProgression(LongInteger M, const LongInteger& Q, const int N)
{
    LongInteger sum = 0;
    for (int i = 0; i < N; ++i) {
        sum = sum + M;
        M = M * Q;
    }
    return sum;
}