#include "FileUtil.h"

// 检查文件是否存在函数实现
bool FileUtil::fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

// 获取文件大小函数实现
size_t FileUtil::getFileSize(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    return file.tellg();
}

// 读取文件内容到字符串函数实现
std::string FileUtil::readFileToString(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    } else {
        throw std::runtime_error("无法打开文件: " + filePath);
    }
}

// 将字符串内容写入文件函数实现
void FileUtil::writeStringToFile(const std::string& content, const std::string& filePath) {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << content;
        file.close();
    } else {
        throw std::runtime_error("无法打开文件进行写入: " + filePath);
    }
}

// 复制文件函数实现
void FileUtil::copyFile(const std::string& sourceFilePath, const std::string& destinationFilePath) {
    std::ifstream sourceFile(sourceFilePath, std::ios::binary);
    std::ofstream destinationFile(destinationFilePath, std::ios::binary);
    if (sourceFile.is_open() && destinationFile.is_open()) {
        destinationFile << sourceFile.rdbuf();
        sourceFile.close();
        destinationFile.close();
    } else {
        throw std::runtime_error("复制文件时出现问题，源文件或目标文件无法打开");
    }
}

// 删除文件函数实现
void FileUtil::deleteFile(const std::string& filePath) {
    if (remove(filePath.c_str())!= 0) {
        throw std::runtime_error("删除文件失败: " + filePath);
    }
}

// 获取文件所在目录路径函数实现
std::string FileUtil::getDirectoryPath(const std::string& filePath) {
    size_t pos = filePath.find_last_of('/');
    if (pos == std::string::npos) {
        pos = filePath.find_last_of('\\');
    }
    return filePath.substr(0, pos);
}

// 获取文件名（不含路径）函数实现
std::string FileUtil::getFileName(const std::string& filePath) {
    size_t pos = filePath.find_last_of('/');
    if (pos == std::string::npos) {
        pos = filePath.find_last_of('\\');
    }
    return filePath.substr(pos + 1);
}

// 重命名文件函数实现
void FileUtil::renameFile(const std::string& oldName, const std::string& newName) {
    if (rename(oldName.c_str(), newName.c_str())!= 0) {
        throw std::runtime_error("重命名文件失败");
    }
}
