#include "DataProcessor.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cctype>
#include <sstream>

DataProcessor::DataProcessor(const std::vector<DataRecord>& data) : data_records(data) {}

ProcessedData DataProcessor::standardizeData() {
    ProcessedData result;
    std::vector<double> numericData;
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            numericData.push_back(std::stod(record.data));
        }
    }
    double mean = calculateMean(numericData);
    double stdDev = calculateStdDev(numericData);
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            double value = std::stod(record.data);
            double standardized = (value - mean) / stdDev;
            result.processedDoubles.push_back(standardized);
        } else {
            result.processedStrings.push_back(record.data);
        }
    }
    return result;
}

ProcessedData DataProcessor::discretizeData(int numBins) {
    ProcessedData result;
    std::vector<double> numericData;
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            numericData.push_back(std::stod(record.data));
        }
    }
    if (numericData.empty()) {
        return result;
    }
    double minVal = *std::min_element(numericData.begin(), numericData.end());
    double maxVal = *std::max_element(numericData.begin(), numericData.end());
    double binSize = (maxVal - minVal) / numBins;
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            double value = std::stod(record.data);
            int binIndex = static_cast<int>((value - minVal) / binSize);
            if (binIndex >= numBins) {
                binIndex = numBins - 1;
            }
            result.processedIntegers.push_back(binIndex);
        } else {
            result.processedStrings.push_back(record.data);
        }
    }
    return result;
}

ProcessedData DataProcessor::cleanTextData() {
    ProcessedData result;
    for (const auto& record : data_records) {
        std::string cleaned = removeSpecialCharacters(record.data);
        result.processedStrings.push_back(cleaned);
    }
    return result;
}

ProcessedData DataProcessor::extractFeatures() {
    ProcessedData result;
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            std::vector<double> features = extractNumericFeatures(record.data);
            result.processedDoubles.insert(result.processedDoubles.end(), features.begin(), features.end());
        } else {
            std::string cleaned = removeSpecialCharacters(record.data);
            std::vector<double> features = extractNumericFeatures(cleaned);
            result.processedDoubles.insert(result.processedDoubles.end(), features.begin(), features.end());
        }
    }
    return result;
}

std::string DataProcessor::removeSpecialCharacters(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (std::isalnum(c) || std::isspace(c)) {
            result += c;
        }
    }
    return result;
}

std::vector<double> DataProcessor::extractNumericFeatures(const std::string& str) {
    std::vector<double> features;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token) {
        if (StringUtil::isNumeric(token)) {
            features.push_back(std::stod(token));
        }
    }
    return features;
}

double DataProcessor::calculateMean(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double DataProcessor::calculateStdDev(const std::vector<double>& data) {
    double mean = calculateMean(data);
    double sumSquaredDiff = 0.0;
    for (const double& value : data) {
        double diff = value - mean;
        sumSquaredDiff += diff * diff;
    }
    return std::sqrt(sumSquaredDiff / (data.size() - 1));
}
