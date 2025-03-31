#include "DataEncryptor.h"
#include <cctype>

DataEncryptor::DataEncryptor(const std::vector<DataRecord>& data, int shift)
    : data_records(data), shift_key(shift) {}

std::vector<DataRecord> DataEncryptor::encryptData() {
    std::vector<DataRecord> encrypted_data;
    for (const auto& record : data_records) {
        DataRecord encrypted_record = record;
        encrypted_record.data = encryptString(record.data);
        encrypted_record.metadata = encryptString(record.metadata);
        encrypted_data.push_back(encrypted_record);
    }
    return encrypted_data;
}

std::vector<DataRecord> DataEncryptor::decryptData() {
    std::vector<DataRecord> decrypted_data;
    for (const auto& record : data_records) {
        DataRecord decrypted_record = record;
        decrypted_record.data = decryptString(record.data);
        decrypted_record.metadata = decryptString(record.metadata);
        decrypted_data.push_back(decrypted_record);
    }
    return decrypted_data;
}

std::string DataEncryptor::encryptString(const std::string& str) {
    std::string encrypted;
    for (char c : str) {
        if (std::isalpha(c)) {
            char base = std::isupper(c)? 'A' : 'a';
            encrypted += static_cast<char>((c - base + shift_key) % 26 + base);
        } else {
            encrypted += c;
        }
    }
    return encrypted;
}

std::string DataEncryptor::decryptString(const std::string& str) {
    std::string decrypted;
    for (char c : str) {
        if (std::isalpha(c)) {
            char base = std::isupper(c)? 'A' : 'a';
            decrypted += static_cast<char>((c - base - shift_key + 26) % 26 + base);
        } else {
            decrypted += c;
        }
    }
    return decrypted;
}
