#include "pch.h"
#include "../BubbleSort/BubbleSort.cpp"
#include "../SelectingSort/SelectingSort.cpp"
#include "../InsertingSort/InsertingSort.cpp"
#include "../ShakerSort/ShakerSort.cpp"
#include "../QuickSort/QuickSort.cpp"
#include "../BinaryInsertingSort/BinaryInsertingSort.cpp"

void initArray(std::ifstream& fin, int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        fin >> arr[i];
    }
}

void writeArray(std::ofstream& fout, int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        fout << arr[i] << ' ';
    }
}

TEST(TestSort, BubbleSort1) {
    std::ifstream fin("input1.txt");
    int n;
    fin >> n;
    int* arr = new int[n];
    initArray(fin, arr, n);
    bubbleSort(arr, n);
    std::ofstream fout("output1.txt");
    writeArray(fout, arr, n);
    EXPECT_TRUE(true);
}

TEST(TestSort, SelectingSort1)
{
    std::ifstream fin("input2.txt");
    int n;
    fin >> n;
    int* arr = new int[n];
    initArray(fin, arr, n);
    selectingSort(arr, n);
    std::ofstream fout("output2.txt");
    writeArray(fout, arr, n);
    EXPECT_TRUE(true);
}

TEST(TestSort, InsertingSort1)
{
    std::ifstream fin("input3.txt");
    int n;
    fin >> n;
    int* arr = new int[n];
    initArray(fin, arr, n);
    insertingSort(arr, n);
    std::ofstream fout("output3.txt");
    writeArray(fout, arr, n);
    EXPECT_TRUE(true);
}

TEST(TestSort, ShakerSort1)
{
    std::ifstream fin("input4.txt");
    int n;
    fin >> n;
    int* arr = new int[n];
    initArray(fin, arr, n);
    shakerSort(arr, n);
    std::ofstream fout("output4.txt");
    writeArray(fout, arr, n);
    EXPECT_TRUE(true);
}

TEST(TestSort, QuickSort1)
{
    std::ifstream fin("input4.txt");
    int n;
    fin >> n;
    int* arr = new int[n];
    initArray(fin, arr, n);
    quickSort(arr, 0, n - 1);
    std::ofstream fout("output4.txt");
    writeArray(fout, arr, n);
    EXPECT_TRUE(true);
}

TEST(TestSort, BinaryInsertingSort1)
{
    std::ifstream fin("input4.txt");
    int n;
    fin >> n;
    int* arr = new int[n];
    initArray(fin, arr, n);
    binaryInsertingSort(arr, n);
    std::ofstream fout("output4.txt");
    writeArray(fout, arr, n);
    EXPECT_TRUE(true);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}