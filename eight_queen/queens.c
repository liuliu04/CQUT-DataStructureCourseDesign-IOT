#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queens.h"

// 广度优先搜索实现
typedef struct {
    int* board;
    int row;
} QueueNode;

typedef struct {
    QueueNode* nodes;
    int front;
    int rear;
    int capacity;
} Queue;

// 初始化解决方案集合
SolutionSet* createSolutionSet(int initialCapacity) {
    SolutionSet* set = (SolutionSet*)malloc(sizeof(SolutionSet));
    set->solutions = (Solution*)malloc(initialCapacity * sizeof(Solution));
    set->capacity = initialCapacity;
    set->size = 0;
    return set;
}

// 释放解决方案集合
void freeSolutionSet(SolutionSet* set) {
    if (set) {
        for (int i = 0; i < set->size; i++) {
            free(set->solutions[i].positions);
        }
        free(set->solutions);
        free(set);
    }
}

// 添加新的解决方案
void addSolution(SolutionSet* set, int* positions) {
    if (set->size >= set->capacity) {
        set->capacity *= 2;
        set->solutions = (Solution*)realloc(set->solutions, set->capacity * sizeof(Solution));
    }
    
    Solution* newSolution = &set->solutions[set->size];
    newSolution->positions = (int*)malloc(QUEENS_BOARD_SIZE * sizeof(int));
    for (int i = 0; i < QUEENS_BOARD_SIZE; i++) {
        newSolution->positions[i] = positions[i];
    }
    newSolution->count = QUEENS_BOARD_SIZE;
    set->size++;
}

// 获取指定索引的解决方案
int* getSolution(SolutionSet* set, int index) {
    if (index >= 0 && index < set->size) {
        return set->solutions[index].positions;
    }
    return NULL;
}

// 获取解决方案总数
int getSolutionCount(SolutionSet* set) {
    return set->size;
}

// 检查位置是否安全
bool isSafe(int* board, int row, int col) {
    // 检查同一列
    for (int i = 0; i < row; i++) {
        if (board[i] == col) {
            return false;
        }
    }
    
    // 检查左上对角线
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i] == j) {
            return false;
        }
    }
    
    // 检查右上对角线
    for (int i = row - 1, j = col + 1; i >= 0 && j < QUEENS_BOARD_SIZE; i--, j++) {
        if (board[i] == j) {
            return false;
        }
    }
    
    return true;
}

// 深度优先搜索实现
void dfs(int row, int* board, SolutionSet* solutions) {
    if (row == QUEENS_BOARD_SIZE) {
        addSolution(solutions, board);
        return;
    }
    
    for (int col = 0; col < QUEENS_BOARD_SIZE; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            dfs(row + 1, board, solutions);
            board[row] = -1;
        }
    }
}

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->nodes = (QueueNode*)malloc(capacity * sizeof(QueueNode));
    queue->front = queue->rear = 0;
    queue->capacity = capacity;
    return queue;
}

void enqueue(Queue* queue, int* board, int row) {
    QueueNode node;
    node.board = (int*)malloc(QUEENS_BOARD_SIZE * sizeof(int));
    for (int i = 0; i < QUEENS_BOARD_SIZE; i++) {
        node.board[i] = board[i];
    }
    node.row = row;
    
    queue->nodes[queue->rear] = node;
    queue->rear = (queue->rear + 1) % queue->capacity;
}

QueueNode dequeue(Queue* queue) {
    QueueNode node = queue->nodes[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    return node;
}

bool isQueueEmpty(Queue* queue) {
    return queue->front == queue->rear;
}

void bfs(SolutionSet* solutions) {
    Queue* queue = createQueue(1000);
    int* initialBoard = (int*)malloc(QUEENS_BOARD_SIZE * sizeof(int));
    for (int i = 0; i < QUEENS_BOARD_SIZE; i++) {
        initialBoard[i] = -1;
    }
    
    enqueue(queue, initialBoard, 0);
    
    while (!isQueueEmpty(queue)) {
        QueueNode current = dequeue(queue);
        
        if (current.row == QUEENS_BOARD_SIZE) {
            addSolution(solutions, current.board);
            free(current.board);
            continue;
        }
        
        for (int col = 0; col < QUEENS_BOARD_SIZE; col++) {
            if (isSafe(current.board, current.row, col)) {
                int* newBoard = (int*)malloc(QUEENS_BOARD_SIZE * sizeof(int));
                for (int i = 0; i < QUEENS_BOARD_SIZE; i++) {
                    newBoard[i] = current.board[i];
                }
                newBoard[current.row] = col;
                enqueue(queue, newBoard, current.row + 1);
            }
        }
        
        free(current.board);
    }
    
    free(queue->nodes);
    free(queue);
    free(initialBoard);
}

// 回溯法实现
void backtrack(int row, int* board, SolutionSet* solutions) {
    if (row == QUEENS_BOARD_SIZE) {
        addSolution(solutions, board);
        return;
    }
    
    for (int col = 0; col < QUEENS_BOARD_SIZE; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            backtrack(row + 1, board, solutions);
            board[row] = -1;
        }
    }
}

// 打印解决方案
void printSolution(Solution* solution) {
    printf("解决方案:\n");
    for (int i = 0; i < QUEENS_BOARD_SIZE; i++) {
        for (int j = 0; j < QUEENS_BOARD_SIZE; j++) {
            if (solution->positions[i] == j) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
} 