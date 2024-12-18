# 设置最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(examplelib VERSION 1.0.0)

# 查找Boost库，需要根据实际安装情况调整路径等配置
find_package(Boost REQUIRED COMPONENTS regex)
# 查找Eigen库，假设Eigen是以头文件形式包含，这里简单添加头文件路径示例
include_directories(/path/to/eigen) 

# 添加子目录包含具体模块的源文件等
add_subdirectory(src)

# 设置生成可执行文件等相关内容，这里可根据实际使用情况添加测试可执行文件等配置
add_executable(my_example_app main.cpp)
target_link_libraries(my_example_app examplelib Boost::regex)


# 把Catch2的头文件路径添加进来
include_directories(extern/Catch2/single_include)

# 用于在测试编译时定义相关宏，便于Catch2使用
add_definitions(-DCATCH_CONFIG_MAIN)

# 可以添加测试相关的可执行文件，这里假设测试文件都放在 tests 目录下
add_executable(test_examplelib tests/test_data_reading.cpp tests/test_data_analysis.cpp)
target_link_libraries(test_examplelib examplelib Boost::regex Eigen3::Eigen)
