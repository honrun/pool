#ifndef _memPool_H_
#define _memPool_H_

#include "stdint.h"


typedef struct MemPoolStruct{
    struct MemPoolStruct *prev;
    struct MemPoolStruct *next;
}MemPoolType;

/* 使x对n字节对齐 */
#define memPoolRoundUp(x)   (((x) + (sizeof(size_t) - 1)) & (~(sizeof(size_t) - 1)))


int8_t cMemPoolCreate(MemPoolType *ptypePool, void *pvMem, size_t size, size_t count);
void *pvMemPoolMalloc(MemPoolType *ptypePool);
void vMemPoolFree(MemPoolType *ptypePool, void *pvMem);


#endif
