#include "Polynom.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    string input;
    cout << "������� �������� �����: ";
    cin >> input;
    ifstream fin(input);
    while (!fin) {
        cout << "����� �� ���������� ��� �� ����������. ������� �������� �����: ";
        cin >> input;
        fin.open(input);
    }
    if (fin.peek() == 0xEF) { //������� BOM-����� � ������ ����� � ������� UTF-8 � BOM
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