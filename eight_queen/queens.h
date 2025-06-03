#ifndef QUEENS_H
#define QUEENS_H

#include <stdbool.h>

#define QUEENS_BOARD_SIZE 8

// 定义解决方案结构
typedef struct {
    int* positions;  // 存储每行皇后的列位置
    int count;       // 当前已放置的皇后数量
} Solution;

// 定义解决方案集合
typedef struct {
    Solution* solutions;  // 存储所有解决方案
    int capacity;        // 当前分配的容量
    int size;           // 当前解决方案数量
} SolutionSet;

// 函数声明
SolutionSet* createSolutionSet(int initialCapacity);
void freeSolutionSet(SolutionSet* set);
void addSolution(SolutionSet* set, int* positions);
bool isSafe(int* board, int row, int col);
void dfs(int row, int* board, SolutionSet* solutions);
void bfs(SolutionSet* solutions);
void backtrack(int row, int* board, SolutionSet* solutions);
int* getSolution(SolutionSet* set, int index);
int getSolutionCount(SolutionSet* set);

#endif // QUEENS_H 