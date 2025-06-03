#ifndef RIVER_CORE_H
#define RIVER_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

// 状态结构体
typedef struct {
    int farmer;  // 农夫位置：0-南岸，1-北岸
    int wolf;    // 狼的位置：0-南岸，1-北岸
    int sheep;   // 羊的位置：0-南岸，1-北岸
    int cabbage; // 白菜位置：0-南岸，1-北岸
} RiverState;

// 解决方案结构体
typedef struct {
    int* states;     // 状态数组
    int state_count; // 状态数量
} Solution;

// 核心算法函数
int is_safe_state(const RiverState* state);
int encode_state(const RiverState* state);
void decode_state(int encoded_state, RiverState* state);
Solution* find_solution(void);
void free_solution(Solution* solution);

#ifdef __cplusplus
}
#endif

#endif // RIVER_CORE_H 