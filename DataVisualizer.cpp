#include "DataVisualizer.h"
// 假设的第三方可视化库头文件包含
#include "matplotlibcpp.h"

// 构造函数，获取分析器对象并提前计算统计信息
DataVisualizer::DataVisualizer(const DataAnalyzer& analyzer) : analyzer(analyzer), statistics(analyzer.calculateStatistics()) {}

// 绘制柱状图展示数据频率等统计信息的函数实现（基于假设的可视化库 API）
void DataVisualizer::plotBarChart(const std::string& title, const std::string& xlabel, const std::string& ylabel) {
    plt::Figure fig;
    plt::Axes ax;
    initFigure(fig, ax, title, xlabel, ylabel);
    std::vector<std::string> metadata;
    std::vector<double> frequencies;
    for (const auto& pair : statistics) {
        if (pair.first.find("frequency_") == 0) {
            metadata.push_back(pair.first.substr(10));
            frequencies.push_back(pair.second);
        }
    }
    ax.bar(metadata, frequencies);
    fig.show();
}

// 绘制折线图展示数据变化趋势等的函数实现（基于假设的可视化库 API）
void DataVisualizer::plotLineChart(const std::string& title, const std::string& xlabel, const std::string& ylabel) {
    plt::Figure fig;
    plt::Axes ax;
    initFigure(fig, ax, title, xlabel, ylabel);
    // 这里简单示例，需根据实际有意义的数据来绘制折线图，目前只是占位逻辑
    std::vector<double> x_data = {1, 2, 3, 4, 5};
    std::vector<double> y_data = {2, 4, 6, 8, 10};
    ax.plot(x_data, y_data);
    fig.show();
}

// 辅助函数，初始化图形等基本设置（根据使用的可视化库具体实现）
void DataVisualizer::initFigure(plt::Figure& fig, plt::Axes& ax, const std::string& title, const std::string& xlabel, const std::string& ylabel) {
    fig = plt::figure();
    ax = fig.add_subplot(111);
    ax.set_title(title);
    ax.set_xlabel(xlabel);
    ax.set_ylabel(ylabel);
}
