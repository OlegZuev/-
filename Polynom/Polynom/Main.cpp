#include "Polynom.h"
#include "windows.h"
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string input;
    cout << "¬ведите название файла: ";
    cin >> input;
    ifstream fin(input);
    while (!fin) {
        cout << "‘айла не существует или он недоступен. ¬ведите название файла: ";
        cin >> input;
        fin.open(input);
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