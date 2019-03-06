#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Edge {
    int y;
    int x;
};

void fillingData(ifstream& fin, vector<vector<char>>& matrix);

void connectPeak(vector<bool>& peaks, Edge& edge);

bool isAllPeakIncluded(vector<bool> peaks);

void searchMinEdge(vector<vector<char>>& matrix, vector<Edge>& edges, vector<bool>& peaks);

void writeResult(ofstream& fout, vector<vector<char>> matrix, vector<Edge> edges);

int main() {
    string input = "input.txt";
    string output = "output.txt";
    ifstream fin(input);
    ofstream fout(output);
    int size;
    fin >> size;
    vector<vector<char>> matrix(size, vector<char>(size));
    fillingData(fin, matrix);
    vector<bool> peaks(size, false);
    vector<Edge> edges;

    searchMinEdge(matrix, edges, peaks);
    peaks[edges.back().y] = true;
    connectPeak(peaks, edges.back());
    
    while (!isAllPeakIncluded(peaks)) {
        searchMinEdge(matrix, edges, peaks);
        connectPeak(peaks, edges.back());
    }
    
    writeResult(fout, matrix, edges);
    fin.close();
    fout.close();
    return 0;
}

void fillingData(ifstream& fin, vector<vector<char>>& matrix) {
    for (vector<char>& line : matrix) {
        for (char& c : line) {
            fin >> c;
        }
    }
}

void connectPeak(vector<bool>& peaks, Edge& edge) {
    peaks[edge.x] = true;
    if (edge.y > edge.x) {
        swap(edge.y, edge.x);
    }
}

bool isAllPeakIncluded(vector<bool> peaks) {
    for (bool element : peaks) {
        if (!element) {
            return false;
        }
    }
    return true;
}

void searchMinEdge(vector<vector<char>>& matrix, vector<Edge>& edges, vector<bool>& peaks) {
    edges.emplace_back();
    edges.back().x = -1;
    edges.back().y = -1;
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (peaks[i] || edges.size() == 1) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (i != j && !peaks[j]) {
                    edges.back().x = j;
                    edges.back().y = i;
                    i = matrix.size();
                    break;
                }
            }
        }
    }
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (peaks[i] || edges.size() == 1) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (i != j && !peaks[j] && matrix[i][j] < matrix[edges.back().x][edges.back().y]) {
                    edges.back().x = j;
                    edges.back().y = i;
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