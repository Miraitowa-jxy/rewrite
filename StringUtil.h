#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <vector>
#include <sstream>
#include <cctype>

// 自定义字符串工具类，提供一些常用的字符串操作方法
class StringUtil {
public:
    // 分割字符串函数，按照指定分隔符将字符串分割为多个子字符串
    static std::vector<std::string> split(const std::string& str, char delimiter);

    // 去除字符串两端空白字符函数，包括空格、制表符、换行符等
    static std::string trim(const std::string& str);

    // 判断字符串是否为数字函数，支持整数和浮点数的判断
    static bool isNumeric(const std::string& str);

    // 字符串替换函数，将指定子字符串替换为另一个字符串
    static std::string replace(const std::string& str, const std::string& target, const std::string& replacement);

    // 字符串转大写函数
    static std::string toUpper(const std::string& str);

    // 字符串转小写函数
    static std::string toLower(const std::string& str);

    // 判断字符串是否以指定前缀开头
    static bool startsWith(const std::string& str, const std::string& prefix);

    // 判断字符串是否以指定后缀结尾
    static bool endsWith(const std::string& str, const std::string& suffix);
};

#endif
