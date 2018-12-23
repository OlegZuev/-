#include <algorithm>

void shakerSort(int* arr, int n)
{
    int start = 0;
    int end = n - 1;
    int indexLastSwap = -1;
    while (start < end) {
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                indexLastSwap = i;
            }
        }
        end = indexLastSwap;
        for (int i = end; i > start; --i) {
            if (arr[i] < arr[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
                indexLastSwap = i;
            }
        }
        start = indexLastSwap;
    }
}