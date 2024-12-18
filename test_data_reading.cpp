#include <catch2/catch.hpp>
#include "../src/DataReader.h"

TEST_CASE("DataReader readData functionality", "[DataReader]") {
    DataReader reader("test_data.txt");  // 假设存在测试数据文件
    auto data_records = reader.readData();
    REQUIRE(data_records.size() > 0);  // 简单检查是否读取到数据
}
