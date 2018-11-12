#pragma once
#include <fstream>

const int maxSize = 128;

class LongInteger {
    int* arr = new int[maxSize];
    int length = 0;

    //Utilities
    int sign(const LongInteger& n) const;
    void reduce();
    void initialize() const;
    LongInteger subtract(LongInteger a, const LongInteger& b) const;
    int dichotomy(const LongInteger& n);

public:
    //Constructors
    LongInteger();
    LongInteger(int n);

    //Arithmetic operations
    LongInteger operator+(const LongInteger& n) const;
    LongInteger operator-(const LongInteger& n) const;
    LongInteger operator*(const LongInteger& n) const;
    LongInteger operator/(const LongInteger& n) const;
    LongInteger operator%(const LongInteger& n) const;

    LongInteger operator+(const int& n) const;
    LongInteger operator-(const int& n) const;
    LongInteger operator*(const int& n) const;
    LongInteger operator/(const int& n) const;
    LongInteger operator%(const int& n) const;

    //Input and output
    friend std::ostream& operator<<(std::ostream& out, const LongInteger& n);
    friend std::istream& operator>>(std::istream& in, LongInteger& n);
    
    //Boolean operation
    bool operator>(const LongInteger& n) const;
    bool operator<(const LongInteger& n) const;
    bool operator==(const LongInteger& n) const;
    bool operator!=(const LongInteger& n) const;
    bool operator>=(const LongInteger& n) const;
    bool operator<=(const LongInteger& n) const;

    //Getters and setters
    int getLength() const;
    void setLength(int length);
    int* getArr() const;
};
