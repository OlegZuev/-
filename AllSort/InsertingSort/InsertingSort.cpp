void insertingSort(int* arr, int n)
{
    for (int i = 1; i < n; ++i) {
        int buff = arr[i];
        int j = i - 1;
        while (buff < arr[j] && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = buff;
    }
}