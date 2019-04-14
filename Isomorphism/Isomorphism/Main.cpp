#include <iostream>
#include <fstream>
#include "Tree.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    string input = "input.txt";
    ifstream fin(input);
    string line;
    fin >> line;
    if (!checkCorrectness(line)) {
        cout << "Некорректные данные";
        return -1;
    }
    PTree tree1 = createTree(line);
    fin >> line;
    if (!checkCorrectness(line)) {
        cout << "Некорректные данные";
        return -1;
    }
    PTree tree2 = createTree(line);
    checkIsomorphism(tree1, tree2);
    if (tree1->checked && tree2->checked) {
        cout << "Изоморфны";
    } else {
        cout << "Не изоморфны";
    }
    return 0;
}