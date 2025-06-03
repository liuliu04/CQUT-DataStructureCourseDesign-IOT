#ifndef STICK_SORTER_H
#define STICK_SORTER_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_STICKS 5000

// 木棒结构体
typedef struct {
    int length;
    int weight;
    int index;
} Stick;

// 排序结果结构体
typedef struct {
    int* order;         // 加工顺序
    int order_size;     // 顺序数组大小
    int total_time;     // 总准备时间
} SortResult;

// 函数声明
void init_sticks(Stick* sticks, int* count);
void add_stick(Stick* sticks, int* count, int length, int weight);
SortResult calculate_min_time(Stick* sticks, int count);
void free_sort_result(SortResult* result);

#ifdef __cplusplus
}
#endif

#endif // STICK_SORTER_H 