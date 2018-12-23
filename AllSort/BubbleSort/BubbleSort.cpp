#include <algorithm>

void bubbleSort(int* arr, int n)
{
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }     
    }
}