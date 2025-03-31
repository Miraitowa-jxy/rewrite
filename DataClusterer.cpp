#include "DataClusterer.h"
#include <algorithm>
#include <random>

DataClusterer::DataClusterer(const std::vector<DataRecord>& data, int num_clusters)
    : data_records(data), num_clusters(num_clusters) {}

std::vector<int> DataClusterer::clusterData() {
    std::vector<double> data = extractNumericData();
    if (data.empty()) {
        return {};
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, data.size() - 1);
    std::vector<double> centroids;
    for (int i = 0; i < num_clusters; ++i) {
        centroids.push_back(data[dis(gen)]);
    }
    std::vector<int> labels(data.size());
    bool changed = true;
    while (changed) {
        changed = false;
        for (size_t i = 0; i < data.size(); ++i) {
            int new_label = findClosestCentroid(data[i], centroids);
            if (new_label != labels[i]) {
                labels[i] = new_label;
                changed = true;
            }
        }
        if (changed) {
            centroids = updateCentroids(data, labels, num_clusters);
        }
    }
    return labels;
}

std::vector<double> DataClusterer::extractNumericData() {
    std::vector<double> numericData;
    for (const auto& record : data_records) {
        if (StringUtil::isNumeric(record.data)) {
            numericData.push_back(std::stod(record.data));
        }
    }
    return numericData;
}

double DataClusterer::distance(double a, double b) {
    return std::abs(a - b);
}

int DataClusterer::findClosestCentroid(double point, const std::vector<double>& centroids) {
    double min_distance = distance(point, centroids[0]);
    int closest_index = 0;
    for (size_t i = 1; i < centroids.size(); ++i) {
        double dist = distance(point, centroids[i]);
        if (dist < min_distance) {
            min_distance = dist;
            closest_index = i;
        }
    }
    return closest_index;
}

std::vector<double> DataClusterer::updateCentroids(const std::vector<double>& data, const std::vector<int>& labels, int num_clusters) {
    std::vector<double> new_centroids(num_clusters, 0.0);
    std::vector<int> counts(num_clusters, 0);
    for (size_t i = 0; i < data.size(); ++i) {
        int label = labels[i];
        new_centroids[label] += data[i];
        counts[label]++;
    }
    for (int i = 0; i < num_clusters; ++i) {
        if (counts[i] > 0) {
            new_centroids[i] /= counts[i];
        }
    }
    return new_centroids;
}
