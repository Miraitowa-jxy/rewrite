#include <omp.h>
#include "DataReader.h"

// 构造函数，打开文件流并初始化正则表达式模式（这里简单示例，可根据实际数据格式调整）
DataReader::DataReader(const std::string& file_path) : file_stream(file_path), data_pattern("(.*)") {}

DataReader::~DataReader() {
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

// 读取数据的函数实现，加入多线程优化
std::vector<DataRecord> DataReader::readData() {
    std::vector<DataRecord> data_records;
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file_stream, line)) {
        lines.push_back(line);
    }

    // 使用OpenMP并行区域划分任务读取数据
    #pragma omp parallel for
    for (size_t i = 0; i < lines.size(); ++i) {
        boost::smatch match;
        if (boost::regex_match(lines[i], match, data_pattern)) {
            DataRecord record;
            record.data = match[1];
            #pragma omp critical
            data_records.push_back(record);
        }
    }

    return data_records;
}
