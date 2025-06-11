#include "MyAES.h"

void print_binary(uint32_t num)
{
    for (int i = 31; i >= 0; i--)
        printf("%d", (num >> i) & 1);
    printf("\n");
}

uint32_t build_block_key(char *str)
{
    uint32_t block = 0;
    int i = 0;

    while (i < 4 && str[i])
    {
        block |= ((uint32_t)str[i]) << (24 - 8 * i);
        i++;
    }
    return block;
}