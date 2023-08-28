#include <iostream>
#include <string>
#include <algorithm>

// Function to add two numbers in base B using school method
std::string addInBase(const std::string &num1, const std::string &num2, int B) {
    int carry = 0, i = num1.size() - 1, j = num2.size() - 1;
    std::string result = "";

    // Continue adding digits as long as there are digits in either number or a carry remains
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0'; // Take a digit from num1 if present
        if (j >= 0) sum += num2[j--] - '0'; // Take a digit from num2 if present
        
        carry = sum / B; // calculate the carry for next step
        sum = sum % B;  // keep the remainder as this position's digit

        result += (sum + '0'); // Convert back to string
    }
    
    std::reverse(result.begin(), result.end()); // Reverse the string as we've computed in reverse order
    return result;
}

// Helper function for Karatsuba multiplication
std::string zeroPad(const std::string &num, int zeros) {
    return num + std::string(zeros, '0');
}

// Implementing Karatsuba multiplication
std::string karatsubaMultiply(const std::string &a, const std::string &b, int B) {
    // Base cases
    if (a.size() <= 1 && b.size() <= 1) {
        int result = (a[0] - '0') * (b[0] - '0');
        return std::to_string(result);
    }

    int mid = std::max(a.size(), b.size()) / 2;

    std::string aLow = a.substr(std::max((int)a.size() - mid, 0));
    std::string aHigh = a.substr(0, std::max((int)a.size() - mid, 0));
    std::string bLow = b.substr(std::max((int)b.size() - mid, 0));
    std::string bHigh = b.substr(0, std::max((int)b.size() - mid, 0));

    std::string z0 = karatsubaMultiply(aLow, bLow, B);
    std::string z2 = karatsubaMultiply(aHigh, bHigh, B);
    std::string z1 = addInBase(karatsubaMultiply(addInBase(aLow, aHigh, B), addInBase(bLow, bHigh, B), B), addInBase(z0, z2, B), B);

    // return z2 * B^(2*mid) + z1 * B^mid + z0
    return addInBase(addInBase(zeroPad(z2, 2*mid), zeroPad(z1, mid), B), z0, B);
}

int main() {
    std::string I1, I2;
    int B;
    std::cin >> I1 >> I2 >> B;

    // Compute addition using school method
    std::string sum = addInBase(I1, I2, B);

    // Compute product using Karatsuba method
    std::string product = karatsubaMultiply(I1, I2, B);

    // Since you're an undergraduate, just output 0 for division
    std::string quotient = "0";

    std::cout << sum << " " << product << " " << quotient << std::endl;
    return 0;
}