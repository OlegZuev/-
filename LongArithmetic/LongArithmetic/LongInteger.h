#pragma once
#include <string>
#include <iostream>

const int maxSize = 128;

class LongInteger {
    int* arr = new int[maxSize];
    int length = 0;
    enum numberSign {negative = -1, zero, positive};
    numberSign sign = zero;

    //Utilities
    bool isInputCorrect(std::string n);
    void initialize() const;
    void reduce();
    void changeSign();
    void reverse();
    void extractPart(LongInteger& a, LongInteger& b, const LongInteger& c) const;
    void returnRemainder(LongInteger& a, LongInteger& b) const;

    bool isZero() const;
    int compareAbsoluteValues(const LongInteger& n) const;
    int compareSigns(const LongInteger& n) const;

    int divide(LongInteger& a, const LongInteger& b) const;
    LongInteger add(const LongInteger& a, const LongInteger& b) const;
    LongInteger subtract(const LongInteger& a, const LongInteger& b) const;
    LongInteger abs(const LongInteger& n) const;

public:
    //Constructors and destructor
    LongInteger();
    LongInteger(int n);
    LongInteger(std::string& n);
    LongInteger(const char n[]);
    LongInteger(const LongInteger& n);
    LongInteger(LongInteger&& n) noexcept;
    ~LongInteger();

    //Getters and setters
    int getLength() const;
    void setLength(int length);
    int* getArr() const;
    numberSign getSign() const;
    void setSign(numberSign sign);

    //Assignment operator and swap
    LongInteger& operator=(const LongInteger n);
    friend void swap(LongInteger& first, LongInteger& second) noexcept;

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

    //Input and output
    friend std::ostream& operator<<(std::ostream& out, const LongInteger& n);
    friend std::istream& operator>>(std::istream& in, LongInteger& n);
};
