#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

/*void main() {
	string word;
	cin >> word;
	int u1_index = word.find_first_of('u');
	int u2_index = word.find_last_of('u');
	if (word.length() % 2 != 0) {
		cout << "NO";
		return;
	}
	if (u2_index - u1_index == 1) {
		if (u1_index % 2 != 0) {
			cout << "NO";
			return;
		} else {
			cout << "YES";
			return;
		}
	}
	if (u1_index >= u2_index - u1_index - 1) {
		cout << "YES";
		return;
	}
	if ((word.length() - 1) - u2_index >= u2_index - u1_index * 2 - 1) {
		cout << "YES";
		return;
	}
	cout << "NO";
}*/

void printMatrix(vector<vector<bool>> used) {
	for (size_t i = 0; i < used.size(); i++) {
		for (size_t j = 0; j < used.size(); j++) {
			if (used[i][j]) {
				cout << "X ";
			} else {
				cout << "O ";
			}
		}
		cout << endl;
	}
}

bool twoInLine(vector<vector<bool>> used, int y) {
	int acc = 0;
	for (size_t i = 0; i < used.size(); i++) {
		if (used[i][y]) {
			if (acc == 0) {
				acc = 1;
			} else {
				return true;
			}
		}
	}
	return false;
} 

bool twoInVertical(vector<vector<bool>> used, int x) {
	int acc = 0;
	for (size_t i = 0; i < used.size(); i++) {
		if (used[x][i]) {
			if (acc == 0) {
				acc = 1;
			} else {
				return true;
			}
		}
	}
	return false;
}

bool twoInDiagonals(vector<vector<bool>> used, int x, int y) {
	int acc = 0;
	int shift = min(x, y);
	for (size_t i = x - shift, j = y - shift; i < used.size() && j < used.size(); i++, j++) {
		if (used[i][j]) {
			if (acc == 0) {
				acc = 1;
			} else {
				return true;
			}
		}
	}
	acc = 0;
	shift = used.size() - max(x ,y);
	for (size_t i = x + shift, j = y - shift; i < used.size() && j < used.size(); i--, j++) {
		if (used[i][j]) {
			if (acc == 0) {
				acc = 1;
			} else {
				return true;
			}
		}
	}
	return false;
}

void bruteForce(vector<vector<bool>> used, int x, int y, int count, bool& done) {
	used[x][y] = true;
	if (done) {
		return;
	}
	if (count == used.size() * 2) {
		printMatrix(used);
		done = true;
		return;
	}
	for (size_t i = 0; i < used.size(); i++) {
		for (size_t j = 0; j < used.size(); j++) {
			if (!used[i][j] && !twoInLine(used, j) && !twoInVertical(used, i) && !twoInDiagonals(used, i, j)) {
				bruteForce(used, i, j, count + 1, done);
			}
		}
	}
	used[x][y] = false;
}

void main() {
	int n;
	cin >> n;
	vector<vector<bool>> matrix(n, vector<bool>(n, false));
	bool done = false;
	bruteForce(matrix, 0, 0, 1, done);
}