#include "MyAES.h"

// printa os bits na tela
void print_binary(uint32_t num)
{
    for (int i = 31; i >= 0; i--)
        printf("%d", (num >> i) & 1);
    printf("\n");
}


// converte para uint32 a chave
uint32_t build_block_key(char *str)
{
    uint32_t block = 0;
    int i = 0;

    while (i < 4 && str[i])
    {
        block |= ((uint32_t)str[i]) << (24 - 8 * i); // bitwise para encaixar os bits no uint32
        i++;
    }
    return block;
}

// printf que exibi na tela os bis em formato hexa
void back_to_string(uint32_t *matrix, int len)
{
    FILE *fp = fopen("result.txt", "w"); // Cria ou sobrescreve o arquivo

    if (!fp) {
        perror("Erro ao criar o arquivo result.txt");
        return;
    }

    for (int i = 0; i < len; i++) {
        uint32_t val = matrix[i];

        // Quebra o uint32_t em 4 bytes (big endian)
        printf("%02X%02X%02X%02X",
            (val >> 24) & 0xFF,
            (val >> 16) & 0xFF,
            (val >> 8)  & 0xFF,
            (val)       & 0xFF);

        fprintf(fp, "%02X%02X%02X%02X",
            (val >> 24) & 0xFF,
            (val >> 16) & 0xFF,
            (val >> 8)  & 0xFF,
            (val)       & 0xFF);
    }

    printf("\n");
    fprintf(fp, "\n");

    fclose(fp); // Fecha o arquivo pra garantir que os dados foram salvos
}


// printf que exibi na tela os bis em formato ascii
void back_to_string_ascii(uint32_t *matrix, size_t len_blocks) {
    size_t i;
    FILE *fp = fopen("result.txt", "w"); // Abre o arquivo para escrita (cria se não existir)

    if (!fp) {
        perror("Erro ao criar o arquivo result.txt");
        return;
    }

    // Quebra o uint32_t em 4 bytes (big endian)
    for (i = 0; i < len_blocks; i++) {
        uint8_t byte1 = (matrix[i] >> 24) & 0xFF;
        uint8_t byte2 = (matrix[i] >> 16) & 0xFF;
        uint8_t byte3 = (matrix[i] >> 8) & 0xFF;
        uint8_t byte4 = matrix[i] & 0xFF;

        // Imprime na tela
        printf("%c%c%c%c", byte1, byte2, byte3, byte4);
        // Escreve no arquivo
        fprintf(fp, "%c%c%c%c", byte1, byte2, byte3, byte4);
    }

    printf("\n");
    fprintf(fp, "\n"); // Termina a linha no arquivo também

    fclose(fp); // Fecha o arquivo direitinho
}


