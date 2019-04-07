#include <iostream>
#include <list>
using namespace std;

void inputNumbers(int n, list<int>& numbers);

void printNumbers(list<int> numbers);

void cyclicalPermutation(list<int>& numbers);

int main() {
    int n;
    cin >> n;
    list<int> numbers;
    inputNumbers(n, numbers);
    printNumbers(numbers);
    cyclicalPermutation(numbers);
    printNumbers(numbers);
}

void inputNumbers(int n, list<int>& numbers) {
    for (int i = 0; i < n; ++i) {
        int data;
        cin >> data;
        numbers.push_back(data);
    }
}

void printNumbers(list<int> numbers) {
    for (int i : numbers) {
        cout << i << ' ';
    }
    cout << endl;
}

void cyclicalPermutation(list<int>& numbers) {
    for (int i = 0; i < numbers.size() - 1; ++i) {
        numbers.splice(numbers.end(), numbers, numbers.begin());
    }
}