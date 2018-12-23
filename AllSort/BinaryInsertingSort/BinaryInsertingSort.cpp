void binaryInsertingSort(int* arr, int n)
{
    for (int i = 1; i < n; ++i) {
        int buff = arr[i];
        int start = 0;
        int end = i;
        while (end - start > 1) {
            int middle = start + (end - start) / 2;
            if (buff < arr[middle]) {
                end = middle;
            } else {
                start = middle;
            }
        }
        if (buff >= arr[start]) {
            start++;
        }
        int j = i - 1;
        while (j >= start) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = buff;
    }
}