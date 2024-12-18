#include "DataAnalyzer.h"

// 构造函数，接收数据记录容器初始化
DataAnalyzer::DataAnalyzer(const std::vector<DataRecord>& data) : data_records(data) {}

// 计算平均数据长度的函数实现
double DataAnalyzer::calculateAverageDataLength() {
    double total_length = 0;
    for (const auto& record : data_records) {
        total_length += record.data.size();
    }
    return total_length / data_records.size();
}

// 数据过滤函数模板实现
template<typename T>
std::vector<T> DataAnalyzer::filterData(int min_length) {
    std::vector<T> filtered_data;
    for (const auto& record : data_records) {
        if (record.data.size() > min_length) {
            filtered_data.push_back(record);
        }
    }
    return filtered_data;
}

// 注意模板函数的实现要在头文件可见或者显式实例化，这里简单在源文件中包含头文件让其可见
#include "DataAnalyzer.h"
