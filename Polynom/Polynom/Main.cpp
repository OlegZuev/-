#include "Polynom.h"
using namespace std;

int main() {
    string input;
    cout << "¬ведите название файла: ";
    cin >> input;
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