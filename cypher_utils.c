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
void back_to_string(uint32_t *matrix, int len)
{
    for (int i = 0; i < len; i++) {
        uint32_t val = matrix[i];

        // Quebra o uint32_t em 4 bytes (big endian)
        printf("%02X%02X%02X%02X",
            (val >> 24) & 0xFF,
            (val >> 16) & 0xFF,
            (val >> 8)  & 0xFF,
            (val)       & 0xFF);
    }
    printf("\n");
}

void back_to_string_ascii(uint32_t *matrix, size_t len_blocks) {
    size_t i;
    for (i = 0; i < len_blocks; i++) {
        uint8_t byte1 = (matrix[i] >> 24) & 0xFF;
        uint8_t byte2 = (matrix[i] >> 16) & 0xFF;
        uint8_t byte3 = (matrix[i] >> 8) & 0xFF;
        uint8_t byte4 = matrix[i] & 0xFF;

        printf("%c%c%c%c", byte1, byte2, byte3, byte4);
    }
    printf("\n");
}

