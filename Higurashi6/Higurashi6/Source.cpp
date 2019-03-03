#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <filesystem>
using namespace std;
namespace fs = experimental::filesystem;

bool isCharacterName(const string& s);

void fillNamesEng();

void fillNamesRus();

void runConvert(const string& filename);

vector<string> namesEng;
vector<string> namesRus;
vector<string> namesFile;

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    fillNamesEng();
    fillNamesRus();

    string path = "./eng";
    for (fs::directory_iterator it(path), end; it != end; ++it) {
        namesFile.push_back(it->path().filename().string());

    }
    for (int i = 0; i < namesFile.size(); ++i) {
        cout << i << "/" << namesFile.size() << " " << namesFile[i] << endl;
        runConvert(namesFile[i]);
    }
    return 0;
}

bool isCharacterName(const string& s)
{
    for (const auto& name : namesEng) {
        if (s.find(name) != -1) {
            return true;
        }
    }
    return false;
}

void fillNamesEng()
{
    ifstream fin("namesEng.txt");
    string buff;
    for (int i = 0; !fin.eof(); ++i) {
        getline(fin, buff);
        namesEng.push_back(">" + buff + "<");
    }
    fin.close();
}

void fillNamesRus()
{
    ifstream fin("namesRus.txt");
    string buff;
    for (int i = 0; !fin.eof(); ++i) {
        getline(fin, buff);
        namesRus.push_back(">" + buff + "<");
    }
    fin.close();
}

void runConvert(const string& filename)
{
    ifstream fin("./eng/" + filename);
    ifstream finTwo("./rus/" + filename);
    ofstream fout("./result/" + filename);
    string s;
    for (int i = 0; !fin.eof(); ++i) {
        getline(fin, s);
        if (isCharacterName(s)) {
            do {
                int ind = 0;
                for (; ind < namesEng.size(); ++ind) {
                    if (s.find(namesEng[ind]) != -1) {
                        break;
                    }
                }
                if (namesRus[ind] == namesEng[ind]) {
                    break;
                }
                s.replace(s.find(namesEng[ind]), namesEng[ind].length(), namesRus[ind]);
            } while (isCharacterName(s));
        } else if (s.find("</color>") != -1) {
            cout << "New name in line " << i + 3 << " " << filename << endl;
            return;
        } else if ((s.find(" NULL, \"") != -1 || s.find("\tNULL, \"") != -1) && s.find(", NULL, \"") == -1) {
            string buff;
            for (int j = 0; !finTwo.eof(); ++j) {
                getline(finTwo, buff);
                if ((buff.find(" NULL, \"") != -1 || buff.find("\tNULL, \"") != -1) && buff.find(", NULL, \"") == -1) {
                    break;
                }
            }
            s.replace(s.find_first_of('\"'), s.find_last_of('\"') - s.find_first_of('\"'),
                buff.substr(buff.find_first_of('\"'), buff.find_last_of('\"') - buff.find_first_of('\"')));
        }
        fout << s << endl;
    }
    fin.close();
    finTwo.close();
    fout.close();
}