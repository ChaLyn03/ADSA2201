#include <iostream>
#include <string>
#include <algorithm>

std::string addInBase(const std::string &num1, const std::string &num2, int B) {
    int carry = 0, i = num1.size() - 1, j = num2.size() - 1;
    std::string result = "";

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        
        carry = sum / B;
        sum = sum % B;
        result += (sum + '0');
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

std::string zeroPad(const std::string &num, int zeros) {
    return num + std::string(zeros, '0');
}

std::string subtractInBase(const std::string &num1, const std::string &num2, int B) {
    int carry = 0, i = num1.size() - 1, j = num2.size() - 1;
    std::string result = "";

    while (i >= 0 || j >= 0) {
        int diff = (i >= 0 ? num1[i--] - '0' : 0) - (j >= 0 ? num2[j--] - '0' : 0) - carry;

        if (diff < 0) {
            diff += B;
            carry = 1;
        } else {
            carry = 0;
        }

        result += (diff + '0');
    }
    
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back(); 
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::string removeLeadingZeros(const std::string &num) {
    size_t start_idx = 0;
    while (start_idx < num.size() && num[start_idx] == '0') {
        ++start_idx;
    }
    return start_idx < num.size() ? num.substr(start_idx) : "0";
}

std::string karatsubaMultiply(const std::string &a, const std::string &b, int B) {
    if (a.size() <= 1 && b.size() <= 1) {
        int result = (a[0] - '0') * (b[0] - '0');
        return std::to_string(result);
    }

    int mid = (std::max(a.size(), b.size()) + 1) / 2;

    std::string aLow = a.size() >= mid ? a.substr(a.size() - mid) : a;
    std::string aHigh = a.size() > mid ? a.substr(0, a.size() - mid) : "0";
    std::string bLow = b.size() >= mid ? b.substr(b.size() - mid) : b;
    std::string bHigh = b.size() > mid ? b.substr(0, b.size() - mid) : "0";

    std::string z0 = karatsubaMultiply(aLow, bLow, B);
    std::string z2 = karatsubaMultiply(aHigh, bHigh, B);
    std::string aPlusb = removeLeadingZeros(addInBase(aLow, aHigh, B));
    std::string cPlusd = removeLeadingZeros(addInBase(bLow, bHigh, B));
    std::string z1Product = karatsubaMultiply(aPlusb, cPlusd, B);
    std::string z0Plusz2 = removeLeadingZeros(addInBase(z0, z2, B));
    std::string z1 = removeLeadingZeros(subtractInBase(z1Product, z0Plusz2, B));

    return removeLeadingZeros(addInBase(addInBase(zeroPad(z2, 2*mid), zeroPad(z1, mid), B), z0, B));
}

int main() {
    std::string I1, I2;
    int B;
    std::cin >> I1 >> I2 >> B;

    std::string sum = addInBase(I1, I2, B);
    std::string product = karatsubaMultiply(I1, I2, B);
    std::string quotient = "0";

    std::cout << sum << " " << product << " " << quotient << std::endl;
    return 0;
}
