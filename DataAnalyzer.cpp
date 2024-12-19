#include "DataAnalyzer.h"

// 构造函数，接收数据记录容器初始化
DataAnalyzer::DataAnalyzer(const std::vector<DataRecord>& data) : data_records(data) {}

// 计算多个统计指标的函数实现，返回指标的映射表，新增更多指标计算逻辑
std::map<std::string, double> DataAnalyzer::calculateStatistics() {
    std::map<std::string, double> statistics;
    double total_length = 0;
    std::map<std::string, int> metadata_count;
    std::vector<double> data_lengths;
    std::vector<int> record_ids;
    for (const auto& record : data_records) {
        total_length += record.data.size();
        metadata_count[record.metadata]++;
        data_lengths.push_back(record.data.size());
        record_ids.push_back(record.record_id);
    }
    statistics["average_length"] = total_length / data_records.size();
    statistics["min_length"] = *std::min_element(data_lengths.begin(), data_lengths.end());
    statistics["max_length"] = *std::max_element(data_lengths.end() - 1, data_lengths.end());
    statistics["median_length"] = 0;  // 待实现计算中位数逻辑
    for (const auto& pair : metadata_count) {
        statistics["frequency_" + pair.first] = static_cast<double>(pair.second) / data_records.size();
    }
    statistics["average_record_id"] = std::accumulate(record_ids.begin(), record_ids.end(), 0.0) / record_ids.size();
    return statistics;
}

// 相关性分析函数实现，计算数据的相关性矩阵，改进算法提高效率
std::vector<std::vector<double>> DataAnalyzer::calculateCorrelationMatrix() {
    std::vector<std::vector<double>> matrix = convertToMatrix();
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();
    std::vector<std::vector<double>> correlation_matrix(rows, std::vector<double>(cols, 0.0));
    // 使用更高效的算法，比如先计算均值等中间结果，减少重复计算
    std::vector<double> row_means(rows, 0.0);
    std::vector<double> col_means(cols, 0.0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            row_means[i] += matrix[i][j];
            col_means[j] += matrix[i][j];
        }
    }
    for (double& mean : row_means) {
        mean /= cols;
    }
    for (double& mean : col_means) {
        mean /= rows;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            double sum_xy = 0.0;
            double sum_x_squared = 0.0;
            double sum_y_squared = 0.0;
            for (size_t k = 0; k < rows; ++k) {
                double x = matrix[i][k] - row_means[i];
                double y = matrix[j][k] - col_means[j];
                sum_xy += x * y;
                sum_x_squared += x * x;
                sum_y_squared += y * y;
            }
            double numerator = sum_xy;
            double denominator = std::sqrt(sum_x_squared * sum_y_squared);
            if (denominator!= 0) {
                correlation_matrix[i][j] = numerator / denominator;
            } else {
                correlation_matrix[i][j] = 0.0;
            }
        }
    }
    return correlation_matrix;
}

// 数据过滤函数模板实现，增加了根据元数据过滤以及是否过滤异常值的功能，更灵活的过滤逻辑
template<typename T>
std::vector<T> DataAnalyzer::filterData(int min_length, const std::string& filter_metadata, bool filter_outliers, const std::string& custom_filter) {
    std::vector<T> filtered_data;
    if (filter_outliers) {
        std::vector<DataRecord> outliers = detectOutliers();
        for (const auto& record : data_records) {
            if (std::find(outliers.begin(), outliers.end(), record) == outliers.end()) {
                if (record.data.size() > min_length && (filter_metadata.empty() || record.metadata == filter_metadata) && evaluateCustomFilter(record, custom_filter)) {
                    filtered_data.push_back(record);
                }
            }
        }
    } else {
        for (const auto& record : data_records) {
            if (record.data.size() > min_length && (filter_metadata.empty() || record.metadata == filter_metadata) && evaluateCustomFilter(record, custom_filter)) {
                filtered_data.push_back(record);
            }
        }
    }
    return filtered_data;
}

// 数据分组分析函数，根据指定字段进行分组并计算每组的统计信息（简单示例），支持更多统计指标和分组方式
std::map<std::string, std::map<std::string, double>> DataAnalyzer::groupBy(const std::string& field, const std::vector<std::string>& statistics_fields) {
    std::map<std::string, std::map<std::string, double>> grouped_data;
    for (const auto& record : data_records) {
        const std::string& group_key = (field == "data")? record.data : (field == "metadata")? record.metadata : std::to_string(record.record_id);
        if (grouped_data.find(group_key) == grouped_data.end()) {
            std::map<std::string, double> group_statistics;
            for (const auto& stat_field : statistics_fields) {
                if (stat_field == "average_length") {
                    // 计算每组平均长度逻辑，待完善
                    group_statistics[stat_field] = 0;
                } else if (stat_field == "frequency") {
                    // 计算每组频率逻辑，待完善
                    group_statistics[stat_field] = 0;
                }
            }
            grouped_data[group_key] = group_statistics;
        }
    }
    return grouped_data;
}

