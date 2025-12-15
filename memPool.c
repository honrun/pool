/*
 *  modifier: Honrun
 *  date:     2021/12/21 20:42
 */
#include "memPool.h"


int8_t cMemPoolCreate(MemPoolType *ptypePool, void *pvMem, size_t size, size_t count)
{
    size_t addr;

    if((ptypePool == NULL) || (pvMem == NULL) || (size < sizeof(MemPoolType)) || (count < 1))
        return 1;

    ptypePool->next = ptypePool->prev = ptypePool;

    /* 分块，插入到空闲链表 */
    for(addr = memPoolRoundUp((size_t)pvMem); count > 0; --count, addr += size)
    {
        vMemPoolFree(ptypePool, (void *)addr);
    }

    return 0;
}

void *pvMemPoolMalloc(MemPoolType *ptypePool)
{
    if((ptypePool == NULL) || (ptypePool->next == ptypePool))
        return NULL;

    ptypePool = ptypePool->next;

    /* 释放空闲链表的第1个节点 */
    ptypePool->prev->next = ptypePool->next;
    ptypePool->next->prev = ptypePool->prev;

    return (void *)ptypePool;
}

void vMemPoolFree(MemPoolType *ptypePool, void *pvMem)
{
    MemPoolType *ptypeNow = pvMem;

    if(pvMem != NULL)
    {
        /* 插入到空闲链表的最后 */
        ptypeNow->prev        = ptypePool->prev;
        ptypeNow->next        = ptypePool;
        ptypePool->prev->next = ptypeNow;
        ptypePool->prev       = ptypeNow;
    }
}
