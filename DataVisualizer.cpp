#include "DataVisualizer.h"
// 假设的第三方可视化库头文件包含
#include "matplotlibcpp.h"

// 构造函数，获取分析器对象并提前计算统计信息
DataVisualizer::DataVisualizer(const DataAnalyzer& analyzer) : analyzer(analyzer), statistics(analyzer.calculateStatistics()) {}

// 绘制柱状图展示数据频率等统计信息的函数实现（基于假设的可视化库 API）
void DataVisualizer::plotBarChart(const std::string& title, const std::string& xlabel, const std::string& ylabel, const std::vector<std::string>& data_fields) {
    plt::Figure fig;
    plt::Axes ax;
    initFigure(fig, ax, title, xlabel, ylabel);
    std::vector<std::string> metadata;
    std::vector<double> frequencies;
    if (data_fields.empty()) {
        for (const auto& pair : statistics) {
            if (pair.first.find("frequency_") == 0) {
                metadata.push_back(pair.first.substr(10));
                frequencies.push_back(pair.second);
            }
        }
    } else {
        for (const auto& field : data_fields) {
            std::string frequency_key = "frequency_" + field;
            if (statistics.find(frequency_key)!= statistics.end()) {
                metadata.push_back(field);
                frequencies.push_back(statistics[frequency_key]);
            }
        }
    }
    ax.bar(metadata, frequencies);
    fig.show();
}

// 绘制折线图展示数据变化趋势等的函数实现（基于假设的可视化库 API）
void DataVisualizer::plotLineChart(const std::string& title, const std::string& xlabel, const std::string& ylabel, const std::vector<std::string>& data_fields) {
    plt::Figure fig;
    plt::Axes ax;
    initFigure(fig, ax, title, xlabel, ylabel);
    std::vector<double> x_data;
    std::vector<double> y_data;
    if (data_fields.empty()) {
        // 简单示例，假设使用记录 ID 作为 x 轴数据，数据长度作为 y 轴数据（可根据实际情况修改）
        for (const auto& record : analyzer.data_records) {
            x_data.push_back(record.record_id);
            y_data.push_back(record.data.size());
        }
    } else {
        x_data = getDataValues({data_fields[0]});
        y_data = getDataValues({data_fields[1]});
    }
    ax.plot(x_data, y_data);
    fig.show();
}

// 绘制散点图展示两个变量之间的关系的函数实现
void DataVisualizer::plotScatterPlot(const std::string& title, const std::string& xlabel, const std::string& ylabel, const std::string& x_data_field, const std::string& y_data_field) {
    plt::Figure fig;
    plt::Axes ax;
    initFigure(fig, ax, title, xlabel, ylabel);
    std::vector<double> x_data = getDataValues({x_data_field});
    std::vector<double> y_data = getDataValues({y_data_field});
    ax.scatter(x_data, y_data);
    fig.show();
}

// 绘制饼图展示分类数据占比的函数实现
void DataVisualizer::plotPieChart(const std::string& title, const std::vector<std::string>& labels, const std::vector<double>& sizes) {
    plt::Figure fig;
    plt::Axes ax;
    initFigure(fig, ax, title, "", "");
    ax.pie(sizes, labels = labels);
    fig.show();
}

// 绘制箱线图展示数据分布情况的函数实现
void DataVisualizer::plotBoxPlot(const std::string& title, const std::vector<double>& data) {
    plt::Figure fig;
    plt::Axes ax;
    initFigure(fig, ax, title, "", "");
    ax.boxplot(data);
    fig.show();
}

// 设置图形大小的函数实现
void DataVisualizer::setFigureSize(int width, int height) {
    plt::figure_size(width, height);
}

// 设置坐标轴范围的函数实现
void DataVisualizer::setAxisLimits(const std::string& axis, double min, double max) {
    if (axis == "x") {
        plt::xlim(min, max);
    } else if (axis == "y") {
        plt::ylim(min, max);
    }
}

// 保存图形为文件的函数实现
void DataVisualizer::saveFigure(const std::string& file_path) {
    plt::savefig(file_path);
}

// 辅助函数，初始化图形等基本设置（根据使用的可视化库具体实现）
void DataVisualizer::initFigure(plt::Figure& fig, plt::Axes& ax, const std::string& title, const std::string& xlabel, const std::string& ylabel) {
    fig = plt::figure();
    ax = fig.add_subplot(111);
    ax.set_title(title);
    ax.set_xlabel(xlabel);
    ax.set_ylabel(ylabel);
}

// 辅助函数，根据数据字段获取数据值（支持多种数据类型转换）
std::vector<double> DataVisualizer::getDataValues(const std::vector<std::string>& data_fields) {
    std::vector<double> data_values;
    for (const auto& record : analyzer.data_records) {
        for (const auto& field : data_fields) {
            if (field == "data") {
                if (StringUtil::isNumeric(record.data)) {
                    data_values.push_back(std::stod(record.data));
                }
            } else if (field == "metadata") {
                if (StringUtil::isNumeric(record.metadata)) {
                    data_values.push_back(std::stod(record.metadata));
                }
            } else if (field == "record_id") {
                data_values.push_back(record.record_id);
            }
        }
    }
    return data_values;
}
