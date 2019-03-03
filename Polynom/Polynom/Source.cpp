#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Polynom {
    int coefficient;
    int degree;
    char symbol;
    Polynom* next;
};

void readPolynom(ifstream& fin, Polynom*& head);

void writePolynom(ofstream& fout, Polynom* head);

int takeNumber(string s);

Polynom* takeTerm(ifstream& fin, char& operand);

bool operator>(const Polynom& oper1, const Polynom& oper2);

void calculateExp(Polynom* head);

bool isNumber(string elem);

void deletePolynom(Polynom* head);

int main() {
    string input = "input.txt";
    ifstream fin(input);  
    Polynom* head;
    readPolynom(fin, head);
    fin.close();
    calculateExp(head);
    ofstream fout(input, ios::app);
    fout << endl;
    writePolynom(fout, head);
    deletePolynom(head);
    fout.close();
}

/**
 * Процедура для считывания многочлена из файла.
 * @param fin входной поток
 * @param head голова результирующего списка
 */
void readPolynom(ifstream& fin, Polynom*& head) {
    char operand = '+';
    head = takeTerm(fin, operand);
    while (!fin.eof()) {
        Polynom* elem = takeTerm(fin, operand);
        Polynom* cur = head;
        if (*elem > *cur) {
            elem->next = head;
            head = elem;
            continue;
        }
        while (cur->next != nullptr && *cur->next > *elem) {
            cur = cur->next;
        }
        elem->next = cur->next;
        cur->next = elem;
    }
}

/**
 * Процедура для записи многочлена в файл.
 * @param fout выходной поток
 * @param head голова записываемого списка
 */
void writePolynom(ofstream& fout, Polynom* head) {
    Polynom* cur = head;
    int firstElem = true;
    while (cur != nullptr) {
        if (cur->coefficient != 0) {
            if (cur->coefficient > 0 && !firstElem) {
                fout << '+';
            }
            if (abs(cur->coefficient) != 1) {
                fout << cur->coefficient;
            }
            if (cur->symbol != NULL) {
                fout << cur->symbol;
            }
            if (cur->degree > 1) {
                fout << '^' << cur->degree;
            }
            firstElem = false;
        }
        cur = cur->next;
    }
}

/**
 * Функция, которая возвращает число из строки.
 * @param s входная строка
 */
int takeNumber(string s) {
    int number = 0;
    for (int i = 0; i < s.length() && s[i] >= '0' && s[i] <= '9'; ++i) {
        number = number * 10 + (s[i] - '0'); 
    }
    return !s.empty() ? number : 1;
}


/**
 * Функция, которая возвращает считанный член полинома.
 * @param fin входной поток
 * @param operand знак перед переменной
 */
Polynom* takeTerm(ifstream& fin, char& operand) {
    bool flag = operand == '-';
    string elem;
    char c;
    while (fin >> c && c != '+' && c != '-') {
        elem += c;
    }
    operand = c;
    int indexOfLid = elem.find('^');
    Polynom* term = new Polynom;
    if (isNumber(elem)) {
        term->coefficient = takeNumber(elem);
        term->symbol = NULL;
        term->degree = 1;
    } else if (indexOfLid != -1) {
        term->coefficient = takeNumber(elem.substr(0, indexOfLid));
        term->degree = takeNumber(elem.substr(indexOfLid + 1));
        term->symbol = elem[indexOfLid - 1];
    } else {
        term->coefficient = takeNumber(elem.substr(0, elem.length() - 1));
        term->symbol = elem[elem.length() - 1];
        term->degree = 1;
    }
    if (flag) {
        term->coefficient *= -1;
    }
    term->next = nullptr;
    return term;
}

bool operator>(const Polynom& oper1, const Polynom& oper2) {
    if (oper1.symbol > oper2.symbol) {
        return true;
    }
    if (oper1.symbol == oper2.symbol && oper1.degree > oper2.degree) {
        return true;
    }
    return oper1.symbol == oper2.symbol && oper1.degree == oper2.degree && oper1.coefficient > oper2.coefficient;
}

/**
 * Функция приводит подобные в списке.
 * @param head голова входного списка
 */
void calculateExp(Polynom* head) {
    Polynom* cur = head;
    while (cur != nullptr && cur->next != nullptr) {
        if (cur->symbol == cur->next->symbol && cur->degree == cur->next->degree) {
            cur->coefficient += cur->next->coefficient;
            Polynom* temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
        }
        cur = cur->next;
    }
}

bool isNumber(string elem) {
    for (char c : elem) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

void deletePolynom(Polynom* head) {
    if (head->next != nullptr) {
        deletePolynom(head->next);
    }
    delete head;
}