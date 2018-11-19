#include "LongInteger.h"

LongInteger::LongInteger()
= default;

LongInteger::LongInteger(int n)
{
    if (n > 0) {
        sign = positive;
    } else if (n < 0) {
        sign = negative;
        n = std::abs(n);
    }
    int i = 0;
    for (; n != 0; ++i) {
        arr[i] = n % 10;
        n /= 10;
    }
    length = i;
    initialize();
}

LongInteger::LongInteger(const LongInteger& n)
{
    sign = n.getSign();
    for (int i = 0; i < n.getLength(); ++i) {
        arr[i] = n.getArr()[i]; 
    }
    length = n.getLength();
    initialize();
}

LongInteger LongInteger::operator+(const LongInteger& n) const
{
    if (sign * n.getSign() == -1) {
        if (compareAbsoluteValues(n) == 2) {
            return subtract(n, *this);
        }
        return subtract(*this, n);
    }
    return add(*this, n);
}

LongInteger LongInteger::operator-(const LongInteger& n) const
{
    if (sign * n.getSign() == -1) {
        return add(*this, n);
    }
    if (compareAbsoluteValues(n) == 2) {
        LongInteger foo = n;
        foo.changeSign();
        return subtract(foo, *this);
    }
    return subtract(*this, n);
}

LongInteger LongInteger::operator*(const LongInteger& n) const
{
    LongInteger foo(0);
    const int length = this->length + n.getLength() + 1;
    foo.initialize();
    foo.setSign(positive);
    if (sign * n.getSign() == -1) {
        foo.changeSign();
    }
    for (int i = 0; i < this->length; ++i) {
        for (int j = 0; j < n.getLength(); ++j) {
            foo.getArr()[i + j] += arr[i] * n.getArr()[j];
        }
    }
    for (int i = 0; i < length; ++i) {
        foo.getArr()[i + 1] += foo.getArr()[i] / 10;
        foo.getArr()[i] %= 10;
    }
    foo.setLength(length);
    foo.reduce();
    return foo;
}

LongInteger LongInteger::operator/(const LongInteger& n) const
{
    //Деление столбиком
    //Из всего числа берётся его часть, которая делится на n
    //Результат деления записывается в конечное число
    //В конце число перевернуть
    LongInteger result(0);
    LongInteger foo(0);
    foo.setSign(positive);
    LongInteger copy = *this;
    for (int i = 0; copy.compareAbsoluteValues(n) != 2; ++i) {
        foo.setLength(n.getLength());
        extractPart(copy, foo, n);
        if (foo < abs(n)) {
            foo.setLength(n.getLength() + 1);
            extractPart(copy, foo, n);
        }

        result.getArr()[i] = divide(foo, n);
        result.setLength(result.getLength() + 1);
        if (foo.isZero()) {
            i++;
            result.getArr()[i] = 0;
            result.setLength(result.getLength() + 1);
        }
        returnRemainder(foo, copy);

    }
    result.reverse();
    if (result.getLength() == 0) {
        result.setSign(zero);
    } else if (sign * n.getSign() == -1) {
        result.setSign(negative);
    } else {
        result.setSign(positive);
    }
    return result;
}

// const int powerOfTen = this->length - n.getLength() + 1;
// int start = 0;
// int end = pow(10, powerOfTen);
// while (end - start > 1) {
//     int pivot = start + (end - start) / 2;
//     if (*this < n * pivot) {
//         end = pivot;
//     } else {
//         start = pivot;
//     }
// }
// return start * sign * n.getSign();

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
    return compareSigns(n) == 1 || compareSigns(n) == 3 && compareAbsoluteValues(n) == 1;
}

bool LongInteger::operator<(const LongInteger& n) const
{
    return compareSigns(n) == 2 || compareSigns(n) == 3 && compareAbsoluteValues(n) == 2;
}

