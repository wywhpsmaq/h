#ifndef FRACTION_H
#define FRACTION_H

#include <stdexcept>
#include <string>

class Fraction {
    int numerator;
    int denominator;

    void normalize() {
        if (denominator == 0) { throw std::runtime_error("Denominator cannot be zero"); }

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }

        const int gcd_val = gcd(std::abs(numerator), std::abs(denominator));
        numerator /= gcd_val;
        denominator /= gcd_val;
    }

    static int gcd(int a, int b) {
        while (b != 0) { const int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    static int lcm(const int a, const int b) { return a / gcd(a, b) * b; }

public:
    explicit Fraction(const int num = 0, const int denom = 1) : numerator(num), denominator(denom) { normalize(); }

    // 获取值
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
    double toDouble() const { return static_cast<double>(numerator) / denominator; }

    // 运算符重载
    Fraction operator+(const Fraction &other) const {
        const int lcm_val = lcm(denominator, other.denominator);
        const int new_num = numerator * (lcm_val / denominator) +
                      other.numerator * (lcm_val / other.denominator);
        return Fraction(new_num, lcm_val);
    }

    Fraction operator-(const Fraction &other) const {
        const int lcm_val = lcm(denominator, other.denominator);
        const int new_num = numerator * (lcm_val / denominator) -
                      other.numerator * (lcm_val / other.denominator);
        return Fraction(new_num, lcm_val);
    }

    Fraction operator*(const Fraction &other) const {
        return Fraction(numerator * other.numerator,
                        denominator * other.denominator);
    }

    Fraction operator/(const Fraction &other) const {
        if (other.numerator == 0) { throw std::runtime_error("Division by zero"); }
        return Fraction(numerator * other.denominator,
                        denominator * other.numerator);
    }

    bool operator==(const Fraction &other) const { return numerator == other.numerator && denominator == other.denominator; }

    bool operator!=(const Fraction &other) const { return !(*this == other); }

    // 转换为字符串
    std::string toString() const {
        if (denominator == 1) return std::to_string(numerator);
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }

    // 从字符串解析
    static Fraction fromString(const std::string &str) {
        const size_t slash_pos = str.find('/');
        if (slash_pos == std::string::npos) { return Fraction(std::stoi(str), 1); }
        const int num = std::stoi(str.substr(0, slash_pos));
        const int denom = std::stoi(str.substr(slash_pos + 1));
        return Fraction(num, denom);
    }
};

#endif // FRACTION_H
