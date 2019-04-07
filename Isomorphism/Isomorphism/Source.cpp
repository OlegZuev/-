#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Tree {
    int data;
    bool checked;
    vector<Tree*> branches;
};

typedef Tree* PTree;

PTree createTree(string s);

int getNumber(string s);

int searchComma(string s);

void checkIsomorphism(PTree tree1, PTree tree2);

void clearChecked(PTree tree);

int main() {
    string input = "input3.txt";
    ifstream fin(input);
    string line;
    fin >> line;
    PTree tree1 = createTree(line);
    fin >> line;
    PTree tree2 = createTree(line);
    checkIsomorphism(tree1, tree2);
    if (tree1->checked && tree2->checked) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    return 0;
}

PTree createTree(string s) {
    if (s.empty()) {
        return nullptr;
    }
    PTree tree = new Tree;
    if (s[0] >= '0' && s[0] <= '9') {
        tree->data = getNumber(s);
        s.erase(0, to_string(tree->data).length());
        tree->checked = false;
    }
    if (s.length() > 1 && s[0] == '{') {
        s.erase(0, 1);
        while (!s.empty()) {
            tree->branches.emplace_back();
            int indexOfComma = searchComma(s);
            tree->branches.back() = createTree(s.substr(0, indexOfComma));
            s.erase(0, indexOfComma + 1);
        }
    }
    return tree;
}

int getNumber(string s) {
    int n = 0;
    for (int i = 0; s[i] != '{' && s[i] != '}' && i < s.length(); ++i) {
        n = n * 10 + (s[i] - '0');
    }
    return n;
}

int searchComma(string s) {
    int index = 0;
    while (s[index] != ',' && index < s.length()) {
        if (s[index] == '{') {
            int count = 0;
            for (; index < s.length(); index++) {
                if (s[index] == '}') {
                    count++;
                }
                if (s[index] == '{') {
                    count--;
                }
                if (count == 0) {
                    break;
                }
            }
        }
        index++;
    }
    return s.length() == index ? index - 1 : index;
}

void checkIsomorphism(PTree tree1, PTree tree2) {
    if (tree1->branches.size() != tree2->branches.size() || tree1->data != tree2->data) {
        return;
    }
    int length = tree1->branches.size();
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (!tree2->branches[j]->checked) {
                checkIsomorphism(tree1->branches[i], tree2->branches[j]);
            }
            if (tree1->branches[i]->checked) {
                break;
            }
        }
        if (!tree1->branches[i]->checked) {
            clearChecked(tree1);
            clearChecked(tree2);
            return;
        }
    }
    tree1->checked = true;
    tree2->checked = true;
}

void clearChecked(PTree tree) {
    for (auto& branch : tree->branches) {
        branch->checked = false;
    }
}