bool LongInteger::operator==(const LongInteger& n) const
{
    return compareSigns(n) == 3 && compareAbsoluteValues(n) == 3;
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

bool LongInteger::operator>(const int& n) const
{
    return *this > LongInteger(n);
}

bool LongInteger::operator<(const int& n) const
{
    return *this < LongInteger(n);
}

bool LongInteger::operator==(const int& n) const
{
    return *this == LongInteger(n);
}

bool LongInteger::operator!=(const int& n) const
{
    return *this != LongInteger(n);
}

bool LongInteger::operator>=(const int& n) const
{
    return *this >= LongInteger(n);
}

bool LongInteger::operator<=(const int& n) const
{
    return *this <= LongInteger(n);
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

LongInteger::numberSign LongInteger::getSign() const
{
    return sign;
}

void LongInteger::setSign(numberSign sign)
{
    this->sign = sign;
}

int LongInteger::compareAbsoluteValues(const LongInteger& n) const
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

int LongInteger::compareSigns(const LongInteger& n) const
{
    int flag = 3; // знаки одинаковые
    if (sign > n.getSign()) { //проверка знака
        flag = 1; // если flag == 1, значит первое число положительное и второе число ноль или отрицательное
                  // либо первое число ноль, а второе отрицательное
    } else if (sign < n.getSign()) {
        flag = 2; // если flag == 2, значит первое число ноль или отрицательное и второе число положительное
                  // либо первое число отрицательное, а второе ноль
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

LongInteger LongInteger::subtract(const LongInteger& a, const LongInteger& b) const
{
    const int countDigit = a.getLength() - b.getLength();
    LongInteger foo = a;
    for (int i = 0; i < b.getLength(); ++i) {
        if (countDigit == 0 && i == b.getLength() - 1) {
            foo.getArr()[i] -= b.getArr()[i];
            break;
        }
        foo.getArr()[i + 1]--;
        foo.getArr()[i] += 10 - b.getArr()[i];
        foo.getArr()[i + 1] += foo.getArr()[i] / 10;
        foo.getArr()[i] %= 10;
    }
    foo.reduce();
    return foo;
}

LongInteger LongInteger::add(const LongInteger& a, const LongInteger& b) const
{
    const int length = a.getLength() > b.getLength() ? a.getLength() : b.getLength();
    LongInteger foo = a;
    foo.initialize();
    foo.setLength(length + 1);
    for (int i = 0; i < length; ++i) {
        foo.getArr()[i] += b.getArr()[i];
        foo.getArr()[i + 1] += foo.getArr()[i] / 10;
        foo.getArr()[i] %= 10;
    }
    foo.reduce();
    return foo;
}

int LongInteger::dichotomy(const LongInteger& n) const
{
    const int powerOfTen = this->length - n.getLength() + 1;
    int start = 0;
    int end = pow(10, powerOfTen);
    while (end - start > 1) {
        int pivot = start + (end - start) / 2;
        if (*this < n * pivot) {
            end = pivot;
        } else {
            start = pivot;
        }
    }
    return start;
}

void LongInteger::changeSign()
{
    if (sign == positive) {
        sign = negative;
    } else if (sign == negative) {
        sign = positive;
    }
}

void LongInteger::extractPart(LongInteger& a, LongInteger& b, const LongInteger& c) const
{
    int i = 0;
    for (; i < b.getLength(); ++i) {
        b.getArr()[b.getLength() - i - 1] = a.getArr()[a.getLength() - i - 1];
        a.getArr()[a.getLength() - i - 1] = 0;
    }
    if (b < abs(c)) {
        for (; i > 0; --i) {
            a.getArr()[a.getLength() - i] = b.getArr()[b.getLength() - i];
            b.getArr()[b.getLength() - i] = 0;
        }
        return;
    }
    a.reduce();
}

int LongInteger::divide(LongInteger& a, const LongInteger& b) const
{
    int count = 0;
    if (a.isZero()) {
        return count;
    }
    while (a.compareAbsoluteValues(b) == 1 || a.compareAbsoluteValues(b) == 3) {
        a = a - abs(b);
        count++;
    }
    return count;
}

void LongInteger::returnRemainder(LongInteger& a, LongInteger& b) const
{
    if (a.isZero()) {
        return;
    }
    int i = 0;
    for (; i < a.getLength(); ++i) {
        b.getArr()[b.getLength() + i] = a.getArr()[i];
        a.getArr()[i] = 0;
    }
    b.setLength(b.getLength() + i);
    a.reduce();
}

void LongInteger::reverse()
{
    for (int i = 0; i < length / 2; ++i) {
        std::swap(arr[i], arr[length - i - 1]);
    }
}

LongInteger LongInteger::abs(const LongInteger& n) const
{
    LongInteger foo = n;
    foo.setSign(positive);
    return foo;
}

bool LongInteger::isZero() const
{
    bool flag = true;
    for (int i = 0; i < length; ++i) {
        if (arr[i] != 0) {
            flag = false;
        }
    }
    return flag;
}


std::ostream& operator<<(std::ostream& out, const LongInteger& n)
{
    if (n.getLength() == 0) {
        out << 0;
    }
    if (n.getSign() == LongInteger::negative) {
        out << '-';
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
