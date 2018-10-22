#include "Fraction.h"


Fraction::Fraction(long long numerator, long long denominator)
{
    while (denominator == 0) {
        std::cout << "Данной дроби не существует. Введите новую:\n";
        std::cin >> numerator >> denominator;
    }
    this->numerator = numerator;
    this->denominator = denominator;
    reduceFraction();
}

long long Fraction::getNumerator() const
{
    return numerator;
}

long long Fraction::getDenominator() const
{
    return denominator;
}

Fraction Fraction::add(Fraction fraction)
{
    numerator = numerator * fraction.getDenominator() + fraction.getNumerator() * denominator;
    denominator *= fraction.getDenominator();
    reduceFraction();
    return *this;
}

Fraction Fraction::sub(Fraction fraction)
{
    numerator = numerator * fraction.getDenominator() - fraction.getNumerator() * denominator;
    denominator *= fraction.getDenominator();
    reduceFraction();
    return *this;
}

Fraction Fraction::multiply(Fraction fraction)
{
    numerator *= fraction.getNumerator();
    denominator *= fraction.getDenominator();
    reduceFraction();
    return *this;
}

Fraction Fraction::divide(Fraction fraction)
{
    numerator *= fraction.getDenominator();
    denominator *= fraction.getNumerator();
    reduceFraction();
    return *this;
}

long long Fraction::GCD(long long a, long long b)
{
    if (b == 0) {
        return a;
    }
    return GCD(b, a % b);
}

void Fraction::reduceFraction()
{
    long long gcd = GCD(numerator, denominator);
    if (gcd == 0) {
        gcd = 1;
    } 
    numerator /= gcd;
    denominator /= gcd;
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

std::ostream& operator<<(std::ostream& os, const Fraction &fr)
{
    return os << fr.numerator << "/" << fr.denominator;
}