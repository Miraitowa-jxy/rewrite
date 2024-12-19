#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <string>
#include <fstream>

// 自定义文件工具类，提供一些文件相关的操作方法
class FileUtil {
public:
    // 检查文件是否存在函数
    static bool fileExists(const std::string& filePath);

    // 获取文件大小函数，以字节为单位
    static size_t getFileSize(const std::string& filePath);

    // 读取文件内容到字符串函数
    static std::string readFileToString(const std::string& filePath);

    // 将字符串内容写入文件函数
    static void writeStringToFile(const std::string& content, const std::string& filePath);

    // 复制文件函数
    static void copyFile(const std::string& sourceFilePath, const std::string& destinationFilePath);

    // 删除文件函数
    static void deleteFile(const std::string& filePath);

    // 获取文件所在目录路径函数
    static std::string getDirectoryPath(const std::string& filePath);

    // 获取文件名（不含路径）函数
    static std::string getFileName(const std::string& filePath);

    // 重命名文件函数
    static void renameFile(const std::string& oldName, const std::string& newName);
};

#endif
