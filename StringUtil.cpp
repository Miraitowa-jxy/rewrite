#include "StringUtil.h"

// 分割字符串函数实现
std::vector<std::string> StringUtil::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// 去除字符串两端空白字符函数实现
std::string StringUtil::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }
    return str.substr(first, (last - first + 1));
}

// 判断字符串是否为数字函数实现
bool StringUtil::isNumeric(const std::string& str) {
    bool hasDot = false;
    for (char c : str) {
        if (!std::isdigit(c)) {
            if (c == '.' &&!hasDot) {
                hasDot = true;
            } else if (c!= '-' && c!= '+') {
                return false;
            }
        }
    }
    return true;
}

// 字符串替换函数实现
std::string StringUtil::replace(const std::string& str, const std::string& target, const std::string& replacement) {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(target, pos))!= std::string::npos) {
        result.replace(pos, target.length(), replacement);
        pos += replacement.length();
    }
    return result;
}

// 字符串转大写函数实现
std::string StringUtil::toUpper(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}

// 字符串转小写函数实现
std::string StringUtil::toLower(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}

// 判断字符串是否以指定前缀开头函数实现
bool StringUtil::startsWith(const std::string& str, const std::string& prefix) {
    return str.substr(0, prefix.length()) == prefix;
}

// 判断字符串是否以指定后缀结尾函数实现
bool StringUtil::endsWith(const std::string& str, const std::string& suffix) {
    return str.substr(str.length() - suffix.length()) == suffix;
}
