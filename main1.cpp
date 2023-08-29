#include <iostream>
#include <string>
#include <algorithm>

// Utility function to make two strings of equal length by adding leading zeros
std::string makeEqualLength(std::string str, int length) {
    while (str.length() < length) {
        str = '0' + str;
    }
    return str;
}

// School Method for Integer Addition
std::string add(const std::string &a, const std::string &b, int base) {
    int length = std::max(a.size(), b.size());
    std::string result = "";
    std::string num1 = makeEqualLength(a, length);
    std::string num2 = makeEqualLength(b, length);

    int carry = 0;
    for (int i = length - 1; i >= 0; i--) {
        int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
        result += (sum % base) + '0';
        carry = sum / base;
    }
    if (carry) {
        result += carry + '0';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// Helper function to multiply a single digit
std::string multiplySingleDigit(const std::string &a, const char &b, int base) {
    std::string result = "";
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int prod = (a[i] - '0') * (b - '0') + carry;
        result += (prod % base) + '0';
        carry = prod / base;
    }
    if (carry) {
        result += carry + '0';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// Karatsuba Algorithm for Integer Multiplication
std::string karatsuba(const std::string &a, const std::string &b, int base) {
    int length = std::max(a.size(), b.size());
    if (length <= 1) {
        return std::to_string((a[0] - '0') * (b[0] - '0'));
    }
    std::string a1 = a.substr(0, length / 2);
    std::string a0 = a.substr(length / 2, length - length / 2);
    std::string b1 = b.substr(0, length / 2);
    std::string b0 = b.substr(length / 2, length - length / 2);

    std::string p0 = karatsuba(a0, b0, base);
    std::string p2 = karatsuba(a1, b1, base);
    std::string p1 = karatsuba(add(a0, a1, base), add(b0, b1, base), base);
    p1 = add(p1, "-" + p0, base);
    p1 = add(p1, "-" + p2, base);

    for (int i = 0; i < 2 * (length - length / 2); i++) {
        p2 += '0';
    }
    for (int i = 0; i < length - length / 2; i++) {
        p1 += '0';
    }

    std::string result = add(p2, add(p1, p0, base), base);
    return result;
}

// Integer Division
std::string integerDivision(const std::string &a, const std::string &b, int base) {
    // Division by subtraction (naive approach)
    // This can be optimized further.
    std::string quotient = "0";
    std::string dividend = a;

    while (dividend >= b) {
        dividend = add(dividend, "-" + b, base);
        quotient = add(quotient, "1", base);
    }

    return quotient;
}

int main() {
    std::string I1, I2;
    int B;
    std::cin >> I1 >> I2 >> B;

    std::cout << add(I1, I2, B) << " ";
    std::cout << karatsuba(I1, I2, B) << " ";

    // If undergraduate, use the line below instead
    // std::cout << "0";
    std::cout << std::endl;

    return 0;
}
