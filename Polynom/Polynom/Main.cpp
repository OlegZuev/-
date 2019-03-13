#include "Polynom.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    string input;
    cout << "Введите название файла: ";
    cin >> input;
    ifstream fin(input);
    while (!fin) {
        cout << "Файла не существует или он недоступен. Введите название файла: ";
        cin >> input;
        fin.open(input);
    }
    if (fin.peek() == 0xEF) { //Пропуск BOM-метки в начале файле в формате UTF-8 с BOM
        fin.ignore(3);
    }
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