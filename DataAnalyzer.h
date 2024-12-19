#ifndef DATA_ANALYZER_H
#define DATA_ANALYZER_H

#include <vector>
#include <Eigen/Dense>
#include <map>
#include "DataReader.h"

class DataAnalyzer {
public:
    DataAnalyzer(const std::vector<DataRecord>& data);
    // 统计分析函数示例，比如计算数据长度平均值、数据出现频率等多个统计指标
    std::map<std::string, double> calculateStatistics();
    // 相关性分析函数示例，假设数据可以转换为数值向量进行相关性计算
    Eigen::MatrixXd calculateCorrelationMatrix();
    // 数据过滤函数模板示例，这里简单过滤长度大于某个值的数据，新增更多过滤条件选项
    template<typename T>
    std::vector<T> filterData(int min_length, const std::string& filter_metadata = "");
private:
    std::vector<DataRecord> data_records;
    // 辅助函数，将数据记录转换为数值向量（简单示例，可根据实际情况拓展）
    Eigen::MatrixXd convertToMatrix();
};

#endif
