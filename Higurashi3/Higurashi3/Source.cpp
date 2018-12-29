#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <filesystem>
using namespace std;
namespace fs = experimental::filesystem;

bool isCharacterName(string s);

void fillNamesEng();

void fillNamesRus();

void writeInFileConvertedDate(ifstream& fin, ifstream& finTwo, ofstream& fout, string buff);

void writeInFileConvertedVoiceMatching(ifstream& finThree, ifstream& finTwo, ofstream& foutThree, ifstream& fin,
                                       ofstream& fout, string filename, string endOne);

void formatFileZwata(const string& filename, const string& end);

void runConvert(string filename);

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
        if (it->path().string().find("vm0") == -1) {
            namesFile.push_back(it->path().filename().string());
        }
    }
    for (int i = 0; i < namesFile.size(); ++i) {
        cout << i << "/" << namesFile.size() << " " << namesFile[i] << endl;
        runConvert(namesFile[i]);
    }
    return 0;
}

bool isCharacterName(string s)
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

void writeInFileConvertedDate(ifstream& fin, ifstream& finTwo, ofstream& fout, string buff)
{
    for (int i = 0; !fin.eof(); ++i) {
        fout << buff << endl;
        getline(fin, buff);
        if (buff.find("void dialog") != -1) {
            return;
        }
        if (isCharacterName(buff)) {   
             do {
                int ind = 0;
                for (; ind < namesEng.size(); ++ind) {
                    if (buff.find(namesEng[ind]) != -1) {
                        break;
                    }
                }
                if (namesRus[ind] == namesEng[ind]) {
                    break;
                }
                buff.replace(buff.find(namesEng[ind]), namesEng[ind].length(), namesRus[ind]);
             } while (isCharacterName(buff));
        } else if (buff.find("</color>") != -1) {
            cout << "New name in line " << i + 3 << " z file. Waiting for pressing any key and enter." << endl;
            cin >> buff;
        } else if (buff.find(" NULL, \"") != -1 || buff.find("\tNULL, \"") != -1) {
            string s;
            for (int j = 0; !finTwo.eof(); ++j) {
                getline(finTwo, s);
                if (s.find(" NULL, \"") != -1 || s.find("\tNULL, \"") != -1) {
                    break;
                }
            }
            buff.replace(buff.find_first_of('\"'), buff.find_last_of('\"') - buff.find_first_of('\"'),
                s.substr(s.find_first_of('\"'), s.find_last_of('\"') - s.find_first_of('\"')));
        }
    }
}

void writeInFileConvertedVoiceMatching(ifstream& finThree, ifstream& finTwo, ofstream& foutThree, ifstream& fin,
                                       ofstream& fout, string filename, string endOne)
{
    finThree.open("./eng/z" + filename.substr(0, filename.length() - 4) + endOne);
    if (!foutThree.is_open()) {
        foutThree.open("./temp/z" + filename.substr(0, filename.length() - 4) + endOne);
        string str;
        for (int k = 0; k < 4; ++k) {
            getline(finThree, str);
            foutThree << str << endl;
        }
    }
    string buff;
    getline(fin, buff);
    fout << buff << endl;
    string key = buff.substr(buff.find("dialog"), 9);
    for (int j = 0; !finThree.eof(); ++j) {
        getline(finThree, buff);
        if (buff.find(key) != -1) {
            writeInFileConvertedDate(finThree, finTwo, foutThree, buff);
            break;
        }
    }
    finThree.close();
}

