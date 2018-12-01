#include <iostream>

void Sort(int A[], int n)
{
    int j, x;
    for (int i = 1; i < n; i++) {
        j = i - 1;
        x = A[i];
        if (A[i] < A[j])
            do {
                A[j + 1] = A[j];
                j--;
            } while (j >= 0 && x < A[j]);
        if (i != j + 1)
            A[j + 1] = x;
    }
}

int main()
{
    int arr[10] = { 7, 5, 6, 8, 1, 6, 3, 4, 5, 9 };
    Sort(arr, 10);
    for (int i : arr) {
        std::cout << i << " ";
    }
    return 0;
}