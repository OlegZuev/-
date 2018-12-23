#include <algorithm>

void selectingSort(int* arr, int n)
{
    for (int i = n - 1; i >= 0; --i) {
        int iMax = 0;
        for (int j = 0; j <= i; ++j) {
            if (arr[iMax] < arr[j]) {
                iMax = j;
            }
        }
        std::swap(arr[iMax], arr[i]);
    }
}