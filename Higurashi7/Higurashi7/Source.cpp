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

void searchDelayedPairLine(ifstream& finTwo, string& buff, string& delayedLine);

void searchPairLine(ifstream& finTwo, string& buff, string& delayedLine);

bool checkLineOfSpaces(const string& text);

vector<string> namesEng;
vector<string> namesRus;
vector<string> namesFileEng;

//_mina_002_1 - don't forget about choice in the end

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    fillNamesEng();

    string pathEng = "./eng";
    for (fs::directory_iterator it(pathEng), end; it != end; ++it) {
        namesFileEng.push_back(it->path().filename().string());
    }
    for (int i = 0; i < namesFileEng.size(); ++i) {
        cout << i << "/" << namesFileEng.size() << " " << namesFileEng[i] << endl;
        runConvert(namesFileEng[i]);
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
	string delayedLine;
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
        } else if (!checkLineOfSpaces(s) && (s.find(" NULL, \"") != -1 || s.find("\tNULL, \"") != -1) && s.find(", NULL, \"") == -1) {
            string buff;
			if (delayedLine.empty()) {
				searchPairLine(finTwo, buff, delayedLine);
			} else {
				searchDelayedPairLine(finTwo, buff, delayedLine);
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

void searchDelayedPairLine(ifstream& finTwo, string& buff, string& delayedLine) {
	buff = delayedLine;
	if (buff.find("{w=") != -1) {
		int wIndex = buff.find("{w=");
		buff.replace(wIndex, buff.find('}', wIndex) - wIndex + 1, "\"9 9\"");
		delayedLine = buff.substr(buff.find("9\"") + 1);
		buff = buff.substr(0, buff.find("\"9") + 1);
	} else {
		delayedLine = "";
	}
	while (buff.find('{') != -1) {
		buff.replace(buff.find_first_of('{'), buff.find_first_of('}') - buff.find_first_of('{') + 1, "");
	}
	if (buff.find_first_of('"') - buff.find_last_of('"') == -1 ||
		buff.find_first_of('"') - buff.find_last_of('"') == -2 && buff[buff.find_first_of('"') + 1] == ' ') {
		searchPairLine(finTwo, buff, delayedLine);
	}
}

void searchPairLine(ifstream& finTwo, string& buff, string& delayedLine) {
	for (int j = 0; !finTwo.eof(); ++j) {
		getline(finTwo, buff);
		if (buff.find('\"') != -1) {
			if (buff.find(" \"{nw}\"") != -1 || buff.find("n \"") == -1 && buff.find("extend \"") == -1 && buff.find("centered \"") == -1) {
				continue;
			}
			while (buff.find("\\n") != -1) {
				buff.replace(buff.find("\\n"), 2, "");
			}
			if (buff.find("{w=") != -1) {
				int wIndex = buff.find("{w=");
				buff.replace(wIndex, buff.find('}', wIndex) - wIndex + 1, "\"9 9\"");
				delayedLine = buff.substr(buff.find("9\"") + 1);
				buff = buff.substr(0, buff.find("\"9") + 1);
			}
			while (buff.find('{') != -1) {
				buff.replace(buff.find_first_of('{'), buff.find_first_of('}') - buff.find_first_of('{') + 1, "");
			}
			if (buff.find_first_of('"') - buff.find_last_of('"') == -1 || 
				buff.find_first_of('"') - buff.find_last_of('"') == -2 && buff[buff.find_first_of('"') + 1] == ' ') {
				if (!delayedLine.empty()) {
					searchDelayedPairLine(finTwo, buff, delayedLine);
				} else {
					continue;
				}
			}
			break;
		}
	}
}

bool checkLineOfSpaces(const string& text) {
	int last = text.find_last_of('"');
	for (int i = text.find_first_of('"') + 1; i < last; ++i) {
		if (text[i] != ' ') {
			return false;
		}
	}
	return true;
}