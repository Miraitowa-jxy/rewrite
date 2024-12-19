#include "FileHandler.h"
// 假设引入 JSON 解析库，比如 nlohmann/json（需正确安装配置）
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// 构造函数，目前无特殊初始化操作
FileHandler::FileHandler() {}

// 将数据记录保存为 CSV 文件的函数实现（简单格式，可完善 CSV 格式规范等细节）
void FileHandler::saveDataAsCsv(const std::vector<DataRecord>& data, const std::string& file_path) {
    std::ofstream out_file(file_path);
    if (out_file.is_open()) {
        out_file << "data,metadata,record_id\n";
        for (const auto& record : data) {
            out_file << record.data << "," << record.metadata << "," << record.record_id << "\n";
        }
        out_file.close();
    } else {
        throw std::runtime_error("无法打开文件进行写入: " + file_path);
    }
}

// 从其他格式文件（
