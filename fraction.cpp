#include <bits/stdc++.h>

class Fraction {
 private:
  long long numerator;
  long long denominator;

  void reduce() {
    long long gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    if (denominator < 0) {
      numerator = -numerator;
      denominator = -denominator;
    }
  }

 public:
  Fraction(long long num = 0, long long denom = 1)
      : numerator(num), denominator(denom) {
    if (denominator == 0) {
      throw std::invalid_argument("Denominator cannot be zero.");
    }
    reduce();
  }

  friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac.numerator;
    if (frac.denominator != 1) {
      os << "/" << frac.denominator;
    }
    return os;
  }

  Fraction operator+(const Fraction& other) const {
    return Fraction(
        numerator * other.denominator + other.numerator * denominator,
        denominator * other.denominator);
  }

  Fraction operator-(const Fraction& other) const {
    return Fraction(
        numerator * other.denominator - other.numerator * denominator,
        denominator * other.denominator);
  }

  Fraction operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator,
                    denominator * other.denominator);
  }

  Fraction operator/(const Fraction& other) const {
    if (other.numerator == 0) {
      throw std::invalid_argument("Division by zero.");
    }
    return Fraction(numerator * other.denominator,
                    denominator * other.numerator);
  }

  Fraction operator+(long long value) const { return *this + Fraction(value); }

  Fraction operator-(long long value) const { return *this - Fraction(value); }

  Fraction operator*(long long value) const { return *this * Fraction(value); }

  Fraction operator/(long long value) const {
    if (value == 0) {
      throw std::invalid_argument("Division by zero.");
    }
    return *this / Fraction(value);
  }

  Fraction& operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
  }

  Fraction& operator-=(const Fraction& other) {
    *this = *this - other;
    return *this;
  }

  Fraction& operator*=(const Fraction& other) {
    *this = *this * other;
    return *this;
  }

  Fraction& operator/=(const Fraction& other) {
    *this = *this / other;
    return *this;
  }

  long long getNumerator() const { return numerator; }

  long long getDenominator() const { return denominator; }
};

Fraction operator+(long long value, const Fraction& frac) {
  return Fraction(value * frac.getDenominator() + frac.getNumerator(),
                  frac.getDenominator());
}

Fraction operator/(long long value, const Fraction& frac) {
  if (frac.getNumerator() == 0) {
    throw std::invalid_argument("Division by zero.");
  }
  return Fraction(value * frac.getDenominator(), frac.getNumerator());
}

using namespace std;

int main() {
  Fraction a(3, 4);
  cout << 1 / a << endl;
}