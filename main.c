#include "MyAES.h"

static void cypher_round(uint32_t *matrix, uint32_t key, int len)
{
    int     i;
    int     round;

    for (round = 0; round < 3; round++)
    {
        for(i = 0; i < len; i++)
            matrix[i] ^= key;
        printf("aqui está a key depois do xor\n");
        print_binary(key);
        sbox(matrix, len, key, CRYPT);
        permutacao(matrix, len, key);
        key = derive_key(key, round + 1);
    }
    back_to_string(matrix, len);
}

static void cypher_decrypt(char *conteudo, uint32_t key, int len)
{
    int         i;
    int         round;
    size_t      byte_len;
    uint32_t    *key_list;
    uint8_t     *bytes;
    size_t      len_blocks;
    uint32_t    *matrix;

    (void) len;
    bytes = hex_string_to_bytes(conteudo, &byte_len);
    if (!bytes) return;

    matrix = bytes_to_uint32_array(bytes, byte_len, &len_blocks);
    if (!matrix)
    {
        free(bytes);
        return;
    }

    key_list = decrypt_derive_key(key);
    if (!key_list)
    {
        free(bytes);
        free(matrix);
        return;
    }

    for (round = 2; round >= 0; round--)
    {
        key = key_list[round];
        permutacao(matrix, len_blocks, key); 
        sbox(matrix, len_blocks, key, DECRYPT);
        for (i = 0; i < (int)len_blocks; i++)
            matrix[i] ^= key;
        printf("aqui está a key depois do xor\n");
        print_binary(key);
    }
    //for (i = 0; i < len; i++)
    //    print_binary(matrix[i]);
    back_to_string(matrix, len_blocks);
    back_to_string_ascii(matrix, len_blocks);

    free(bytes);
    free(matrix);
    free(key_list);
}


int main()
{
    uint32_t *matrix;
    uint32_t key;
    char     filename[1024];
    int      i;
    int      len;
    char     char_key[1024];

    printf("digite o nome do arquivo!\n");
    scanf("%s", filename);
    printf("aqui está o nome escrito %s\n", filename);
    printf("digite a chave!\n");
    scanf("%s", char_key);
    printf("aqui está a chave escrito %s|\n", char_key);
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);

    char *conteudo = malloc(filesize + 1);
    if (!conteudo) {
        perror("Erro ao alocar memória");
        fclose(fp);
        return 1;
    }

    fread(conteudo, 1, filesize, fp);
    conteudo[filesize] = '\0';
    fclose(fp);

    printf("\nConteúdo do arquivo:\n%s\n", conteudo);

    len = (strlen(conteudo) + 3) / 4;
    matrix = convert_to_block(conteudo);
    for (i = 0; matrix[i] != 0; i++)
        print_binary(matrix[i]);
    key = build_block_key(char_key); // verify if its higher than 32 bits
    printf("aqui está a key:\n");
    print_binary(key);
    int choice = 0;
    printf("escolha o modo: \n 1 - Criptografar \n 2 - Decriptografar \n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        cypher_round(matrix, key, len);
        break;
    case 2:
        cypher_decrypt(conteudo, key, len);
        break;
    default:
        printf("escolha invalida\n");
        return 0; // check for leaks
    }

    free(conteudo);
    return (0);
}
