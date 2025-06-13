#include "MyAES.h"

uint32_t derive_key(uint32_t key, int round) {
    return (key << round | key >> (32 - round)) ^ (0xA5A5A5A5 * round);
}


uint32_t *decrypt_derive_key(uint32_t key) 
{
    uint32_t *list = malloc(sizeof(uint32_t) * 3);
    list[0] = key;
    list[1] = derive_key(list[0], 1);
    list[2] = derive_key(list[1], 2);
    return list;
}
