#pragma once
#include <fstream>

const int maxSize = 128;

class LongInteger {
    int* arr = new int[maxSize];
    int length = 0;
    enum numberSign {negative = -1, zero, positive};
    numberSign sign = zero;

    //Utilities
    int compareAbsoluteValues(const LongInteger& n) const;
    int compareSigns(const LongInteger& n) const;
    void reduce();
    void initialize() const;
    LongInteger subtract(const LongInteger& a, const LongInteger& b) const;
    LongInteger add(const LongInteger& a, const LongInteger& b) const;
    int dichotomy(const LongInteger& n) const;
    void changeSign();
    void extractPart(LongInteger& a, LongInteger& b, const LongInteger& c) const;
    int divide(LongInteger& a, const LongInteger& b) const;
    void returnRemainder(LongInteger& a, LongInteger& b) const;
    void reverse();
    LongInteger abs(const LongInteger& n) const;
    bool isZero() const;

public:
    //Constructors
    LongInteger();
    LongInteger(int n);
    LongInteger(const LongInteger& n);

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

    bool operator>(const int& n) const;
    bool operator<(const int& n) const;
    bool operator==(const int& n) const;
    bool operator!=(const int& n) const;
    bool operator>=(const int& n) const;
    bool operator<=(const int& n) const;

    //Getters and setters
    int getLength() const;
    void setLength(int length);
    int* getArr() const;
    numberSign getSign() const;
    void setSign(numberSign sign);
};
