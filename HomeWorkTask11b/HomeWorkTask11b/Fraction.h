#pragma once
#include <ostream>

class Fraction {
    private:
        long long GCD(long long a, long long b);
        void reduceFraction();
        long long numerator;
        long long denominator;

    public:
        Fraction(long long numerator, long long denominator);
        long long getNumerator() const;
        long long getDenominator() const;
        Fraction add(Fraction fraction);
        Fraction sub(Fraction fraction);
        Fraction multiply(Fraction fraction);
        Fraction divide(Fraction fraction);
        friend std::ostream& operator<<(std::ostream& os, const Fraction& fr);
};
