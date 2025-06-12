#include "MyAES.h"

uint32_t derive_key(uint32_t key, int round) {
    return (key << round | key >> (32 - round)) ^ (0xA5A5A5A5 * round);
}
