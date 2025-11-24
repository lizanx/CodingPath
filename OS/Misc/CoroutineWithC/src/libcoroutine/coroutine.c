#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "coroutine.h"

enum
{
    CO_R15 = 0,
    CO_R14,
    CO_R13,
    CO_R12,
    CO_R9,
    CO_R8,
    CO_RBP,
    CO_RDI,
    CO_RSI,
    CO_RDX,
    CO_RCX,
    CO_RBX,
    CO_RSP,
};

struct co_context
{
    void *regs[13];
};

struct coroutine
{
    struct co_context ctx;
    char *stack;
    size_t stack_size;
    int status;
    struct coroutine *prev;
    start_coroutine start;
    void *data;
};

extern void co_ctx_swap(struct co_context *curr, struct co_context *next);

static struct coroutine *g_curr_co = NULL;

void co_entrance(struct coroutine *co)
{
    void *result = co->start(co->data);
    co->status = CO_STATUS_DEAD;
    co_yield(result, NULL);
}

void co_ctx_make(struct coroutine *co)
{
    char *sp = co->stack + co->stack_size - sizeof(void *);
    sp = (char *)((intptr_t)sp & -16LL);
    *(void **)sp = (void *)co_entrance;
    co->ctx.regs[CO_RSP] = sp;
    co->ctx.regs[CO_RDI] = co;
}

struct coroutine *co_new(start_coroutine start, size_t stack_size)
{
    struct coroutine *co = malloc(sizeof(struct coroutine));
    memset(&co->ctx, 0, sizeof(co->ctx));
    if (stack_size)
        co->stack = malloc(stack_size);
    else
        co->stack = NULL;
    co->stack_size = stack_size;
    co->status = CO_STATUS_INIT;
    co->prev = NULL;
    co->start = start;

    return co;
}

void co_free(struct coroutine *co)
{
    free(co->stack);
    free(co);
}

void check_init()
{
    if (!g_curr_co)
    {
        g_curr_co = co_new(NULL, 0);
        g_curr_co->status = CO_STATUS_RUNNING;
    }
}

int co_resume(struct coroutine *next, void *param, void **result)
{
    check_init();

    switch (next->status)
    {
    case CO_STATUS_INIT:
        co_ctx_make(next);
    case CO_STATUS_PENDING:
        break;
    default:
        return -1;
    }

    struct coroutine *curr = g_curr_co;
    g_curr_co = next;
    next->prev = curr;
    curr->status = CO_STATUS_NORMAL;
    next->status = CO_STATUS_RUNNING;
    next->data = param;
    co_ctx_swap(&curr->ctx, &next->ctx);
    if (result)
        *result = curr->data;

    return 0;
}

int co_yield(void *result, void **param)
{
    check_init();

    struct coroutine *curr = g_curr_co;
    struct coroutine *prev = curr->prev;

    if (!prev)
        return -1;

    g_curr_co = prev;
    if (curr->status != CO_STATUS_DEAD)
        curr->status = CO_STATUS_PENDING;
    prev->status = CO_STATUS_RUNNING;
    prev->data = result;
    co_ctx_swap(&curr->ctx, &prev->ctx);
    if (param)
        *param = curr->data;

    return 0;
}
