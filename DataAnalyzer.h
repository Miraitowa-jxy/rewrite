#ifndef DATA_ANALYZER_H
#define DATA_ANALYZER_H

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>
#include <numeric>
#include "DataReader.h"

class DataAnalyzer {
public:
    DataAnalyzer(const std::vector<DataRecord>& data);
    // 统计分析函数示例，比如计算数据长度平均值、数据出现频率等多个统计指标，新增更多指标计算
    std::map<std::string, double> calculateStatistics();
    // 相关性分析函数示例，假设数据可以转换为数值向量进行相关性计算，改进算法提高效率
    std::vector<std::vector<double>> calculateCorrelationMatrix();
    // 数据过滤函数模板示例，这里简单过滤长度大于某个值的数据，新增更多过滤条件选项，更灵活的过滤逻辑
    template<typename T>
    std::vector<T> filterData(int min_length, const std::string& filter_metadata = "", bool filter_outliers = false, const std::string& custom_filter = "");
    // 数据分组分析函数，根据指定字段进行分组并计算每组的统计信息（简单示例），支持更多统计指标和分组方式
    std::map<std::string, std::map<std::string, double>> groupBy(const std::string& field, const std::vector<std::string>& statistics_fields);
    // 异常值检测函数，使用简单的统计方法（如 3 倍标准差法）检测异常值（简单示例），可切换不同检测方法
    std::vector<DataRecord> detectOutliers(const std::string& method = "3_sigma");
    // 数据合并函数，将两个数据集按指定规则合并（简单示例，假设按记录 ID 合并），处理更多合并冲突情况
    std::vector<DataRecord> mergeData(const std::vector<DataRecord>& other_data, const std::string& merge_strategy = "id_based");
    // 复杂数据查询函数，根据多个条件查询数据（简单示例），支持更复杂的查询表达式和逻辑运算
    std::vector<DataRecord> queryData(const std::vector<std::string>& conditions);
    // 数据可视化建议函数，根据数据特征给出适合的可视化方式建议
    std::vector<std::string> suggestVisualization();
    // 时间序列分析函数（简单示例，假设数据包含时间相关字段），可进行趋势分析、周期性分析等
    void timeSeriesAnalysis(const std::string& time_field);
private:
    std::vector<DataRecord> data_records;
    // 辅助函数，将数据记录转换为数值向量（简单示例，可根据实际情况拓展）
    std::vector<std::vector<double>> convertToMatrix();
    // 辅助函数，计算均值
    double calculateMean(const std::vector<double>& data);
    // 辅助函数，计算标准差
    double calculateStdDev(const std::vector<double>& data);
    // 辅助函数，合并数据的具体实现，根据不同合并策略处理
    void mergeDataInternal(const std::vector<DataRecord>& other_data, const std::string& merge_strategy, std::map<int, DataRecord>& merged_map);
    // 辅助函数，执行数据查询的具体逻辑，解析复杂查询条件
    bool evaluateCondition(const std::string& condition);
    // 辅助函数，判断数据是否为时间序列数据（简单根据字段名判断，可完善）
    bool isTimeSeriesData(const std::string& field);
    // 辅助函数，进行时间序列趋势分析（简单示例，可采用更专业算法）
    void timeSeriesTrendAnalysis(const std::string& time_field);
    // 辅助函数，进行时间序列周期性分析（简单示例，可采用更专业算法）
    void timeSeriesPeriodicityAnalysis(const std::string& time_field);
};

#endif
