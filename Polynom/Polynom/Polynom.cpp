#include "Polynom.h"

/**
 * Процедура для считывания многочлена из файла.
 * @param fin входной поток
 * @param head голова результирующего списка
 */
void readPolynom(std::ifstream& fin, Polynom*& head) {
    fin >> std::ws;
    head = takeTerm(fin);
    while (!fin.eof()) {
        Polynom* elem = takeTerm(fin);
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
void writePolynom(std::ofstream& fout, Polynom* head) {
    Polynom* cur = head;
    int firstElem = true;
    while (cur != nullptr) {
        if (cur->coefficient == 0) {
            fout << 0;
        } else {
            if (cur->coefficient > 0 && !firstElem) {
                fout << " + ";
            } else if (cur->coefficient < 0 && !firstElem) {
                fout << " - ";
            } else if (firstElem) {
                if (cur->coefficient < 0) {
                    fout << '-';
                }
                firstElem = false;
            }
            if (abs(cur->coefficient) != 1) {
                fout << abs(cur->coefficient);
            }
            if (cur->symbol != NULL) {
                fout << cur->symbol;
            }
            if (cur->degree > 1) {
                fout << '^' << cur->degree;
            }
        }
        cur = cur->next;
    }
}

/**
 * Функция, которая возвращает число из строки.
 * @param s входная строка
 */
int takeNumber(std::string s) {
    int number = 0;
    for (size_t i = 0; i < s.length() && s[i] >= '0' && s[i] <= '9'; ++i) {
        number = number * 10 + (s[i] - '0'); 
    }
    return !s.empty() ? number : 1;
}

/**
 * Функция, которая возвращает считанный член полинома.
 * @param fin входной поток
 */
Polynom* takeTerm(std::ifstream& fin) {
    bool flag = fin.peek() == '-';
    if (fin.peek() == '-' || fin.peek() == '+') {
        fin.ignore();
    }
    fin >> std::ws;
    std::string elem;
    char c;
    while (fin.peek() != '-' && fin.peek() != '+' && fin.peek() != ' ' && fin.peek() != EOF) {
        fin >> c;
        elem += c;
    }
    fin >> std::ws;
    int indexOfLid = elem.find('^');
    Polynom* term = new Polynom;
    if (isNumber(elem)) {
        term->coefficient = takeNumber(elem);
        term->symbol = NULL;
        term->degree = 1;
    } else if (indexOfLid != -1) {
        term->coefficient = takeNumber(elem.substr(0, indexOfLid - 1));
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
 * Функция приводит подобные в списке и удаляет нулевые значения.
 * @param head голова входного списка
 */
void calculateExp(Polynom*& head) {
    Polynom* cur = head;
    while (cur != nullptr && cur->next != nullptr) {
        if (head->coefficient == 0) {
            head = head->next;
            delete cur;
            cur = head;
            continue;
        }
        if (cur->next->coefficient == 0) {
            Polynom* temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
            continue;
        }
        if (cur->symbol == cur->next->symbol && cur->degree == cur->next->degree) {
            cur->coefficient += cur->next->coefficient;
            Polynom* temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
            continue;
        }
        cur = cur->next;
    }
}

bool isNumber(std::string elem) {
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