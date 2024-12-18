#ifndef DATA_READER_H
#define DATA_READER_H

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <boost/regex.hpp>

// 自定义数据结构示例，比如存储读取的数据行
struct DataRecord {
    std::string data;
};

class DataReader {
public:
    DataReader(const std::string& file_path);
    ~DataReader();
    // 读取数据并返回存储数据的容器
    std::vector<DataRecord> readData();
private:
    std::ifstream file_stream;
    boost::regex data_pattern;  // 用于解析数据的正则表达式模式
};

#endif
