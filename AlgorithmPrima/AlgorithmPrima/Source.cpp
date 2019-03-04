#include <fstream>
#include <vector>
using namespace std;

struct Edge {
    int y;
    int x;
};

struct Peak {
    int number;
    vector<Peak*> next;
    bool isIncluded;
};

//ToDo: реализовать граф в виде двусвязного списка

void fillingData(ifstream& fin, vector<vector<char>>& matrix);

//bool isPeakIncluded(vector<vector<char>>& mask, int x, int y);

bool isAllPeakIncluded(vector<Peak*> peaks);

bool isCycle(Peak* original, Peak* prev, Peak* peak, int length);

void searchMinPos(vector<vector<char>>& matrix, vector<vector<char>>& mask, bool first, Edge& minValue, vector<Peak*> peaks);

void main() {
    string input = "input.txt";
    string output = "output.txt";
    ifstream fin(input);
    ofstream fout(output);
    vector<vector<char>> matrix;
    fillingData(fin, matrix);

    vector<vector<char>> mask;
    for (auto& i : matrix) {
        mask.emplace_back(i.size(), '-');
    }
    vector<Peak*> peaks;
    for (int i = 0; i < matrix.size(); ++i) {
        peaks.push_back(new Peak);
        peaks[i]->number = i;
        peaks[i]->isIncluded = false;
    }
    Edge minValue;
    vector<Edge> edges;

    bool first = true;
    searchMinPos(matrix, mask, first, minValue, peaks); 
    peaks[minValue.y]->next.push_back(peaks[minValue.x]);
    peaks[minValue.x]->next.push_back(peaks[minValue.y]);
    peaks[minValue.x]->isIncluded = true;
    mask[minValue.y][minValue.x] = '+';
    mask[minValue.x][minValue.y] = '+';
    first = false;
    edges.push_back(minValue);

    while (!isAllPeakIncluded(peaks)) {
        searchMinPos(matrix, mask, first, minValue, peaks);
        peaks[minValue.y]->next.push_back(peaks[minValue.x]);
        peaks[minValue.x]->next.push_back(peaks[minValue.y]);
        peaks[minValue.x]->isIncluded = true;
        mask[minValue.y][minValue.x] = '+';
        mask[minValue.x][minValue.y] = '+';
        if (isCycle(peaks[minValue.y], peaks[minValue.y], peaks[minValue.y], 1)) {
            peaks[minValue.y]->next.pop_back();
            peaks[minValue.x]->next.pop_back();
            //peaks[minValue.x]->isIncluded = false;
            mask[minValue.y][minValue.x] = 'x';
            mask[minValue.x][minValue.y] = 'x';
        } else {
            edges.push_back(minValue);
        }
    }

    int sum = 0;
    for (auto element : edges) {
        sum += matrix[element.y][element.x] - '0';
    }
    fout << sum << endl;
    for (auto element : edges) {
        fout << element.y + 1 << ' ' << element.x + 1 << endl;
    }
}

void fillingData(ifstream& fin, vector<vector<char>>& matrix) {
    int size;
    fin >> size;
    for (int i = 0; i < size; ++i) {
        matrix.emplace_back();
        for (int j = 0; j < size; ++j) {
            char date;
            fin >> date;
            matrix[i].push_back(date);
        }
    }
}

bool isAllPeakIncluded(vector<Peak*> peaks) {
    for (Peak* element : peaks) {
        if (!element->isIncluded) {
            return false;
        }
    }
    return true;
}

bool isCycle(Peak* original, Peak* prev, Peak* peak, int length) {
    for (auto& elem : peak->next) {
        if (prev != original && elem == original) {
            return length > 2;
        }
    }
    for (int i = 0; i < peak->next.size(); ++i) {
        bool flag = false;
        if (peak->next[i] != prev) {
            flag = isCycle(original, peak, peak->next[i], length + 1);
        }
        if (flag) {
            return true;
        }
    }
    return false;
}

void searchMinPos(vector<vector<char>>& matrix, vector<vector<char>>& mask, bool first, Edge& minValue, vector<Peak*> peaks) {
    minValue.x = -1;
    minValue.y = -1;
    for (int i = 0; i < matrix.size(); ++i) {
        if (peaks[i]->isIncluded || first) {
            for (int j = 0; j < matrix.size(); ++j) {
                if (i != j && mask[i][j] != '+') {
                    minValue.x = j;
                    minValue.y = i;
                    i = matrix.size();
                    break;
                }
            }
        }
    }
    if (first) {
        peaks[minValue.y]->isIncluded = true;
    }
    for (int i = 0; i < matrix.size(); ++i) {
        if (peaks[i]->isIncluded) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (i != j && mask[i][j] != 'x' && mask[i][j] != '+' && matrix[i][j] < matrix[minValue.x][minValue.y]) {
                    minValue.x = j;
                    minValue.y = i;
                }
            }
        }
    }
    if (minValue.y > minValue.x) {
        swap(minValue.y, minValue.x);
    }
}