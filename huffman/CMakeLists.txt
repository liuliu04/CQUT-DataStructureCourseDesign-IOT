cmake_minimum_required(VERSION 3.10)
project(huffman C)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 添加编译选项
add_compile_options(-Wall -Wextra)

# 添加源文件
set(SOURCES
    main.c
    huffman.c
)

# 创建可执行文件
add_executable(huffman ${SOURCES})

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 