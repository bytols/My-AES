#include "MyAES.h" 

void    sbox(uint32_t *matrix, int len)
{
    int i;
    int j;
    uint32_t bloco;

    j = 0;
    uint8_t sbox4[16] = {
        0xE, 0x4, 0xD, 0x1,
        0x2, 0xF, 0xB, 0x8,
        0x3, 0xA, 0x6, 0xC,
        0x5, 0x9, 0x0, 0x7
    };

    while (j < len)
    {
        bloco = matrix[j];
        for(i = 0; i < 8; i ++)
        {
            uint32_t mask = 0xF << (i * 4);
            uint8_t nibble = (bloco >> (i * 4)) & 0xF;
            uint8_t substituted = sbox4[nibble];
            bloco = (bloco & ~mask) | ((uint32_t)substituted << (i * 4));  
        }
        matrix[j] = bloco;
        j++;
    }
}
