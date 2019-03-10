#include "pch.h"
#include "../Polynom/Polynom.cpp"

bool compareLists(Polynom* head1, Polynom* head2) {
    while (true) {
        if (head1->coefficient != head2->coefficient || head1->degree != head2->degree || head1->symbol != head2->symbol) {
            if (head1->coefficient != 0 && head2->coefficient != 0) {
                return false;
            }
        }
        if (head1->next == nullptr && head2->next != nullptr) {
            return false;
        }
        if (head1->next != nullptr && head2->next == nullptr) {
            return false;
        }
        if (head1->next == nullptr && head2->next == nullptr) {
            return true;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
}

bool runTest(const int n) {
    std::string input = "input" + std::to_string(n) + ".txt";
    std::string answer = "answer" + std::to_string(n) + ".txt";
    std::ifstream fin(input);
    Polynom *head1, *head2;
    readPolynom(fin, head1);
    fin.close();
    fin.open(answer);
    readPolynom(fin, head2);
    fin.close();
    calculateExp(head1);
    bool result = compareLists(head1, head2);
    deletePolynom(head1);
    deletePolynom(head2);
    return result;
}

TEST(Test, TestDefault) {
    EXPECT_TRUE(runTest(1));
}

TEST(Test, TestDirectOrder) {
    EXPECT_TRUE(runTest(2));
}

TEST(Test, TestMixedOrder) {
    EXPECT_TRUE(runTest(3));
}

TEST(Test, TestZeroCases) {
    EXPECT_TRUE(runTest(4));
}

TEST(Test, TestZeroWithSum) {
    EXPECT_TRUE(runTest(5));
}

TEST(Test, TestZeroInRow) {
    EXPECT_TRUE(runTest(6));
}

TEST(Test, TestZeroWithPerem) {
    EXPECT_TRUE(runTest(7));
}

TEST(Test, TestMixedOrder2) {
    EXPECT_TRUE(runTest(8));
}

TEST(Test, TestMixedOrder3) {
    EXPECT_TRUE(runTest(9));
}

TEST(Test, TestNumbers) {
    EXPECT_TRUE(runTest(10));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}