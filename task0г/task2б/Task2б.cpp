#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;

set<string> readSentence();

int main() {
    set<string> sentence1 = readSentence();
    set<string> sentence2 = readSentence();
    set<string> result;
    result.insert("ssd");

    set_symmetric_difference(sentence1.begin(), sentence1.end(), sentence2.begin(), sentence2.end(), result.begin());
    for (string s : result) {
        cout << s << " ";
    }
    return 0;
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