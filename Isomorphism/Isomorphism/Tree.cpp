#include "Tree.h"

/**
 * Функция, которая возвращает созданное дерево.
 * @param s дерево в виде строки
 */
PTree createTree(std::string s) {
    if (s.empty()) {
        return nullptr;
    }
    PTree tree = new Tree;
    if (s[0] >= '0' && s[0] <= '9') {
        tree->data = getNumber(s);
        s.erase(0, std::to_string(tree->data).length());
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

/**
 * Функция, которая парсит число в строке
 * @param s строка с числом
 */
int getNumber(std::string s) {
    int n = 0;
    for (size_t i = 0; s[i] != '{' && s[i] != '}' && i < s.length(); ++i) {
        n = n * 10 + (s[i] - '0');
    }
    return n;
}

/**
 * Функция, которая возвращает индекс запятой в строке
 * @param s строка с запятой
 */
int searchComma(std::string s) {
    size_t index = 0;
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

/**
 * Процедура для проверки двух деревьев на изоморфизм. Результат сохраняется в переменную checked у деревьев типа Tree.
 * @param tree1 дерево
 * @param tree2 дерево
 */
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

/**
 * Процедура для очищения меток у дерева.
 * @param tree
 */
void clearChecked(PTree tree) {
    if (tree->branches.empty()) {
        tree->checked = false;
    }
    for (auto& branch : tree->branches) {
        clearChecked(branch);
    }
}

/**
 * Функция для проверки дерева на корректность
 * @param s строка с деревом
 */
bool checkCorrectness(std::string s) {
    if (s.empty()) {
        return false;
    }
    if (s[0] < '0' || s[0] > '9') {
        return false;
    }
    for (size_t i = 0; i < s.length(); ++i) {
        if (!isNumber(s[i]) && s[i] != '{' && s[i] != '}' && s[i] != ',') {
            return false;
        }
        if (s[i] == ',' && s[i - 1] != '}' && !isNumber(s[i - 1])) {
            return false;
        }
        if (s[i] == '{' && !isNumber(s[i - 1])) {
            return false;
        }
        if (s[i] == '}' && !isNumber(s[i - 1]) && s[i - 1] != '}') {
            return false;
        }
    }
    return true;
}

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}