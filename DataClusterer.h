#ifndef DATA_CLUSTERER_H
#define DATA_CLUSTERER_H

#include <vector>
#include <string>
#include "DataAnalyzer.h"

// 简单的 K-Means 聚类器
class DataClusterer {
public:
    DataClusterer(const std::vector<DataRecord>& data, int num_clusters);

    // 执行聚类
    std::vector<int> clusterData();

private:
    std::vector<DataRecord> data_records;
    int num_clusters;
    std::vector<double> extractNumericData();
    double distance(double a, double b);
    int findClosestCentroid(double point, const std::vector<double>& centroids);
    std::vector<double> updateCentroids(const std::vector<double>& data, const std::vector<int>& labels, int num_clusters);
};

#endif
