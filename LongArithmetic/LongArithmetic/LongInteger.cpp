#include "LongInteger.h"

LongInteger::LongInteger()
= default;

LongInteger::LongInteger(int n)
{
    int i = 0;
    for (; n != 0; ++i) {
        arr[i] = n % 10;
        n /= 10;
    }
    length = i;
    initialize();
}

LongInteger LongInteger::operator+(const LongInteger& n) const
{
    const int length = this->length > n.getLength() ? this->length : n.getLength();
    LongInteger foo = *this;
    foo.setLength(length + 1);
    for (int i = 0; i < length; ++i) {
        foo.getArr()[i] += n.getArr()[i];
        foo.getArr()[i + 1] += foo.getArr()[i] / 10;
        foo.getArr()[i] %= 10;
    }
    foo.reduce();
    return foo;
}

LongInteger LongInteger::operator-(const LongInteger& n) const
{
    if (*this >= n) {
        return subtract(*this, n);
    }
    LongInteger l = subtract(n, *this);
    l.getArr()[length - 1] *= -1;
    return l;
}

LongInteger LongInteger::operator*(const LongInteger& n) const
{
    LongInteger l(0);
    const int length = this->length + n.getLength() + 1;
    for (int i = 0; i < length; ++i) {
        l.getArr()[i] = 0;
    }
    for (int i = 0; i < this->length; ++i) {
        for (int j = 0; j < n.getLength(); ++j) {
            l.getArr()[i + j] += arr[i] * n.getArr()[j];
        }
    }
    for (int i = 0; i < length; ++i) {
        l.getArr()[i + 1] += l.getArr()[i] / 10;
        l.getArr()[i] %= 10;
    }
    l.setLength(length);
    l.reduce();
    return l;
}

LongInteger LongInteger::operator/(const LongInteger& n) const
{
    int count = 0;
    LongInteger foo = *this;
    while (foo >= n) {
        foo = foo - n;
        count++;
    }
    return {count};
}

LongInteger LongInteger::operator%(const LongInteger& n) const
{
    LongInteger foo = *this;
    while (foo >= n) {
        foo = foo - n;
    }
    return *this;
}

LongInteger LongInteger::operator+(const int& n) const
{
    return *this + LongInteger(n);
}

LongInteger LongInteger::operator-(const int& n) const
{
    return *this - LongInteger(n);
}

LongInteger LongInteger::operator*(const int& n) const
{
    return *this * LongInteger(n);
}

LongInteger LongInteger::operator/(const int& n) const
{
    return *this / LongInteger(n);
}

LongInteger LongInteger::operator%(const int& n) const
{
    return *this % LongInteger(n);
}

bool LongInteger::operator>(const LongInteger& n) const
{
    return sign(n) == 1;
}

bool LongInteger::operator<(const LongInteger& n) const
{
    return sign(n) == 2;
}

bool LongInteger::operator==(const LongInteger& n) const
{
    return sign(n) == 3;
}

bool LongInteger::operator!=(const LongInteger& n) const
{
    return !(*this == n);
}

bool LongInteger::operator>=(const LongInteger& n) const
{
    return *this > n || *this == n;
}

bool LongInteger::operator<=(const LongInteger& n) const
{
    return *this < n || *this == n;
}

int LongInteger::getLength() const
{
    return length;
}

void LongInteger::setLength(int length)
{
    this->length = length;
}

int* LongInteger::getArr() const
{
    return arr;
}

int LongInteger::sign(const LongInteger& n) const
{
    int flag = 3; // если flag == 3, значит числа одинаковой длинны
    int length = this->length;
    if (this->length > n.getLength()) {
        flag = 1; // если flag == 1, значит первое число длиннее второго
    } else if (n.getLength() > this->length) {
        flag = 2; // если flag == 2, значит второе число длиннее первого
    } else {// если числа одинаковой длинны, то необходимо сравнить их вес
        for (int i = length - 1; i >= 0; --i) { // поразрядное сравнение веса чисел
            if (arr[i] > n.getArr()[i]) // если разряд первого числа больше
            {
                flag = 1; // значит первое число длиннее второго
                break; // выход из цикла for
            }

            if (n.getArr()[i] > arr[i]) // если разряд второго числа больше
            {
                flag = 2; // значит второе число длиннее первого
                break; // выход из цикла for
            }
        }
    }
    return flag;
}

void LongInteger::reduce()
{
    if (arr[length - 1] == 0) {
        length--;
        reduce();
    }
}

void LongInteger::initialize() const
{
    for (int i = length; i < maxSize; ++i) {
        arr[i] = 0;
    }
}

LongInteger LongInteger::subtract(LongInteger a, const LongInteger& b) const
{
    const int countDigit = a.getLength() - b.getLength();
    for (int i = 0; i < b.getLength(); ++i) {
        if (countDigit == 0 && i == b.getLength() - 1) {
            a.getArr()[i] -= b.getArr()[i];
            break;
        }
        a.getArr()[i + 1]--;
        a.getArr()[i] += 10 - b.getArr()[i];
        a.getArr()[i + 1] += a.getArr()[i] / 10;
        a.getArr()[i] %= 10;
    }
    a.reduce();
    return a;
}

int LongInteger::dichotomy(const LongInteger& n)
{
    const int powerOfTen = this->length - n.getLength();
    int start = 0;
    int end = pow(10, powerOfTen);
    while (end - start > 1) {
        if (*this - n * end < 0) {
            end = start + (end - start) / 2;
        }
    }
    return 0;
}

std::ostream& operator<<(std::ostream& out, const LongInteger& n)
{
    if (n.getLength() == 0) {
        out << 0;
    }
    for (int i = n.getLength() - 1; i >= 0; --i) {
        out << n.getArr()[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, LongInteger& n)
{
    int temp;
    in >> temp;
    n = LongInteger(temp);
    return in;
}
