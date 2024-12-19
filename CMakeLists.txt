# 设置最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(examplelib VERSION 1.0.0)

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Boost 库，需要根据实际安装情况调整路径等配置
find_package(Boost REQUIRED COMPONENTS regex filesystem program_options)
# 查找 Eigen 库，假设 Eigen 是以头文件形式包含，这里简单添加头文件路径示例
include_directories(/path/to/eigen) 

# 添加子目录包含具体模块的源文件等
add_subdirectory(src)

# 设置生成可执行文件等相关内容，这里可根据实际使用情况添加测试可执行文件等配置
add_executable(my_example_app main.cpp)
target_link_libraries(my_example_app examplelib Boost::regex Boost::filesystem Boost::program_options Eigen3::Eigen)

# 添加测试相关配置
enable_testing()
add_subdirectory(tests)

# 把 Catch2 的头文件路径添加进来
include_directories(extern/Catch2/single_include)

# 用于在测试编译时定义相关宏，便于 Catch2 使用
add_definitions(-DCATCH_CONFIG_MAIN)

# 遍历 tests 目录下所有以 test_ 开头的.cpp 文件，添加为测试可执行文件
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} examplelib Boost::regex Boost::filesystem Boost::program_options Eigen3::Eigen)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
