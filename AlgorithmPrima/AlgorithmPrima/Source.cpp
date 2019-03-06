#include <fstream>
#include <vector>
using namespace std;

struct Edge {
    int y;
    int x;
};

void fillingData(ifstream& fin, vector<vector<int>>& matrix);

void connectPeak(vector<bool>& peaks, Edge& edge);

void searchMinEdge(vector<vector<int>>& matrix, vector<Edge>& edges, vector<bool>& peaks);

void writeResult(ofstream& fout, vector<Edge> edges, int sum);

int main() {
    string input = "input5.txt";
    string output = "output.txt";
    ifstream fin(input);
    ofstream fout(output);
    int size, sum = 0;
    fin >> size;
    vector<vector<int>> matrix(size, vector<int>(size));
    fillingData(fin, matrix);
    vector<bool> peaks(size, false);
    vector<Edge> edges;

    searchMinEdge(matrix, edges, peaks);
    peaks[edges.back().y] = true;
    connectPeak(peaks, edges.back());
    sum += matrix[edges.back().y][edges.back().x];
    
    for (int i = 0; i < size - 2; ++i) {
        searchMinEdge(matrix, edges, peaks);
        connectPeak(peaks, edges.back());
        sum += matrix[edges.back().y][edges.back().x];
    }

    writeResult(fout, edges, sum);
    fin.close();
    fout.close();
    return 0;
}

void fillingData(ifstream& fin, vector<vector<int>>& matrix) {
    for (vector<int>& line : matrix) {
        for (int& c : line) {
            if ((fin >> ws).peek() == '~') {
                c = INT_MAX;
                fin.ignore();
            } else { fin >> c; }
        }
    }
}

void connectPeak(vector<bool>& peaks, Edge& edge) {
    peaks[edge.x] = true;
    if (edge.y > edge.x) {
        swap(edge.y, edge.x);
    }
}

void searchMinEdge(vector<vector<int>>& matrix, vector<Edge>& edges, vector<bool>& peaks) {
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
                if (i != j && !peaks[j] && matrix[i][j] < matrix[edges.back().y][edges.back().x]) {
                    edges.back().x = j;
                    edges.back().y = i;
                }
            }
        }
    }
}

void writeResult(ofstream& fout, vector<Edge> edges, int sum) {
    fout << sum << endl;
    for (auto element : edges) {
        fout << element.y + 1 << ' ' << element.x + 1 << endl;
    }
}