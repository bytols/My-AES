#include "MyAES.h"


// esse é o algoritimo que roda as rodas de criptografia
static void cypher_round(uint32_t *matrix, uint32_t key, int len)
{
    int     i;
    int     round;

    for (round = 0; round < 3; round++)
    {
        // realizo um xor com chave e os blocos de 32bits
        for(i = 0; i < len; i++)
            matrix[i] ^= key;
        // realizo  a substiuição!
        sbox(matrix, len, key, CRYPT);
        // realizo a permutação
        permutacao(matrix, len, key);
        // derivo a key
        key = derive_key(key, round + 1);
    }
    // back to string
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
    }
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
    int      len;
    char     char_key[1024];

    // etapa de recebemento dos dados, escolho se vai ser criptograifa ou decripto, passo o nome do arquivo e a chave em formato char *
    printf("digite o nome do arquivo!\n");
    scanf("%s", filename);
    printf("digite a chave!\n");
    scanf("%s", char_key);
    FILE *fp = fopen(filename, "r"); // abrindo o arquivo
    if (!fp) { // tratativa de erro ao abrir o arquivo
        perror("Erro ao abrir arquivo");
        return 1;
    }

    // levo o cursor até o fim do arquivo e contanto quantoas bytes ele tem, para conseguir o len
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);

    // malloco o tamanho necessário para receber o conteudo do arquivo.
    char *conteudo = malloc(filesize + 1);
    // tratativa de erro do malloc;
    if (!conteudo) {
        perror("Erro ao alocar memória");
        fclose(fp);
        return 1;
    }

    // leio o arquivo e preencho no bufer conteudo
    fread(conteudo, 1, filesize, fp);
    conteudo[filesize] = '\0';
    fclose(fp); // fecho o arquivo

    len = (strlen(conteudo) + 3) / 4; // pego o len da quantidade de blocos de 32 bits necessários para conter o texto

    matrix = convert_to_block(conteudo); // crio a matrix de blocos de 32 bits 
    // check se a chave tem o tamanho adqueado
    if(strlen(char_key) > 4)
    {
        printf("chave com mais de 32 bits\n");
        return (0);
    }
    key = build_block_key(char_key); // converto a chave para uint32
    int choice = 0;
    printf("escolha o modo: \n 1 - Criptografar \n 2 - Decriptografar \n");
    scanf("%d", &choice); //captura a escolha!
    switch (choice) // switch para decidir entre crypt ou decrypt
    {
    case 1:
        cypher_round(matrix, key, len); // invoca a sequencia de criptografia
        break;
    case 2:
        cypher_decrypt(conteudo, key, len); // invoca a sequencia de decriptografia
        break;
    default:
        printf("escolha invalida\n");
    }
    free(conteudo);
    return (0);
}
