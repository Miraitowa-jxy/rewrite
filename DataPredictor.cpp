#include "DataPredictor.h"
#include <algorithm>
#include <numeric>

DataPredictor::DataPredictor(const std::vector<DataRecord>& data)
    : data_records(data), slope(0), intercept(0) {}

void DataPredictor::trainModel() {
    calculateRegression();
}

double DataPredictor::predict(double input) {
    return slope * input + intercept;
}

std::vector<double> DataPredictor::extractNumericData() {
    std::vector<double> numericData;
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            numericData.push_back(std::stod(record.data));
        }
    }
    return numericData;
}

void DataPredictor::calculateRegression() {
    std::vector<double> x;
    std::vector<double> y;
    for (size_t i = 0; i < data_records.size(); ++i) {
        if (StringUtil::isNumeric(data_records[i].data)) {
            x.push_back(i);
            y.push_back(std::stod(data_records[i].data));
        }
    }
    if (x.empty() || y.empty()) {
        return;
    }
    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
    double sum_xy = 0.0;
    double sum_x2 = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }
    double n = x.size();
    slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    intercept = (sum_y - slope * sum_x) / n;
}
