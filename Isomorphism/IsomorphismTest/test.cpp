#include "pch.h"
#include "../Isomorphism/Tree.cpp"

bool runTest(int n) {
    std::string input = "input" + (n == 1 ? "" : std::to_string(n)) + ".txt";
    std::string answer = "answer" + (n == 1 ? "" : std::to_string(n)) + ".txt";
    std::ifstream fin1(input);
    std::ifstream fin2(answer);
    std::string line, result, expected;
    fin1 >> line;
    std::getline(fin2, expected);
    fin2.close();
    if (!checkCorrectness(line)) {
        result = "Некорректные данные";
        return result == expected;
    }
    PTree tree1 = createTree(line);
    fin1 >> line;
    if (!checkCorrectness(line)) {
        result = "Некорректные данные";
        return result == expected;
    }
    PTree tree2 = createTree(line);
    checkIsomorphism(tree1, tree2);
    if (tree1->checked && tree2->checked) {
        result = "Изоморфны";
    } else {
        result = "Не изоморфны";
    }
    return result == expected;
}

TEST(Test, TestDefault) {
    EXPECT_TRUE(runTest(1));
}

TEST(Test, ShuffleOrder) {
    EXPECT_TRUE(runTest(2));
}

TEST(Test, ShuffleOrder2) {
    EXPECT_TRUE(runTest(3));
}

TEST(Test, ExtraElement) {
    EXPECT_TRUE(runTest(4));
}

TEST(Test, DirectOrder) {
    EXPECT_TRUE(runTest(5));
}

TEST(Test, DirectOrder2) {
    EXPECT_TRUE(runTest(6));
}

TEST(Test, List) {
    EXPECT_TRUE(runTest(7));
}

TEST(Test, IncorrectData) {
    EXPECT_TRUE(runTest(8));
}

TEST(Test, MiniTree) {
    EXPECT_TRUE(runTest(9));
}

TEST(Test, MegaTree) {
    EXPECT_TRUE(runTest(10));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}