# 重庆理工大学物联网工程专业数据结构课程设计

本项目包含四个经典的数据结构课程设计题目，分别实现了农夫过河问题、木棒问题、哈夫曼编码/译码器和八皇后问题的求解。

## 项目结构

- `River/` - 农夫过河问题（带Qt界面）
- `huffman/` - 哈夫曼编码/译码器
- `eight_queen/` - 八皇后问题（带Qt界面）
- `sticksorter/` - 木棒问题（带Qt界面）

## 功能说明

### 1. 农夫过河问题 (River Crossing Problem)
- 使用Qt实现图形界面
- 核心算法在`river_core.c`中实现
- 支持可视化展示过河过程
- 文件：`River/`

### 2. 哈夫曼编码/译码器 (Huffman Coding)
- 纯C语言实现
- 支持文本文件的编码和解码
- 包含频率统计、建树、编码和解码功能
- 文件：`huffman/`

### 3. 八皇后问题 (Eight Queens Puzzle)
- 使用Qt实现图形界面
- 支持可视化展示皇后放置过程
- 包含回溯算法实现
- 文件：`eight_queen/`

### 4. 木棒问题 (Stick Sorter)
- 使用Qt实现图形界面
- 支持可视化展示木棒排序过程
- 包含排序算法实现
- 文件：`sticksorter/`

## 运行环境要求

- C/C++编译器（支持C11标准）
- Qt 5.x 或更高版本（用于运行带界面的项目）
- CMake 3.x 或更高版本

## 编译运行说明

### 哈夫曼编码/译码器
```bash
cd huffman
mkdir build && cd build
cmake ..
make
./huffman
```

### 农夫过河问题
```bash
cd River
qmake River.pro
make
./River
```

### 八皇后问题
```bash
cd eight_queen
mkdir build && cd build
cmake ..
make
./eight_queen
```

## 注意事项

1. 确保已安装Qt开发环境
2. 编译前请确保已安装必要的开发工具
3. 如遇到编译问题，请检查CMake和Qt的版本兼容性

## 作者

dubbkd

## 许可证

本项目仅用于教学目的
