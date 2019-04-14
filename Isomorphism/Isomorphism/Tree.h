#pragma once
#include <vector>
#include <string>

struct Tree {
    int data;
    bool checked;
    std::vector<Tree*> branches;
};

typedef Tree* PTree;

PTree createTree(std::string s);

int getNumber(std::string s);

int searchComma(std::string s);

void checkIsomorphism(PTree tree1, PTree tree2);

void clearChecked(PTree tree);

bool checkCorrectness(std::string s);

bool isNumber(char c);