// 异常值检测函数，使用简单的统计方法（如 3 倍标准差法）检测异常值（简单示例），可切换不同检测方法
std::vector<DataRecord> DataAnalyzer::detectOutliers(const std::string& method) {
    std::vector<DataRecord> outliers;
    if (method == "3_sigma") {
        std::vector<double> data_lengths;
        for (const auto& record : data_records) {
            data_lengths.push_back(record.data.size());
        }
        double mean = calculateMean(data_lengths);
        double std_dev = calculateStdDev(data_lengths);
        for (const auto& record : data_records) {
            if (std::abs(record.data.size() - mean) > 3 * std_dev) {
                outliers.push_back(record);
            }
        }
    }
    return outliers;
}

// 数据合并函数，将两个数据集按指定规则合并（简单示例，假设按记录 ID 合并），处理更多合并冲突情况
std::vector<DataRecord> DataAnalyzer::mergeData(const std::vector<DataRecord>& other_data, const std::string& merge_strategy) {
    std::map<int, DataRecord> merged_map;
    mergeDataInternal(data_records, merge_strategy, merged_map);
    mergeDataInternal(other_data, merge_strategy, merged_map);
    std::vector<DataRecord> merged_data;
    for (const auto& pair : merged_map) {
        merged_data.push_back(pair.second);
    }
    return merged_data;
}

// 复杂数据查询函数，根据多个条件查询数据（简单示例），支持更复杂的查询表达式和逻辑运算
std::vector<DataRecord> DataAnalyzer::queryData(const std::vector<std::string>& conditions) {
    std::vector<DataRecord> result;
    for (const auto& record : data_records) {
        bool match = true;
        for (const auto& condition : conditions) {
            if (!evaluateCondition(condition)) {
                match = false;
                break;
            }
        }
        if (match) {
            result.push_back(record);
        }
    }
    return result;
}

// 数据可视化建议函数，根据数据特征给出适合的可视化方式建议
std::vector<std::string> DataAnalyzer::suggestVisualization() {
    std::vector<std::string> suggestions;
    // 简单判断是否数值型数据，若大部分是数值型可考虑柱状图、折线图等
    bool isMostlyNumeric = true;
    int numericCount = 0;
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            numericCount++;
        }
    }
    if (numericCount > data_records.size() / 2) {
        suggestions.push_back("柱状图（适用于展示数据分布情况）");
        suggestions.push_back("折线图（适用于展示数据随时间或其他顺序变量的变化趋势）");
    }

    // 若有分类字段，可考虑饼图等
    std::map<std::string, int> metadataCount;
    for (const auto& record : data_records) {
        metadataCount[record.metadata]++;
    }
    if (metadataCount.size() > 1) {
        suggestions.push_back("饼图（适用于展示各分类占比情况）");
    }

    return suggestions;
}

// 时间序列分析函数（简单示例，假设数据包含时间相关字段），可进行趋势分析、周期性分析等
void DataAnalyzer::timeSeriesAnalysis(const std::string& time_field) {
    if (isTimeSeriesData(time_field)) {
        timeSeriesTrendAnalysis(time_field);
        timeSeriesPeriodicityAnalysis(time_field);
    } else {
        std::cerr << "指定字段并非有效的时间序列字段，无法进行时间序列分析。" << std::endl;
    }
}

// 辅助函数，将数据记录转换为数值向量（简单示例，可根据实际情况拓展）
std::vector<std::vector<double>> DataAnalyzer::convertToMatrix() {
    std::vector<std::vector<double>> matrix;
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            std::vector<double> row;
            row.push_back(std::stod(record.data));
            matrix.push_back(row);
        }
    }
    return matrix;
}

