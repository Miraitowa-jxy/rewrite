#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>
#include "DataReader.h"
#include "DataAnalyzer.h"

class FileHandler {
public:
    FileHandler();
    // 将数据记录保存为 CSV 文件（简单示例，可拓展更多格式支持）
    void saveDataAsCsv(const std::vector<DataRecord>& data, const std::string& file_path);
    // 从其他格式文件读取数据并转换为 DataRecord 格式（简单示例，假设从 JSON 格式转换，需引入 JSON 库）
    std::vector<DataRecord> readDataFromJson(const std::string& file_path);
    // 备份文件功能
    bool backupFile(const std::string& file_path, const std::string& backup_dir);
private:
    // 辅助函数，创建目录（如果不存在）
    void createDirectory(const std::string& dir_path);
};

#endif
