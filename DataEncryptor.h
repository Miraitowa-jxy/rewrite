#ifndef DATA_ENCRYPTOR_H
#define DATA_ENCRYPTOR_H

#include <vector>
#include <string>
#include "DataAnalyzer.h"

// 简单的加密算法，这里使用凯撒密码作为示例
class DataEncryptor {
public:
    DataEncryptor(const std::vector<DataRecord>& data, int shift);

    // 加密数据
    std::vector<DataRecord> encryptData();

    // 解密数据
    std::vector<DataRecord> decryptData();

private:
    std::vector<DataRecord> data_records;
    int shift_key;
    std::string encryptString(const std::string& str);
    std::string decryptString(const std::string& str);
};

#endif
