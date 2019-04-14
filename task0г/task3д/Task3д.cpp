#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <fstream>
using namespace std;

string readWord(string s);

void fillMap(map<string, set<string>>& words, ifstream& fin, string word);

void fillGroups(map<string, set<string>>& words);

void show(map<string, set<string>> words, ofstream& fout);

int main() {
    setlocale(LC_ALL, "Russian");
    map<string, set<string>> words;
    ifstream fin("slovar.TXT");
    ofstream fout("output.txt");
    string word;
    fillMap(words, fin, word);
    fillGroups(words);
    show(words, fout);
    string s;
    fin.close();
    fout.close();
    return 0;
}

void fillMap(map<string, set<string>>& words, ifstream& fin, string word) {
    while (fin >> word) {
        reverse(word.begin(), word.end());
        words[word] = set<string>();
    }
}

void fillGroups(map<string, set<string>>& words) {
    for (auto itA = words.begin(); itA != words.end(); ++itA) {
        for (auto itB = itA; itB != words.end(); ++itB) {
            if (itA->first.length() <= itB->first.length() && itB->first.find(itA->first) == 0) {
                itA->second.insert(itB->first);
            } else {
                break;
            }
        }
    }
}

void show(map<string, set<string>> words, ofstream& fout) {
    for (auto itA = words.begin(); itA != words.end(); ++itA) {
        if (itA->second.size() > 1) {
            int i = 0;
            set<string>::iterator itB;
            string temp;
            for (itB = itA->second.begin(); i < itA->second.size() - 1; ++itB, ++i) {
                temp = *itB;
                reverse(temp.begin(), temp.end());
                fout << temp << " - ";
            }
            temp = *itB;
            reverse(temp.begin(), temp.end());
            fout << temp << endl;
        }
    }
}