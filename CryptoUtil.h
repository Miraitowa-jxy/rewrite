#ifndef CRYPTO_UTIL_H
#define CRYPTO_UTIL_H

#include <string>

// 数据加密解密工具类，提供简单的加密和解密方法示例（可进一步完善加密算法）
class CryptoUtil {
public:
    // 简单加密函数，将每个字符的 ASCII 码按照指定偏移量进行加密
    static std::string encrypt(const std::string& data, int offset = 1);

    // 简单解密函数，将加密后的字符的 ASCII 码按照指定偏移量进行解密
    static std::string decrypt(const std::string& encryptedData, int offset = 1);
};

#endif
