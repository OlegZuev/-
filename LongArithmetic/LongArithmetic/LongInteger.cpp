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
}

LongInteger LongInteger::operator+(LongInteger n)
{
    const int length = this->length > n.getLength() ? this->length : n.getLength();
    for (int i = 0; i < length; ++i) {
        arr[i] += n.getArr()[i];
        arr[i + 1] += n.getArr()[i] / 10;
        arr[i] %= 10;
    }
    reduce(*this);
    return *this;
}

LongInteger LongInteger::operator-(LongInteger n)
{
    if (*this > n || *this == n) {
        return subtract(*this, n);
    }
    LongInteger l = subtract(n, *this);
    l.getArr()[length - 1] *= -1;
    return l;
}

LongInteger LongInteger::operator*(LongInteger n)
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
    reduce(l);
    return l;
}

LongInteger LongInteger::operator/(LongInteger n)
{
    int count = 0;
    while (*this > n) {
        *this = *this - n;
        count++;
    }
    return LongInteger(count);
}

LongInteger LongInteger::operator%(LongInteger n)
{
    while (*this > n) {
        *this = *this - n;
    }
    return *this;
}

bool LongInteger::operator>(LongInteger n)
{
    return sign(n) == 1;
}

bool LongInteger::operator<(LongInteger n)
{
    return sign(n) == 2;
}

bool LongInteger::operator==(LongInteger n)
{
    return sign(n) == 3;
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

int LongInteger::sign(LongInteger n)
{
    int flag = 3; // ���� flag == 3, ������ ����� ���������� ������
    int length = this->length;
    if (this->length > n.getLength()) {
        flag = 1; // ���� flag == 1, ������ ������ ����� ������� �������
    } else if (n.getLength() > this->length) {
        flag = 2; // ���� flag == 2, ������ ������ ����� ������� �������
    } else {// ���� ����� ���������� ������, �� ���������� �������� �� ���
        for (int i = length - 1; i >= 0; --i) { // ����������� ��������� ���� �����
            if (arr[i] > n.getArr()[i]) // ���� ������ ������� ����� ������
            {
                flag = 1; // ������ ������ ����� ������� �������
                break; // ����� �� ����� for
            }

            if (n.getArr()[i] > arr[i]) // ���� ������ ������� ����� ������
            {
                flag = 2; // ������ ������ ����� ������� �������
                break; // ����� �� ����� for
            }
        }
    }
    return flag;
}

void LongInteger::reduce(LongInteger& n)
{
    if (n.getArr()[n.getLength() - 1] == 0) {
        n.setLength(n.getLength() - 1);
        reduce(n);
    }
}

LongInteger LongInteger::subtract(LongInteger a, LongInteger b)
{
    int countDigit = a.getLength() - b.getLength();
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
    reduce(a);
    return a;
}

std::ostream& operator<<(std::ostream& out, LongInteger& n)
{
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
