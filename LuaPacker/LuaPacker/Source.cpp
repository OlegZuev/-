#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
    string input, output;
    if (argc < 2) {
        cout << "Please enter input file: ";
        cin >> input;
        cout << "Please enter output file: ";
        cin >> output;
    } else {
        input = argv[1];
        output = argv[2];
    }
    ifstream fin(input);
    ofstream fout(output);
    string line;
    while (fin.peek() != EOF) {
        getline(fin, line);
        if (line.find("require") != -1 && line.find("Do not pack") == -1) {
            string filename = line.substr(line.find('\"') + 1, line.find_last_of('\"') - line.find('\"') - 1);
            ifstream fin2(filename + ".lua");
            while (fin2.peek() != EOF) {
                string temp;
                getline(fin2, temp);
                if (temp.find("---") == -1) {
                    fout << temp << endl;
                }
            }
            fin2.close();
        } else {
            fout << line << endl;
        }
    }
    fin.close();
    return 0;
}