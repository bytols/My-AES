#include "MyAES.h"

static void cypher_round(uint32_t *matrix, uint32_t key, int len)
{
    int     i;

    for(i = 0; matrix[i] != 0; i++)
        matrix[i] = matrix[i] ^ key;
    printf("aqui estão as novas chaves depois do XOR:\n");
    for (i = 0; matrix[i] != 0; i++)
        print_binary(matrix[i]);
    for (i = 0; matrix[i] != 0; i++)
        printf("aqui está os valores dos bits em hexa: %x e em decimal %d\n ", matrix[i], matrix[i]);
    sbox(matrix, len);
    printf("aqui estão os novos bits depois do sbox:\n");
    for (i = 0; matrix[i] != 0; i++)
        print_binary(matrix[i]);
}

int main(int argc, char *argv[])
{
    uint32_t *matrix;
    uint32_t key;
    int       i;
    int         len;

    if (argc < 3)
    {
        printf("valor incorreto de parametros!\n");
        return (0);
    }
    len = (strlen(argv[1]) + 3) / 4;
    matrix = convert_to_block(argv[1]);
    for (i = 0; matrix[i] != 0; i++)
        print_binary(matrix[i]);
    key = build_block_key(argv[2]);
    printf("aqui está a key:\n");
    print_binary(key);
    cypher_round(matrix, key, len);
    return (0);
}