// 辅助函数，计算均值
double DataAnalyzer::calculateMean(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// 辅助函数，计算标准差
double DataAnalyzer::calculateStdDev(const std::vector<double>& data) {
    double mean = calculateMean(data);
    double sumSquaredDiff = 0.0;
    for (const double& value : data) {
        double diff = value - mean;
        sumSquaredDiff += diff * diff;
    }
    return std::sqrt(sumSquaredDiff / (data.size() - 1));
}

// 辅助函数，合并数据的具体实现，根据不同合并策略处理
void DataAnalyzer::mergeDataInternal(const std::vector<DataRecord>& other_data, const std::string& merge_strategy, std::map<int, DataRecord>& merged_map) {
    if (merge_strategy == "id_based") {
        for (const auto& record : data_records) {
            merged_map[record.record_id] = record;
        }
        for (const auto& record : other_data) {
            merged_map[record.record_id] = record;
        }
    } else if (merge_strategy == "data_based") {
        // 假设以 data 字段内容为合并依据，若相同则合并（简单示例，可完善更复杂逻辑）
        for (const auto& record : data_records) {
            merged_map[record.record_id] = record;
        }
        for (const auto& record : other_data) {
            if (merged_map.find(record.record_id) == merged_map.end()) {
                merged_map[record.record_id] = record;
            } else {
                // 合并逻辑，比如合并 metadata 等字段（简单示例，拼接字符串）
                merged_map[record.record_id].metadata += ", " + record.metadata;
            }
        }
    } else {
        throw std::runtime_error("无效的合并策略");
    }
}

// 辅助函数，执行数据查询的具体逻辑，解析复杂查询条件
bool DataAnalyzer::evaluateCondition(const std::string& condition) {
    // 简单示例，假设条件格式为 "field operator value"，如 "data > 10"
    std::vector<std::string> parts = StringUtil::split(condition,'');
    if (parts.size()!= 3) {
        throw std::runtime_error("无效的查询条件格式");
    }
    const std::string& field = parts[0];
    const std::string& op = parts[1];
    const std::string& valueStr = parts[2];
    double value = std::stod(valueStr);
    for (const auto& record : data_records) {
        double recordValue = 0;
        if (field == "data") {
            if (!StringUtil::isNumeric(record.data)) {
                continue;
            }
            recordValue = std::stod(record.data);
        } else if (field == "record_id") {
            recordValue = record.record_id;
        }
        if (op == ">") {
            if (recordValue > value) {
                return true;
            }
        } else if (op == "<") {
            if (recordValue < value) {
                return true;
            }
        } else if (op == "==") {
            if (recordValue == value) {
                return true;
            }
        } else if (op == ">=") {
            if (recordValue >= value) {
                return true;
            }
        } else if (op == "<=") {
            if (recordValue <= value) {
                return true;
            }
        }
    }
    return false;
}

// 辅助函数，判断数据是否为时间序列数据（简单根据字段名判断，可完善）
bool DataAnalyzer::isTimeSeriesData(const std::string& field) {
    return StringUtil::endsWith(field, "_time") || StringUtil::startsWith(field, "time_");
}

// 辅助函数，进行时间序列趋势分析（简单示例，可采用更专业算法）
void DataAnalyzer::timeSeriesTrendAnalysis(const std::string& time_field) {
    std::vector<double> timeValues;
    std::vector<double> dataValues;
    for (const auto& record : data_records) {
        if (field == "data") {
            if (!StringUtil::isNumeric(record.data)) {
                continue;
            }
            dataValues.push_back(std::stod(record.data));
        } else if (field == "record_id") {
            dataValues.push_back(record.record_id);
        }
        // 假设时间字段也是可转换为数值的简单格式（需完善实际解析逻辑）
        timeValues.push_back(std::stod(record.metadata));
    }
    if (timeValues.size() < 2 || dataValues.size() < 2) {
        std::cerr << "数据量不足，无法进行有效的趋势分析。" << std::endl;
        return;
    }
    double slope = 0;  // 待计算斜率，简单线性回归示例，可完善更复杂算法
    // 简单计算斜率示例，可根据实际需求采用专业统计库等优化
    for (size_t i = 0; i < timeValues.size() - 1; ++i) {
        slope += (dataValues[i + 1] - dataValues[i]) / (timeValues[i + 1] - timeValues[i]);
    }
    slope /= (timeValues.size() - 1);
    if (slope > 0) {
        std::cout << "时间序列呈现上升趋势。" << std::endl;
    } else if (slope < 0) {
        std::cout << "时间序列呈现下降趋势。" << std::endl;
    } else {
        std::cout << "时间序列趋势相对平稳。" << std::endl;
    }
}

// 辅助函数，进行时间序列周期性分析（简单示例，可采用更专业算法）
void DataAnalyzer::timeSeriesPeriodicityAnalysis(const std::string& time_field) {
    std::vector<double> timeValues;
    std::vector<double> dataValues;
    for (const auto& record : data_records) {
        if (field == "data") {
            if (!StringUtil::isNumeric(record.data)) {
                continue;
            }
            dataValues.push_back(std::stod(record.data));
        } else if (field == "record_id") {
            dataValues.push_back(record.record_id);
        }
        // 假设时间字段也是可转换为数值的简单格式（需完善实际解析逻辑）
        timeValues.push_back(std::stod(record.metadata));
    }
    if (timeValues.size() < 2 || dataValues.size() < 2) {
        std::cerr << "数据量不足，无法进行有效的周期性分析。" << std::endl;
        return;
    }
    // 简单示例，可采用自相关等专业方法完善，这里仅简单判断相邻时间间隔是否有规律
    std::vector<double> timeIntervals;
    for (size_t i = 0; i < timeValues.size() - 1; ++i) {
        timeIntervals.push_back(timeValues[i + 1] - timeValues[i]);
    }
    double meanInterval = calculateMean(timeIntervals);
    double stdDevInterval = calculateStdDev(timeIntervals);
    bool hasPeriodicity = false;
    for (const double& interval : timeIntervals) {
        if (std::abs(interval - meanInterval) < 2 * stdDevInterval) {
            hasPeriodicity = true;
            break;
        }
    }
    if (hasPeriodicity) {
        std::cout << "时间序列可能存在周期性特征。" << std::endl;
    } else {
        std::cout << "未发现明显的时间序列周期性特征。" << std::endl;
    }
}
