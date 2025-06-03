#include "river_core.h"
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 16
#define QUEUE_SIZE 100

// 队列结构体
typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// 队列操作函数
static void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

static void enqueue(Queue* q, int item) {
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
}

static int dequeue(Queue* q) {
    int item = q->items[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return item;
}

static int is_queue_empty(Queue* q) {
    return q->front == q->rear;
}

// 检查状态是否安全
int is_safe_state(const RiverState* state) {
    // 如果农夫不在场，检查是否有危险情况
    if (state->farmer != state->wolf) {
        if (state->wolf == state->sheep) return 0;  // 狼和羊在一起
    }
    if (state->farmer != state->sheep) {
        if (state->sheep == state->cabbage) return 0;  // 羊和白菜在一起
    }
    return 1;
}

// 将状态编码为整数
int encode_state(const RiverState* state) {
    return (state->farmer << 3) | (state->wolf << 2) | 
           (state->cabbage << 1) | state->sheep;
}

// 将整数解码为状态
void decode_state(int encoded_state, RiverState* state) {
    state->farmer = (encoded_state >> 3) & 1;
    state->wolf = (encoded_state >> 2) & 1;
    state->cabbage = (encoded_state >> 1) & 1;
    state->sheep = encoded_state & 1;
}

// 寻找解决方案
Solution* find_solution(void) {
    Queue moveTo;
    int route[MAX_STATES];
    int visited[MAX_STATES];
    Solution* solution = (Solution*)malloc(sizeof(Solution));
    
    // 初始化
    init_queue(&moveTo);
    memset(route, -1, sizeof(route));
    memset(visited, 0, sizeof(visited));
    
    // 初始状态：全部在南岸
    int initial_state = 0;
    enqueue(&moveTo, initial_state);
    route[initial_state] = initial_state;
    visited[initial_state] = 1;
    
    // 广度优先搜索
    while (!is_queue_empty(&moveTo)) {
        int current = dequeue(&moveTo);
        
        // 如果到达目标状态
        if (current == 15) {  // 1111
            break;
        }
        
        // 尝试移动农夫和可能的物品
        for (int i = 0; i < 4; i++) {
            int next = current ^ (1 << 3);  // 移动农夫
            if (i < 3) {
                next ^= (1 << i);  // 移动物品
            }
            
            if (!visited[next]) {
                RiverState state;
                decode_state(next, &state);
                if (is_safe_state(&state)) {
                    route[next] = current;
                    visited[next] = 1;
                    enqueue(&moveTo, next);
                }
            }
        }
    }
    
    // 构建解决方案路径
    int path[MAX_STATES];
    int path_length = 0;
    int current = 15;
    
    while (current != 0) {
        path[path_length++] = current;
        current = route[current];
    }
    path[path_length++] = 0;
    
    // 反转路径
    solution->states = (int*)malloc(path_length * sizeof(int));
    solution->state_count = path_length;
    for (int i = 0; i < path_length; i++) {
        solution->states[i] = path[path_length - 1 - i];
    }
    
    return solution;
}

// 释放解决方案内存
void free_solution(Solution* solution) {
    if (solution) {
        free(solution->states);
        free(solution);
    }
} 