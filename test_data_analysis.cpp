#include <catch2/catch.hpp>
#include "../src/DataAnalyzer.h"
#include "../src/DataReader.h"

TEST_CASE("DataAnalyzer calculateAverageDataLength functionality", "[DataAnalyzer]") {
    DataReader reader("test_data.txt");
    auto data_records = reader.readData();
    DataAnalyzer analyzer(data_records);
    double avg_length = analyzer.calculateAverageDataLength();
    REQUIRE(avg_length >= 0);  // 简单验证结果合理性
}
