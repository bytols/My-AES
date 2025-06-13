#include "MyAES.h" 

// Gera uma S-box dinâmica (substituição) de 4 bits baseada em uma chave
static void gerar_sbox_dinamica(uint8_t *sbox4, uint32_t chave)
{
    // Inicializa a S-box com valores de 0 a 15
    for (int i = 0; i < 16; i++)
        sbox4[i] = i;

    // Usa a chave como seed para gerar aleatoriedade reprodutível
    srand(chave);

    // Aplica o algoritmo de Fisher-Yates para embaralhar os valores da S-box
    for (int i = 15; i > 0; i--) {
        int j = rand() % (i + 1);
        uint8_t tmp = sbox4[i];
        sbox4[i] = sbox4[j];
        sbox4[j] = tmp;
    }
}

// Gera uma permutação dinâmica de pares de índices (para usar na permutação dos nibbles)
static void gerar_permutacao_dinamica(int pares[4][2], uint32_t chave)
{
    // Vetor de índices de 0 a 7 (representa os 8 nibbles de um bloco de 32 bits)
    int indices[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    srand(chave);

    // Embaralha os índices
    for (int i = 7; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    // Agrupa os índices embaralhados em pares
    for (int i = 0; i < 4; i++) {
        pares[i][0] = indices[2*i];
        pares[i][1] = indices[2*i + 1];
    }
}

// Gera a S-box inversa com base na chave (útil para decriptografar)
static void gerar_sbox_inversa(uint8_t *sbox_inv, uint32_t chave)
{
    uint8_t sbox[16];
    gerar_sbox_dinamica(sbox, chave);  // Gera a mesma S-box usada na criptografia

    // Inverte os valores da S-box, ou seja, cria a S-box inversa
    for (int i = 0; i < 16; i++)
        sbox_inv[sbox[i]] = i;
}

// Função que aplica a S-box (ou sua inversa) em todos os blocos da matriz
void sbox(uint32_t *matrix, int len, uint32_t key, t_mode mode)
{
    int i;
    int j;
    uint32_t bloco;

    j = 0;
    uint8_t sbox4[16];
    
    // Gera a S-box dependendo do modo (0 para criptografar, outro valor para decriptar)
    if(mode == 0)
        gerar_sbox_dinamica(sbox4, key);
    else
        gerar_sbox_inversa(sbox4, key);

    // Aplica a substituição S-box em cada bloco da matriz
    while (j < len)
    {
        bloco = matrix[j];
        for(i = 0; i < 8; i++) // Itera por cada nibble (4 bits) do bloco
        {
            uint32_t mask = 0xF << (i * 4); // Cria uma máscara para isolar o nibble
            uint8_t nibble = (bloco >> (i * 4)) & 0xF; // Extrai o nibble
            uint8_t substituted = sbox4[nibble]; // Substitui usando a S-box
            bloco = (bloco & ~mask) | ((uint32_t)substituted << (i * 4));  // Reinsere o nibble substituído
        }
        matrix[j] = bloco;
        j++;
    }
}

// Função que aplica permutação nos nibbles de cada bloco da matriz
void permutacao(uint32_t *matrix, int len, uint32_t key)
{
    int j = 0;
    while (j < len)
    {
        uint32_t bloco = matrix[j];

        int pares[4][2]; 
        gerar_permutacao_dinamica(pares, key); // Gera os pares de índices para permutação

        // Para cada par, troca os nibbles entre as posições a e b
        for (int k = 0; k < 4; k++)
        {
            int a = pares[k][0];
            int b = pares[k][1];

            uint32_t mask_a = 0xF << (a * 4);
            uint32_t mask_b = 0xF << (b * 4);

            uint8_t nibble_a = (bloco >> (a * 4)) & 0xF;
            uint8_t nibble_b = (bloco >> (b * 4)) & 0xF;

            bloco = (bloco & ~mask_a) | (nibble_b << (a * 4)); // Coloca nibble_b na posição a
            bloco = (bloco & ~mask_b) | (nibble_a << (b * 4)); // Coloca nibble_a na posição b
        }

        matrix[j] = bloco;
        j++;
    }
}
