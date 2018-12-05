#include "pch.h"
#include "../LongArithmetic/LongInteger.cpp"
#include "../LongArithmetic/Utilities.cpp"
#include <fstream>

int* actualArray(LongInteger M, LongInteger Q, int N)
{
    int* result = new int[10];
    initArray(result, 10);
    const LongInteger sum = sumOfGeometricProgression(M, Q, N);
    counting(result, sum);
    return result;
}

int* expectedArray(std::ifstream& fin)
{
    int* result = new int[10];
    for (int i = 0; i < 10; ++i) {
        fin >> result[i];
    }
    return result;
}

bool compareArrays(const int* arr1, const int* arr2, const int n)
{
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (arr1[i] != arr2[i]) {
            flag = false;
            break;
        }
    }
    return flag;
}

void writeArray(std::ofstream& fout, const int* arr, const int n)
{
    for (int i = 0; i < n - 1; ++i) {
        fout << arr[i] << " ";
    }
    fout << arr[9];
}

bool runTest(const int n)
{
    std::ifstream fin("input" + std::to_string(n) + ".txt");
    if (!fin.is_open()) {
        std::cout << "Ошибка открытия файла." << std::endl;
        return false;
    }
    std::ofstream fout("output" + std::to_string(n) + ".txt");
    LongInteger M;
    LongInteger Q;
    int N;
    fin >> M >> Q >> N;
    fin.close();
    fin.open("answer" + std::to_string(n) + ".txt");
    int* actualArray = ::actualArray(M, Q, N);
    int* expectedArray = ::expectedArray(fin);
    const bool flag = compareArrays(actualArray, expectedArray, 10);
    writeArray(fout, actualArray, 10);
    fin.close();
    fout.close();
    return flag;
}

TEST(LongIntegerTest, TestZero1) {
    bool flag = runTest(1);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestZero2)
{
    bool flag = runTest(2);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestZero3)
{
    bool flag = runTest(3);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestMinValues)
{
    bool flag = runTest(4);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestMaxValues)
{
    bool flag = runTest(5);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestDefault)
{
    bool flag = runTest(6);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestNegativeValue1)
{
    bool flag = runTest(7);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestNegativeValue2)
{
    bool flag = runTest(8);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestNegativeValue3)
{
    bool flag = runTest(9);
    EXPECT_EQ(flag, true);
}

TEST(LongIntegerTest, TestOneOneOne)
{
    bool flag = runTest(10);
    EXPECT_EQ(flag, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}