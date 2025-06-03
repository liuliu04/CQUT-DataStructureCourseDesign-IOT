#include "stick_sorter.h"
#include <stdlib.h>
#include <stddef.h>  // 为NULL定义
#include <string.h>  // 为calloc定义

// 交换两个木棒的位置
static void swap_sticks(Stick* a, Stick* b) {
    Stick temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序的分区函数
static int partition(Stick* sticks, int low, int high) {
    Stick pivot = sticks[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (sticks[j].length < pivot.length || 
            (sticks[j].length == pivot.length && sticks[j].weight < pivot.weight)) {
            i++;
            swap_sticks(&sticks[i], &sticks[j]);
        }
    }
    swap_sticks(&sticks[i + 1], &sticks[high]);
    return i + 1;
}

// 快速排序实现
static void quick_sort(Stick* sticks, int low, int high) {
    if (low < high) {
        int pi = partition(sticks, low, high);
        quick_sort(sticks, low, pi - 1);
        quick_sort(sticks, pi + 1, high);
    }
}

// 初始化木棒数组
void init_sticks(Stick* sticks, int* count) {
    *count = 0;
    for (int i = 0; i < MAX_STICKS; i++) {
        sticks[i].length = 0;
        sticks[i].weight = 0;
        sticks[i].index = 0;
    }
}

// 添加木棒
void add_stick(Stick* sticks, int* count, int length, int weight) {
    if (*count >= MAX_STICKS) {
        return;
    }
    sticks[*count].length = length;
    sticks[*count].weight = weight;
    sticks[*count].index = *count + 1;
    (*count)++;
}

// 计算最长递增子序列
static int* find_lis(Stick* sticks, int count, int* lis_length) {
    int* dp = (int*)malloc(sizeof(int) * count);  // 存储以每个位置结尾的最长递增子序列长度
    int* prev = (int*)malloc(sizeof(int) * count);  // 存储前驱节点
    int* result = (int*)malloc(sizeof(int) * count);  // 存储最终结果
    
    // 初始化
    for (int i = 0; i < count; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }
    
    // 计算最长递增子序列
    int max_len = 1;
    int max_end = 0;
    
    for (int i = 1; i < count; i++) {
        for (int j = 0; j < i; j++) {
            // 只有当当前木棒的长度和重量都大于等于前一个木棒时，才能加入序列
            if (sticks[i].length >= sticks[j].length && 
                sticks[i].weight >= sticks[j].weight) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                    if (dp[i] > max_len) {
                        max_len = dp[i];
                        max_end = i;
                    }
                }
            }
        }
    }
    
    // 重建最长递增子序列
    *lis_length = max_len;
    int current = max_end;
    for (int i = max_len - 1; i >= 0; i--) {
        result[i] = sticks[current].index;
        current = prev[current];
    }
    
    free(dp);
    free(prev);
    return result;
}

// 计算最优加工顺序
SortResult calculate_min_time(Stick* sticks, int count) {
    SortResult result;
    result.order = NULL;
    result.order_size = 0;
    result.total_time = 0;
    
    if (count == 0) {
        return result;
    }
    
    // 创建临时数组
    Stick temp_sticks[MAX_STICKS];
    for (int i = 0; i < count; i++) {
        temp_sticks[i] = sticks[i];
    }
    
    // 使用快速排序对木棒进行排序
    quick_sort(temp_sticks, 0, count - 1);
    
    // 找到最长递增子序列
    int lis_length;
    int* lis = find_lis(temp_sticks, count, &lis_length);
    
    // 计算需要额外准备时间的木棒
    int* used = (int*)calloc(count, sizeof(int));
    int* order = (int*)malloc(sizeof(int) * count);
    int order_size = 0;
    int total_time = 1;  // 第一根木棒需要1分钟准备时间
    
    // 首先处理最长递增子序列中的木棒
    for (int i = 0; i < lis_length; i++) {
        order[order_size++] = lis[i];
        used[lis[i] - 1] = 1;
    }
    
    // 处理剩余的木棒
    for (int i = 0; i < count; i++) {
        if (!used[i]) {
            // 检查是否需要额外准备时间
            if (order_size > 0) {
                int last_index = order[order_size - 1] - 1;
                if (temp_sticks[i].length < temp_sticks[last_index].length || 
                    temp_sticks[i].weight < temp_sticks[last_index].weight) {
                    total_time++;  // 需要额外准备时间
                }
            }
            order[order_size++] = temp_sticks[i].index;
        }
    }
    
    result.order = order;
    result.order_size = order_size;
    result.total_time = total_time;
    
    free(lis);
    free(used);
    return result;
}

// 释放排序结果
void free_sort_result(SortResult* result) {
    if (result->order != NULL) {
        free(result->order);
        result->order = NULL;
    }
    result->order_size = 0;
    result->total_time = 0;
} 