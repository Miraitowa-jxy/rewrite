#include "DataReader.h"

// 构造函数，打开文件流并初始化正则表达式模式、分隔符等相关属性（这里简单示例，可根据实际数据格式调整）
DataReader::DataReader(const std::string& file_path, const std::string& delimiter, bool has_header)
    : file_stream(file_path), delimiter(delimiter), has_header(has_header), encoding("utf-8"), file_line_count(0) {
    if (!boost::filesystem::exists(file_path)) {
        throw std::runtime_error("文件不存在: " + file_path);
    }
    if (!file_stream.is_open()) {
        throw std::runtime_error("无法打开文件: " + file_path);
    }
    data_pattern = boost::regex("([^" + delimiter + "]+)");
    countLines();
}

DataReader::~DataReader() {
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

// 读取数据的函数实现，添加了更多数据解析和处理逻辑
std::vector<DataRecord> DataReader::readData() {
    std::vector<DataRecord> data_records;
    std::string line;
    size_t current_line = 0;
    if (has_header) {
        std::getline(file_stream, line);  // 跳过头部行
    }
    while (std::getline(file_stream, line)) {
        current_line++;
        boost::sregex_token_iterator it(line.begin(), line.end(), data_pattern, -1);
        boost::sregex_token_iterator end;
        DataRecord record;
        record.record_id = current_line;
        if (it!= end) {
            record.data = *it++;
            if (it!= end) {
                record.metadata = *it;
            }
        }
        data_records.push_back(record);
    }
    return data_records;
}

// 获取文件行数（不包含头部，如果有）的函数实现
size_t DataReader::getFileLineCount() {
    return file_line_count;
}

// 设置数据编码格式（简单示例，目前仅做了简单赋值，可拓展更多编码转换逻辑）
void DataReader::setEncoding(const std::string& encoding) {
    this->encoding = encoding;
}

// 辅助函数，用于统计文件行数（不包含头部，如果有）
void DataReader::countLines() {
    std::string line;
    size_t count = 0;
    if (has_header) {
        std::getline(file_stream, line);  // 跳过头部行
    }
    while (std::getline(file_stream, line)) {
        count++;
    }
    file_line_count = count;
    file_stream.clear();
    file_stream.seekg(0, std::ios::beg);
}
