#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <iterator>
#include <fstream>
#include <iomanip>
using namespace std;

set<string> readSentence(ifstream& fin);

string readWord(string s);

int main() {
    setlocale(LC_ALL, "Russian");
    string input = "input.txt";
    ifstream fin(input);
    set<string> sentence1 = readSentence(fin);
    set<string> sentence2 = readSentence(fin);
    set<string> result;
    set_intersection(sentence1.begin(), sentence1.end(), sentence2.begin(), sentence2.end(), inserter(result, result.begin()));

    for (const string& word : result) {
        cout << word << " ";
    }
    fin.close();
    return 0;
}

set<string> readSentence(ifstream& fin) { //Каждое предложение в отдельной строке
    set<string> text;
    string word;
    while (fin.peek() != '\n' && fin >> word) {
        word = readWord(word);
        if (!word.empty()) {
            text.insert(word);
        }
    }
    fin >> ws;
    return text;
}

string readWord(string s) {
    string word;
    for (char c : s) {
        if (c >= 'а' && c <= 'я' || c >= 'А' && c <= 'Я' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
            word += toupper(c);
        }
    }
    return word;
}