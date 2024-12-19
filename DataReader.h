#ifndef DATA_READER_H
#define DATA_READER_H

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

// 自定义数据结构示例，比如存储读取的数据行，添加更多字段方便后续处理
struct DataRecord {
    std::string data;
    std::string metadata;
    int record_id;
};

class DataReader {
public:
    DataReader(const std::string& file_path, const std::string& delimiter = ",", bool has_header = false);
    ~DataReader();
    // 读取数据并返回存储数据的容器
    std::vector<DataRecord> readData();
    // 获取文件行数（不包含头部，如果有），用于进度显示等功能
    size_t getFileLineCount();
    // 设置数据编码格式（简单示例，可拓展更多编码处理）
    void setEncoding(const std::string& encoding);
private:
    std::ifstream file_stream;
    boost::regex data_pattern;  // 用于解析数据的正则表达式模式
    std::string delimiter;
    bool has_header;
    std::string encoding;
    size_t file_line_count;
    void countLines();
};

#endif
