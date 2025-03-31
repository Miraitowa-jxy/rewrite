#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <vector>
#include <string>
#include "DataAnalyzer.h"

// 定义新的数据结构，用于存储处理后的数据
struct ProcessedData {
    std::vector<std::string> processedStrings;
    std::vector<int> processedIntegers;
    std::vector<double> processedDoubles;
};

class DataProcessor {
public:
    DataProcessor(const std::vector<DataRecord>& data);

    // 对数据进行标准化处理
    ProcessedData standardizeData();

    // 对数据进行离散化处理
    ProcessedData discretizeData(int numBins);

    // 对数据进行文本清理
    ProcessedData cleanTextData();

    // 对数据进行特征提取
    ProcessedData extractFeatures();

private:
    std::vector<DataRecord> data_records;
    std::string removeSpecialCharacters(const std::string& str);
    std::vector<double> extractNumericFeatures(const std::string& str);
    double calculateMean(const std::vector<double>& data);
    double calculateStdDev(const std::vector<double>& data);
};

#endif
