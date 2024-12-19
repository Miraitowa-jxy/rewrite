#include "DataAnalyzer.h"

// 构造函数，接收数据记录容器初始化
DataAnalyzer::DataAnalyzer(const std::vector<DataRecord>& data) : data_records(data) {}

// 计算多个统计指标的函数实现，返回指标的映射表
std::map<std::string, double> DataAnalyzer::calculateStatistics() {
    std::map<std::string, double> statistics;
    double total_length = 0;
    std::map<std::string, int> metadata_count;
    for (const auto& record : data_records) {
        total_length += record.data.size();
        metadata_count[record.metadata]++;
    }
    statistics["average_length"] = total_length / data_records.size();
    for (const auto& pair : metadata_count) {
        statistics["frequency_" + pair.first] = static_cast<double>(pair.second) / data_records.size();
    }
    return statistics;
}

// 相关性分析函数实现，计算数据的相关性矩阵
Eigen::MatrixXd DataAnalyzer::calculateCorrelationMatrix() {
    Eigen::MatrixXd matrix = convertToMatrix();
    return matrix.transpose() * matrix / (matrix.rows() - 1);
}

// 数据过滤函数模板实现，增加了根据元数据过滤的功能
template<typename T>
std::vector<T> DataAnalyzer::filterData(int min_length, const std::string& filter_metadata) {
    std::vector<T> filtered_data;
    for (const auto& record : data_records) {
        if (record.data.size() > min_length && (filter_metadata.empty() || record.metadata == filter_metadata)) {
            filtered_data.push_back(record);
        }
    }
    return filtered_data;
}

// 辅助函数，将数据记录转换为数值向量（简单示例，可根据实际情况拓展）
Eigen::MatrixXd DataAnalyzer::convertToMatrix() {
    Eigen::MatrixXd matrix(data_records.size(), 1);
    for (size_t i = 0; i < data_records.size(); ++i) {
        // 简单假设数据可以转换为整数，实际可能需要更复杂的转换逻辑
        matrix(i, 0) = std::stoi(data_records[i].data);
    }
    return matrix;
}

// 注意模板函数的实现要在头文件可见或者显式实例化，这里简单在源文件中包含头文件让其可见
#include "DataAnalyzer.h"
