#include "DataReader.h"

// 从加密文件中读取数据函数，支持指定加密偏移量（续）
std::vector<DataRecord> DataReader::readDataFromEncryptedFile(const std::string& encrypted_file_path, int offset) {
    std::vector<DataRecord> encrypted_data = readData(encrypted_file_path);
    std::vector<DataRecord> decrypted_data;
    for (const auto& encryptedRecord : encrypted_data) {
        decrypted_data.push_back(decryptRecord(encryptedRecord, offset));
    }
    return decrypted_data;
}

// 读取指定范围行的数据（例如从第 startLine 行到第 endLine 行）
std::vector<DataRecord> DataReader::readDataRange(size_t startLine, size_t endLine) {
    if (startLine > endLine) {
        throw std::runtime_error("起始行号大于结束行号");
    }
    if (startLine > file_line_count || endLine > file_line_count) {
        throw std::runtime_error("指定的行号超出文件总行数");
    }
    return readDataRangeFromFile(startLine, endLine);
}

// 合并读取多个文件的数据（将多个文件的数据合并到一个数据容器中）
std::vector<DataRecord> DataReader::mergeFilesData(const std::vector<std::string>& filePaths) {
    std::vector<DataRecord> mergedData;
    for (const auto& filePath : filePaths) {
        DataReader reader(filePath);
        std::vector<DataRecord> data = reader.readData();
        mergedData.insert(mergedData.end(), data.begin(), data.end());
    }
    return mergedData;
}

// 辅助函数，用于统计文件行数（不包含头部，如果有）
void DataReader::countLines() {
    std::string line;
    size_t count = 0;
    std::ifstream file(file_path);
    if (file.is_open()) {
        if (has_header) {
            std::getline(file, line);  // 跳过头部行
        }
        while (std::getline(file, line)) {
            count++;
        }
    } else {
        throw std::runtime_error("无法打开文件: " + file_path);
    }
    file_line_count = count;
}

// 辅助函数，清洗单个字符串（去除空白、特定特殊字符等）
std::string DataReader::cleanString(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), [](unsigned char c) {
        return std::isspace(c) || c == '\t' || c == '\r' || c == ',' || c == ';' || c == ':' || c == '"';
    }), result.end());
    return result;
}

// 比较函数，用于排序
bool DataReader::compareRecords(const DataRecord& a, const DataRecord& b, const std::string& field) {
    if (field == "data") {
        return a.data < b.data;
    } else if (field == "metadata") {
        return a.metadata < b.metadata;
    } else if (field == "record_id") {
        return a.record_id < b.record_id;
    } else {
        throw std::runtime_error("无效的排序字段: " + field);
    }
}

// 辅助函数，将加密数据转换为原始数据记录
DataRecord DataReader::decryptRecord(const std::string& encryptedRecord, int offset) {
    std::vector<std::string> encryptedTokens = StringUtil::split(encryptedRecord, ',');
    DataRecord record;
    record.record_id = std::stoi(CryptoUtil::decrypt(encryptedTokens[0], offset));
    record.data = CryptoUtil::decrypt(encryptedTokens[1], offset);
    record.metadata = CryptoUtil::decrypt(encryptedTokens[2], offset);
    return record;
}

// 辅助函数，读取单个文件指定范围行的数据
std::vector<DataRecord> DataReader::readDataRangeFromFile(size_t startLine, size_t endLine) {
    std::vector<DataRecord> data_records;
    std::string line;
    size_t current_line = 0;
    std::ifstream file(file_path);
    if (file.is_open()) {
        if (has_header) {
            std::getline(file, line);  // 跳过头部行
        }
        while (std::getline(file, line) && current_line < endLine) {
            current_line++;
            if (current_line >= startLine) {
                std::vector<std::string> tokens = StringUtil::split(line, delimiter[0]);
                DataRecord record;
                record.record_id = current_line;
                if (tokens.size() > 0) {
                    record.data = tokens[0];
                }
                if (tokens.size() > 1) {
                    record.metadata = tokens[1];
                }
                data_records.push_back(record);
            }
        }
    } else {
        throw std::runtime_error("无法打开文件: " + file_path);
    }
    return data_records;
}