void formatFileZwata(const string& filename, const string& end)
{
    ifstream fin("./temp/z" + filename.substr(0, filename.length() - 4) + end);
    ofstream fout("./result/z" + filename.substr(0, filename.length() - 4) + end);
    string buff;
    for (int i = 0; i < 4; ++i) {
        getline(fin, buff);
        fout << buff << endl;
    }
    string maxDialog = "dialog000";
    for (int i = 0; !fin.eof(); ++i) {
        getline(fin, buff);
        if (buff.find("dialog") != -1) {
            string compare = buff.substr(buff.find("dialog"), 9);
            if (compare > maxDialog) {
                maxDialog = compare;
            }
        }
    }
    fin.clear();
    fin.seekg(0, ios::beg);
    string curDialog = "dialog000";
    for (int i = 1; curDialog < maxDialog; ++i) {
        for (int j = 0; !fin.eof(); ++j) {
            getline(fin, buff);
            if (buff.find(curDialog) != -1) {
                fout << buff << endl;
                for (int k = 0; !fin.eof(); ++k) {  
                    getline(fin, buff);
                    if (buff.find("dialog") != -1) {
                        goto label1;
                    }
                    fout << buff << endl;

                }
            }
        }
        label1:
        curDialog = curDialog.substr(0, curDialog.length() - to_string(i).length()) + to_string(i);
        fin.clear();
        fin.seekg(0, ios::beg);
    }
    for (int i = 0; !fin.eof(); ++i) {
        getline(fin, buff);
        if (buff.find(curDialog) != -1) {
            fout << buff << endl;
            for (int k = 0; !fin.eof(); ++k) {
                getline(fin, buff);
                if (buff.find("dialog") != -1) {
                    goto label2;
                }
                fout << buff << endl;
            }
        }
    }
    label2:
    fin.close();
    fout.close();
}

void runConvert(string filename)
{
    string endOne = "_vm00_n01.txt";
    string endTwo = "_vm0x_n01.txt";
    string endOne2 = "_vm00_n02.txt";
    string endTwo2 = "_vm0x_n02.txt";
    ifstream fin("./eng/" + filename);
    ifstream finTwo("./rus/" + filename);
    ifstream finThree;
    ifstream finThree2;
    ofstream fout("./result/" + filename);
    ofstream foutThree;
    ofstream foutThree2;
    string s;
    int flag = 0;
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
                s.replace(s.find(namesEng[ind]), namesEng[ind].length(), namesRus[ind]);
            } while (isCharacterName(s));
        } else if (s.find("</color>") != -1) {
            cout << "New name in line " << i + 3 << " " << filename << endl;
            return;
        } else if (s.find("VoiceMatching") != -1 && s.find("End") == -1) {
            fout << s << endl;
            getline(fin, s);
            fout << s << endl;

            if (filename.find("omake") != -1) {
                writeInFileConvertedVoiceMatching(finThree, finTwo, foutThree, fin, fout, "tata_" + filename, endOne);
            } else if (s.find("_n01") != -1) {
                writeInFileConvertedVoiceMatching(finThree, finTwo, foutThree, fin, fout, filename, endOne);
            } else if (s.find("_n02") != -1) {
                writeInFileConvertedVoiceMatching(finThree2, finTwo, foutThree2, fin, fout, filename, endOne2);
            }
            continue;
        } else if ((s.find(" NULL, \"") != -1 || s.find("\tNULL, \"") != -1) && s.find(", NULL, \"") == -1) {
            string buff;
            for (int j = 0; !finTwo.eof(); ++j) {
                getline(finTwo, buff);
                if (buff.find(" NULL, \"") != -1) {
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
    if (foutThree.is_open()) {
        if (filename.find("omake") != -1) {
            filename = "tata_" + filename;
        }
        formatFileZwata(filename, endOne);
        foutThree.close();
        ifstream finCopy("./result/z" + filename.substr(0, filename.length() - 4) + endOne);
        ofstream foutCopy("./result/z" + filename.substr(0, filename.length() - 4) + endTwo);
        foutCopy << finCopy.rdbuf();
        finCopy.close();
        foutCopy.close();
    }
    if (foutThree2.is_open()) {
        formatFileZwata(filename, endOne2);
        foutThree2.close();
        ifstream finCopy("./result/z" + filename.substr(0, filename.length() - 4) + endOne2);
        ofstream foutCopy("./result/z" + filename.substr(0, filename.length() - 4) + endTwo2);
        foutCopy << finCopy.rdbuf();
        finCopy.close();
        foutCopy.close();
    }
}