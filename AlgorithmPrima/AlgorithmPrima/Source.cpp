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

void fillingData(ifstream& fin, vector<vector<char>>& matrix, vector<vector<char>>& mask, vector<Peak*>& peaks);

void connectPeak(vector<Peak*> peaks, vector<vector<char>> mask, vector<Edge>& edges, Edge minValue);

bool isAllPeakIncluded(vector<Peak*> peaks);

bool isCycle(Peak* prev, Peak* next);

void searchMinPos(vector<vector<char>>& matrix, vector<vector<char>>& mask, bool first, Edge& minValue, vector<Peak*> peaks);

void writeResult(ofstream& fout, vector<vector<char>> matrix, vector<Edge> edges);

void main() {
    string input = "input.txt";
    string output = "output.txt";
    ifstream fin(input);
    ofstream fout(output);
    vector<vector<char>> matrix;
    vector<vector<char>> mask;
    vector<Peak*> peaks;
    Edge minValue;
    vector<Edge> edges;
    fillingData(fin, matrix, mask, peaks);

    bool first = true;
    searchMinPos(matrix, mask, first, minValue, peaks); 
    connectPeak(peaks, mask, edges, minValue);
    first = false;

    while (!isAllPeakIncluded(peaks)) {
        searchMinPos(matrix, mask, first, minValue, peaks);
        if (!isCycle(peaks[minValue.y], peaks[minValue.x])) {
            connectPeak(peaks, mask, edges, minValue);
        } else {
            mask[minValue.y][minValue.x] = 'x';
            mask[minValue.x][minValue.y] = 'x';
        }
    }

    writeResult(fout, matrix, edges);
    fin.close();
    fout.close();
}

void fillingData(ifstream& fin, vector<vector<char>>& matrix, vector<vector<char>>& mask, vector<Peak*>& peaks) {
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
    for (auto& i : matrix) {
        mask.emplace_back(i.size(), '-');
    }
    for (int i = 0; i < size; ++i) {
        peaks.push_back(new Peak);
        peaks[i]->number = i;
        peaks[i]->isIncluded = false;
    }
}

void connectPeak(vector<Peak*> peaks, vector<vector<char>> mask, vector<Edge>& edges, Edge minValue) {
    peaks[minValue.y]->next.push_back(peaks[minValue.x]);
    peaks[minValue.x]->next.push_back(peaks[minValue.y]);
    peaks[minValue.x]->isIncluded = true;
    mask[minValue.y][minValue.x] = '+';
    mask[minValue.x][minValue.y] = '+';
    if (minValue.y > minValue.x) {
        swap(minValue.y, minValue.x);
    }
    edges.push_back(minValue);
}

bool isAllPeakIncluded(vector<Peak*> peaks) {
    for (Peak* element : peaks) {
        if (!element->isIncluded) {
            return false;
        }
    }
    return true;
}

bool isCycle(Peak* prev, Peak* next) {
    return prev->isIncluded && next->isIncluded;
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
}

void writeResult(ofstream& fout, vector<vector<char>> matrix, vector<Edge> edges) {
    int sum = 0;
    for (auto element : edges) {
        sum += matrix[element.y][element.x] - '0';
    }
    fout << sum << endl;
    for (auto element : edges) {
        fout << element.y + 1 << ' ' << element.x + 1 << endl;
    }
}