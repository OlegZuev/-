#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

set<string> readSentence();

bool comparator(string a, string b) {
    return a > b;
}

int main() {
    set<string> sentence1 = readSentence();
    set<string> sentence2 = readSentence();
    vector<string> result;
    //sort(sentence1.begin(), sentence1.end());
    //sort(sentence2.begin(), sentence2.end());

    set_symmetric_difference(sentence1.begin(), sentence1.end(), sentence2.begin(), sentence2.end(), back_inserter(result), comparator);
    for (string s : result) {
        cout << s << " ";
    }
}

set<string> readSentence() {
    set<string> text;
    string word;
    while (cin >> word) {
        text.insert(word);
        if (word[word.length() - 1] == '.') {
            break;
        }
    }
    return text;
}