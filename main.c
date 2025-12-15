#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "memPool.h"


/* 模拟内存池块大小 */
#define MEM_POOL_BLOCK_SIZE     memPoolRoundUp(12)
/* 模拟内存池块数量 */
#define MEM_POOL_BLOCK_COUNT    64

MemPoolType g_typeMemPool;
/* 需要增加 sizeof(size_t) 个长度，以保证字节对齐 */
static uint8_t st_ucMemPool[(MEM_POOL_BLOCK_SIZE * MEM_POOL_BLOCK_COUNT) + sizeof(size_t)];


int main(void)
{
    size_t i = 0, j = 0, *pMem[256] = {0};

    printf("memory pool test.\r\n");

    cMemPoolCreate(&g_typeMemPool, st_ucMemPool, MEM_POOL_BLOCK_SIZE, MEM_POOL_BLOCK_COUNT);

    while(1)
    {
        i = abs(rand()) % 3;
        j = abs(rand()) & 255;

        /* 新建 */
        if(i == 0)
        {
            if(pMem[j] == NULL)
            {
                pMem[j] = pvMemPoolMalloc(&g_typeMemPool);

                if(pMem[j] != NULL)
                {
                    memset(pMem[j], rand(), MEM_POOL_BLOCK_SIZE);
                }

                printf("new: j: %d,\tpMem: 0x%08X\r\n", j, (size_t)pMem[j]);
            }
        }
        /* 删除 */
        else
        {
            if(pMem[j] != NULL)
            {
                printf("del: j: %d,\tpMem: 0x%08X\r\n", j, (size_t)pMem[j]);

                vMemPoolFree(&g_typeMemPool, pMem[j]);
                pMem[j] = NULL;
            }
        }
    }

    return 0;
}
