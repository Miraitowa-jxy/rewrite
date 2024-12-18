#ifndef DATA_ANALYZER_H
#define DATA_ANALYZER_H

#include <vector>
#include <Eigen/Dense>
#include "DataReader.h"

class DataAnalyzer {
public:
    DataAnalyzer(const std::vector<DataRecord>& data);
    // 统计分析函数示例，比如计算数据长度平均值
    double calculateAverageDataLength();
    // 数据过滤函数模板示例，这里简单过滤长度大于某个值的数据
    template<typename T>
    std::vector<T> filterData(int min_length);
private:
    std::vector<DataRecord> data_records;
};

#endif
