#include <iostream>

int count_mM() {
    std::string str;
    std::cin >> str;
    int count = 0;
    for (char c : str) {
        if (c == 'm' || c == 'M') {
            ++count;
        }
    }
    return count;
}

std::string repeater() {
    int n;
    std::cin >> n;
    std::string str;
    std::cin >> str;
    if (n < 0) {
        return "hiba";
    }

    std::string result;
    for (int i = 0; i < n; ++i) {
        result += str;
    }
    return result;
}

std::string multiplier(unsigned n) {
    std::string result = std::to_string(n * 3);
    return result;
}

int strmin(const std::string& str1, const std::string& str2) {
    bool isDigit1 = true;
    bool isDigit2 = true;
    int i1 = 0;
    int i2 = 0;

    try {
        i1 = std::stoi(str1);
    } catch (std::invalid_argument& e) {
        isDigit1 = false;
    }

    try {
        i2 = std::stoi(str2);
    } catch (std::invalid_argument& e) {
        isDigit2 = false;
    }

    if (isDigit1 && isDigit2) {
        return std::min(i1, i2);
    } else if (isDigit1) {
        return i1;
    } else if (isDigit2) {
        return i2;
    } else {
        return -999;
    }
}
