#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

#include <vector>
#include <string>
#include <map>
#include "DataAnalyzer.h"

// 简单假设使用第三方库的命名空间，实际需替换为真实库的对应内容
namespace plt {
class Figure;
class Axes;
}

class DataVisualizer {
public:
    DataVisualizer(const DataAnalyzer& analyzer);
    // 绘制柱状图展示数据频率等统计信息
    void plotBarChart(const std::string& title, const std::string& xlabel, const std::string& ylabel, const std::vector<std::string>& data_fields = {});
    // 绘制折线图展示数据变化趋势等（简单示例，需根据实际数据含义拓展）
    void plotLineChart(const std::string& title, const std::string& xlabel, const std::string& ylabel, const std::vector<std::string>& data_fields = {});
    // 绘制散点图展示两个变量之间的关系
    void plotScatterPlot(const std::string& title, const std::string& xlabel, const std::string& ylabel, const std::string& x_data_field, const std::string& y_data_field);
    // 绘制饼图展示分类数据占比
    void plotPieChart(const std::string& title, const std::vector<std::string>& labels, const std::vector<double>& sizes);
    // 绘制箱线图展示数据分布情况
    void plotBoxPlot(const std::string& title, const std::vector<double>& data);
    // 设置图形大小
    void setFigureSize(int width, int height);
    // 设置坐标轴范围
    void setAxisLimits(const std::string& axis, double min, double max);
    // 保存图形为文件
    void saveFigure(const std::string& file_path);
private:
    const DataAnalyzer& analyzer;
    std::map<std::string, double> statistics;
    // 辅助函数，初始化图形等基本设置（根据使用的可视化库具体实现）
    void initFigure(plt::Figure& fig, plt::Axes& ax, const std::string& title, const std::string& xlabel, const std::string& ylabel);
    // 辅助函数，根据数据字段获取数据值（支持多种数据类型转换）
    std::vector<double> getDataValues(const std::vector<std::string>& data_fields);
};

#endif
