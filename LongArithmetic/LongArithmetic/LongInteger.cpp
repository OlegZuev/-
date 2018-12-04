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

LongInteger::LongInteger(LongInteger&& n) noexcept
    : LongInteger()
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

/**
 * Функция переопределяет оператор присваивания для LongInteger. Основан на идее copy-and-swap idiom.
 * @param n длинное число
 * @return *this, значение которого обменялось с n
 */
LongInteger& LongInteger::operator=(LongInteger n)
{
    swap(*this, n);
    return *this;
}

/**
 * Процедура обменивает внутренние значения двух переменных типа LongInteger
 * @param first первое длинное число
 * @param second второе длинное число
 */
void swap(LongInteger& first, LongInteger& second) noexcept
{
    using std::swap;
    swap(first.arr, second.arr);
    swap(first.length, second.length);
    swap(first.sign, second.sign);
}

/**
 * Функция для сложения длинных чисел. В зависимости от знака переменных вызывает subtract или add
 * и возвращает результат этих функций как ответ
 * @param n длинное число
 * @return вызов функции subtract, если значения разных знаков
 * @return вызов функции add, если значения одинаковых знаков
 */
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

/**
 * Функция для вычитания длинных чисел. В зависимости от знака переменных вызывает subtract или add
 * и возвращает результат этих функций как ответ
 * @param n длинное число
 * @return вызов функции subtract, если значения одинаковых знаков
 * @return вызов функции add, если значения разных знаков
 */
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

/**
 * Функция для умножения длинных чисел. Реализовано обычное умножение столбиком
 * @param n длинное число
 * @return произведение *this на n
 */
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
    if (foo.isZero()) {
        foo.setSign(zero);
    }
    return foo;
}

/**
 * Функция для деления длинных чисел. Реализовано сложное деление столбиком нацело
 * @param n длинное число
 * @return частное *this и n
 */
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

/**
 * Функция для взятия остатка от длинного числа. Реализация вытекает из сложного деления столбиком
 * @param n длинное число
 * @return остаток при делении *this на n
 */
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
    if (copy.isZero()) {
        copy.setSign(zero);
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

/**
 * Функция для вывода длинных чисел. Посимвольно выводит цифры длинного числа.
 * @param out поток вывода
 * @param n длинное число, которое выводится
 * @return изменённый поток вывода
 */
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

/**
 * Функция для ввода длинных чисел. Вводится значение как строка, которая передаётся в конструктор
 * длинных чисел. После чего новое длинное число присваивается n
 * @param in поток ввода
 * @param n длинное число, которому присваивается значение
 * @return изменённый поток ввода
 */
std::istream& operator>>(std::istream& in, LongInteger& n)
{
    std::string temp;
    in >> temp;
    n = LongInteger(temp);
    return in;
}

/**
 * Функция проверяет корректность входных данных.
 * @param n длинное число в виде строки для избежания переполнения
 * @return flag - является ли число корректным
 */
bool LongInteger::isInputCorrect(std::string n) const
{
    bool flag = true;
    int i = 0;
    if (n[0] == '-') {
        i++;
        if (i == n.length()) {
            flag = false;
        }
    }
    for (; i < n.length(); ++i) {
        if (n[i] - '0' < 0 || n[i] - '0' > 9) {
            flag = false;
            break;
        }
    }
    return flag;
}

/**
 * Процедура для инициализации пустых значений внутреннего массива цифр arr нулями
 */
void LongInteger::initialize() const
{
    for (int i = length; i < maxSize; ++i) {
        arr[i] = 0;
    }
}

/**
 * Процедура для сокращения length числа из нулевых значений
 */
void LongInteger::reduce()
{
    if (arr[length - 1] == 0) {
        length--;
        reduce();
    }
}

/**
 * Процедура для смены знака числа на противоположный
 */
void LongInteger::changeSign()
{
    if (sign == positive) {
        sign = negative;
    } else if (sign == negative) {
        sign = positive;
    }
}

/**
 * Процедура, которая переворачивает длинное число
 */
void LongInteger::reverse()
{
    for (int i = 0; i < length / 2; ++i) {
        std::swap(arr[i], arr[length - i - 1]);
    }
}

/**
 * Процедура для извлечения части длинного числа в другое длинное число.
 * С условием, что полученное число больше третьего
 * @param a длинное число, из которого извлекаем часть
 * @param b длинное число, в которое извлекается часть
 * @param c длинное число, с которым сравнивается b
 */
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

/**
 * Процедура для извлечения(возвращения) части длинного числа в другое длинное число.
 * @param a длинное число, из которого извлекаем часть
 * @param b длинное число, в которое извлекается часть
 */
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

/**
 * Функция проверяет значения числа на ноль
 * @return flag - является ли число нулём
 */
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
 * @return 1) 1 - первое число больше второго
 * @return 2) 2 - первое число меньше второго
 * @return 3) 3 - числа равны
 */
int LongInteger::compareAbsoluteValues(const LongInteger& n) const
{
    int flag = 3;
    const int length = this->length;
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
 * @return 1) 1 - знак первого числа "больше" второго
 * @return 2) 2 - знак первого числа "меньше" второго
 * @return 3) 3 - знаки чисел равны
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

/**
 * Приватная функция для сложения двух длинных чисел.
 * Реализована основная логика через сложение столбиком.
 * @param a первое длинное число 
 * @param b второе длинное число
 * @return результат сложения двух чисел 
 */
LongInteger LongInteger::add(const LongInteger& a, const LongInteger& b) const
{
    const int length = a.getLength() > b.getLength() ? a.getLength() : b.getLength();
    LongInteger foo = a;
    if (foo.getSign() == zero && b.getSign() != zero) {
        foo.setSign(b.getSign());
    }
    foo.setLength(length + 1);
    for (int i = 0; i < length; ++i) {
        foo.getArr()[i] += b.getArr()[i];
        foo.getArr()[i + 1] += foo.getArr()[i] / 10;
        foo.getArr()[i] %= 10;
    }
    foo.reduce();
    return foo;
}

/**
 * Приватная функция для вычитания двух длинных чисел.
 * Реализована основная логика через вычитание столбиком.
 * @param a первое длинное число 
 * @param b второе длинное число
 * @return результат вычитания двух чисел 
 */
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

/**
 * Функция возвращает абсолютное значение числа
 * @param n длинное число
 * @return абсолютное значение числа
 */
LongInteger LongInteger::abs(const LongInteger& n) const
{
    LongInteger foo = n;
    if (foo.isZero()) {
        foo.setSign(zero);
    } else {
        foo.setSign(positive);    
    }
    return foo;
}