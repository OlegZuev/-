#include "LongInteger.h"

LongInteger::LongInteger()
= default;

LongInteger::LongInteger(int n)
{
    if (!isInputCorrect(std::to_string(n))) {
        std::cout << "Ошибка ввода." << std::endl;
        throw 1;
    }
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

LongInteger::LongInteger(std::string& n)
{
    if (!isInputCorrect(n)) {
        std::cout << "Ошибка ввода. Пожалуйста, введите значение заново: ";
        std::cin >> *this;
        return;
    }
    int flag = 0;
    if (n[0] == '-') {
        sign = negative;
        flag++;
    } else if (n[0] != '0') {
        sign = positive;
    }
    length = n.length() - flag;
    for (int i = 0; i < length; ++i) {
        arr[length - i - 1] = n[i + flag] - '0';
    }
    initialize();
}

LongInteger::LongInteger(const char n[])
{
    const int tempLength = strlen(n);
    if (!isInputCorrect(std::string(n, tempLength))) {
        std::cout << "Ошибка ввода." << std::endl;
        throw 1;
    }
    int flag = 0;
    if (n[0] == '-') {
        sign = negative;
        flag++;
    } else if (n[0] != '0') {
        sign = positive;
    }
    length = tempLength - flag;
    for (int i = 0; i < length; ++i) {
        arr[length - i - 1] = n[i + flag] - '0';
    }
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

LongInteger::LongInteger(LongInteger&& n) noexcept : LongInteger()
{
    swap(*this, n);
}

LongInteger::~LongInteger()
{
    delete[] arr;
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

LongInteger& LongInteger::operator=(LongInteger n)
{
    swap(*this, n);
    return *this;
}

void swap(LongInteger& first, LongInteger& second) noexcept
{
    using std::swap;
    swap(first.arr, second.arr);
    swap(first.length, second.length);
    swap(first.sign, second.sign);
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
    LongInteger foo = 0;
    const int length = this->length + n.getLength() + 1;
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
    LongInteger result = 0;
    LongInteger foo = 0;
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
        int tempLength = foo.getLength();
        result.setLength(result.getLength() + 1);
        returnRemainder(foo, copy);
        if (copy.isZero()) {
            break;
        }

        foo.setLength(++tempLength);
        extractPart(copy, foo, n);
        while (foo.isZero()) {
            i++;
            result.getArr()[i] = 0;
            result.setLength(result.getLength() + 1);
            foo.setLength(++tempLength);
            extractPart(copy, foo, n);
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

LongInteger LongInteger::operator%(const LongInteger& n) const
{
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
        divide(foo, n);
        returnRemainder(foo, copy);
        if (copy.isZero()) {
            break;
        }
    }
    return copy;
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
    std::string temp;
    in >> temp;
    n = LongInteger(temp);
    return in;
}

bool LongInteger::isInputCorrect(std::string n)
{
    bool flag = true;
    for (char с : n) {
        if (с - '0' < 0 || с - '0' > 9) {
            flag = false;
            break;
        }
    }
    return flag;
}

void LongInteger::initialize() const
{
    for (int i = length; i < maxSize; ++i) {
        arr[i] = 0;
    }
}

void LongInteger::reduce()
{
    if (arr[length - 1] == 0) {
        length--;
        reduce();
    }
}

void LongInteger::changeSign()
{
    if (sign == positive) {
        sign = negative;
    } else if (sign == negative) {
        sign = positive;
    }
}

void LongInteger::reverse()
{
    for (int i = 0; i < length / 2; ++i) {
        std::swap(arr[i], arr[length - i - 1]);
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

/**
 * Функция сравнивает абсолютное значение длинных чисел.
 * @param n - число, с которым сравнивают
 * @return flag - целое число, которое имеет три значения:
 *         1) 1 - первое число больше второго
 *         2) 2 - первое число меньше второго
 *         3) 3 - числа равны
 */
int LongInteger::compareAbsoluteValues(const LongInteger& n) const
{
    int flag = 3;
    int length = this->length;
    if (this->length > n.getLength()) {
        flag = 1;
    } else if (n.getLength() > this->length) {
        flag = 2;
    } else {
        for (int i = length - 1; i >= 0; --i) {
            if (arr[i] > n.getArr()[i]) {
                flag = 1;
                break;
            }

            if (n.getArr()[i] > arr[i]) {
                flag = 2;
                break;
            }
        }
    }
    return flag;
}

/**
 * Функция сравнивает знаки длинных чисел.
 * @param n - число, с которым сравнивают
 * @return flag - целое число, которое имеет три значения:
 *         1) 1 - знак первого числа "больше" второго
 *         2) 2 - знак первого числа "меньше" второго
 *         3) 3 - знаки чисел равны
 */
int LongInteger::compareSigns(const LongInteger& n) const
{
    int flag = 3;
    if (sign > n.getSign()) {
        flag = 1;
    } else if (sign < n.getSign()) {
        flag = 2;
    }
    return flag;
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

LongInteger LongInteger::add(const LongInteger& a, const LongInteger& b) const
{
    const int length = a.getLength() > b.getLength() ? a.getLength() : b.getLength();
    LongInteger foo = a;
    foo.setLength(length + 1);
    for (int i = 0; i < length; ++i) {
        foo.getArr()[i] += b.getArr()[i];
        foo.getArr()[i + 1] += foo.getArr()[i] / 10;
        foo.getArr()[i] %= 10;
    }
    foo.reduce();
    return foo;
}

LongInteger LongInteger::subtract(const LongInteger& a, const LongInteger& b) const
{
    LongInteger foo = a;
    for (int i = 0; i < b.getLength(); ++i) {
        foo.getArr()[i + 1]--;
        foo.getArr()[i] += 10 - b.getArr()[i];
        foo.getArr()[i + 1] += foo.getArr()[i] / 10;
        foo.getArr()[i] %= 10;
    }
    foo.reduce();
    return foo;
}

LongInteger LongInteger::abs(const LongInteger& n) const
{
    LongInteger foo = n;
    foo.setSign(positive);
    return foo;
}