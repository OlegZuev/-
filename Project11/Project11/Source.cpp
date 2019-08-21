#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

bool pred(int a, int b) {
    return a % 10 > b % 10;
}

void main() {
    ifstream fin("input.txt");
    int temp;
    vector<int> vec;
    while (fin >> temp) {
        vec.push_back(temp);
    }
    sort(vec.begin(), vec.end(), pred);
    for (int i : vec) {
        cout << i << " ";
    }
}
