#include "CryptoUtil.h"

// 简单加密函数实现
std::string CryptoUtil::encrypt(const std::string& data, int offset) {
    std::string encryptedData;
    for (char c : data) {
        encryptedData += static_cast<char>(c + offset);
    }
    return encryptedData;
}

// 简单解密函数实现
std::string CryptoUtil::decrypt(const std::string& encryptedData, int offset) {
    std::string decryptedData;
    for (char c : encryptedData) {
        decryptedData += static_cast<char>(c - offset);
    }
    return decryptedData;
}
