#ifndef DATA_PREDICTOR_H
#define DATA_PREDICTOR_H

#include <vector>
#include <string>
#include "DataAnalyzer.h"

// 简单的线性回归预测器
class DataPredictor {
public:
    DataPredictor(const std::vector<DataRecord>& data);

    // 训练模型
    void trainModel();

    // 进行预测
    double predict(double input);

private:
    std::vector<DataRecord> data_records;
    double slope;
    double intercept;
    std::vector<double> extractNumericData();
    void calculateRegression();
};

#endif
