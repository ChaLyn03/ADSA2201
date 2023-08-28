#include <iostream>
#include <string>
#include <algorithm>

// Helper function to add two numbers in base B using school method
std::string addInBase(const std::string &num1, const std::string &num2, int B) {
    int carry = 0;
    ssize_t i = num1.size() - 1, j = num2.size() - 1;
    std::string result = "";

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry + (i >= 0 ? num1[i--] - '0' : 0) + (j >= 0 ? num2[j--] - '0' : 0);
        
        carry = sum / B;
        sum %= B;

        result += (sum + '0');
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Helper function to pad zeros to a number
std::string zeroPad(const std::string &num, size_t zeros) {
    return num + std::string(zeros, '0');
}

// Implementing Karatsuba multiplication
std::string karatsubaMultiply(const std::string &a, const std::string &b, int B) {
    if (a.size() == 1 || b.size() == 1) {
    int result = (a[0] - '0') * (b[0] - '0');
    if (result < B) {
        return std::to_string(result);
    } else {
        return std::to_string(result / B) + std::to_string(result % B);
    }
    }

    size_t mid = (std::max(a.size(), b.size()) + 1) / 2;

    std::string aLow = a.size() >= mid ? a.substr(a.size() - mid) : a;
    std::string aHigh = a.size() > mid ? a.substr(0, a.size() - mid) : "0";
    std::string bLow = b.size() >= mid ? b.substr(b.size() - mid) : b;
    std::string bHigh = b.size() > mid ? b.substr(0, b.size() - mid) : "0";

    std::string z0 = karatsubaMultiply(aLow, bLow, B);
    std::string z2 = karatsubaMultiply(aHigh, bHigh, B);
    std::string aPlusb = addInBase(aLow, aHigh, B);
    std::string cPlusd = addInBase(bLow, bHigh, B);
    std::string z1Product = karatsubaMultiply(aPlusb, cPlusd, B);
    std::string z0Plusz2 = addInBase(z0, z2, B);
    
    std::string z1 = addInBase(z1Product, "-" + z0Plusz2, B); // Using subtraction logic for signed integers

    return addInBase(addInBase(zeroPad(z2, 2*mid), zeroPad(z1, mid), B), z0, B);
}

int main() {
    std::string I1, I2;
    int B;
    std::cin >> I1 >> I2 >> B;

    std::string sum = addInBase(I1, I2, B);
    std::string product = karatsubaMultiply(I1, I2, B);

    std::string quotient = "0";  // Hardcoded division for undergraduate students

    std::cout << sum << " " << product << " " << quotient << std::endl;
    return 0;
}
