#pragma once
#include <fstream>

class LongInteger {
    int* arr = new int[65];
    int length = 0;
    int sign(LongInteger n);
    void reduce(LongInteger& n);
    LongInteger subtract(LongInteger a, LongInteger b);

public:
    LongInteger();
    LongInteger(int n);
    LongInteger operator+(LongInteger n);
    LongInteger operator-(LongInteger n);
    LongInteger operator*(LongInteger n);
    LongInteger operator/(LongInteger n);
    LongInteger operator%(LongInteger n);
    friend std::ostream& operator<<(std::ostream& out, LongInteger& n);
    friend std::istream& operator>>(std::istream& in, LongInteger& n);
    bool operator>(LongInteger n);
    bool operator<(LongInteger n);
    bool operator==(LongInteger n);
    int getLength() const;
    void setLength(int length);
    int* getArr() const;
};
