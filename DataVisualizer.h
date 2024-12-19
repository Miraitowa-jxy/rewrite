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
    void plotBarChart(const std::string& title, const std::string& xlabel, const std::string& ylabel);
    // 绘制折线图展示数据变化趋势等（简单示例，需根据实际数据含义拓展）
    void plotLineChart(const std::string& title, const std::string& xlabel, const std::string& ylabel);
private:
    const DataAnalyzer& analyzer;
    std::map<std::string, double> statistics;
    // 辅助函数，初始化图形等基本设置（根据使用的可视化库具体实现）
    void initFigure(plt::Figure& fig, plt::Axes& ax, const std::string& title, const std::string& xlabel, const std::string& ylabel);
};

#endif
