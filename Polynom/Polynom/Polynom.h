#pragma once
#include <iostream>
#include <string>
#include <fstream>

struct Polynom {
    int coefficient;
    int degree;
    char symbol;
    Polynom* next;
};

void readPolynom(std::ifstream& fin, Polynom*& head);

void writePolynom(std::ofstream& fout, Polynom* head);

int takeNumber(std::string s);

Polynom* takeTerm(std::ifstream& fin);

bool operator>(const Polynom& oper1, const Polynom& oper2);

void calculateExp(Polynom*& head);

bool isNumber(std::string elem);

void deletePolynom(Polynom* head);