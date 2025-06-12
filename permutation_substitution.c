#include "MyAES.h" 

static void gerar_sbox_dinamica(uint8_t *sbox4, uint32_t chave)
{
    for (int i = 0; i < 16; i++)
        sbox4[i] = i;

    srand(chave);

    for (int i = 15; i > 0; i--) {
        int j = rand() % (i + 1);
        uint8_t tmp = sbox4[i];
        sbox4[i] = sbox4[j];
        sbox4[j] = tmp;
    }
}

static void gerar_permutacao_dinamica(int pares[4][2], uint32_t chave)
{
    int indices[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    srand(chave);

    for (int i = 7; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    for (int i = 0; i < 4; i++) {
        pares[i][0] = indices[2*i];
        pares[i][1] = indices[2*i + 1];
    }
}

void    sbox(uint32_t *matrix, int len, uint32_t key)
{
    int i;
    int j;
    uint32_t bloco;

    j = 0;
    uint8_t sbox4[16];
    gerar_sbox_dinamica(sbox4, key);

    while (j < len)
    {
        bloco = matrix[j];
        for(i = 0; i < 8; i++)
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

void permutacao(uint32_t *matrix, int len, uint32_t key)
{
    int j = 0;
    while (j < len)
    {
        uint32_t bloco = matrix[j];

        int pares[4][2]; 
        gerar_permutacao_dinamica(pares, key);

        for (int k = 0; k < 4; k++)
        {
            int a = pares[k][0];
            int b = pares[k][1];

            uint32_t mask_a = 0xF << (a * 4);
            uint32_t mask_b = 0xF << (b * 4);

            uint8_t nibble_a = (bloco >> (a * 4)) & 0xF;
            uint8_t nibble_b = (bloco >> (b * 4)) & 0xF;

            bloco = (bloco & ~mask_a) | (nibble_b << (a * 4));
            bloco = (bloco & ~mask_b) | (nibble_a << (b * 4));
        }

        matrix[j] = bloco;
        j++;
    }
}


