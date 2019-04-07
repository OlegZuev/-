#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void inputNumbers(ifstream& fin, vector<int>& v);

bool compare(int a, int b);

bool isDividedBy7(int a);

void writeNumbers(ofstream& fout, vector<int> v);

void printNumbers(vector<int> numbers);

int main() {
    string input = "input.txt";
    string output = "output.txt";
    ifstream fin(input);
    ofstream fout(output);
    vector<int> numbers;
    inputNumbers(fin, numbers);
    sort(numbers.begin(), numbers.end(), compare);
    writeNumbers(fout, numbers);
    printNumbers(numbers);
    fin.close();
    fout.close();
}

void inputNumbers(ifstream& fin, vector<int>& v) {
    int data;
    while (fin >> data) {
        v.push_back(data);
    }
}

bool compare(int a, int b) {
    return to_string(a)[0] < to_string(b)[0];
}

void writeNumbers(ofstream& fout, vector<int> v) {
    for (int i : v) {
        fout << i << ' ';
    }
}

bool isDividedBy7(int a) {
    return a % 7 == 0;
}

void printNumbers(vector<int> numbers) {
    vector<int>::iterator it = numbers.begin();
    while ((it = find_if(it + 1, numbers.end(), isDividedBy7)) != numbers.end()) {
        cout << *it << ' ';
    }
}