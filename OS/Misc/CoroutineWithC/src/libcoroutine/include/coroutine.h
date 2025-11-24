#pragma once
#include <stddef.h>

#ifndef __x86_64__
#error "Only support x86-64"
#endif

enum
{
    CO_STATUS_INIT,    // 初始状态
    CO_STATUS_PENDING, // 执行 yield 操作进入的挂起状态
    CO_STATUS_NORMAL,  // 执行 resume 操作进入的挂起状态
    CO_STATUS_RUNNING, // 运行状态
    CO_STATUS_DEAD,    // 死亡状态
};

typedef void *(*start_coroutine)(void *);
struct coroutine;

struct coroutine *co_new(start_coroutine start, size_t stack_size);
void co_free(struct coroutine *co);
// int co_status(struct coroutine *co);
// struct coroutine *co_curr();
int co_resume(struct coroutine *next, void *param, void **result);
int co_yield(void *result, void **param);
