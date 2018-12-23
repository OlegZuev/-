#include <algorithm>

void quickSort(int* arr, int start, int end)
{
    int i = start;
    int j = end;
    int pivot = arr[i + (j - i) / 2];
    while (i < j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (start < j) {
        quickSort(arr, start, j);
    }
    if (i < end) {
        quickSort(arr, i, end);
    }
}