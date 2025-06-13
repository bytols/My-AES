#include "MyAES.h"

// Função que deriva uma nova chave a partir da chave original e do número da rodada
uint32_t derive_key(uint32_t key, int round) {
    // Faz um rotate left na chave com base na rodada, e depois aplica XOR com um valor fixo multiplicado pela rodada
    return (key << round | key >> (32 - round)) ^ (0xA5A5A5A5 * round);
}


// Função que gera uma lista de 3 chaves derivadas para o processo de descriptografia
uint32_t *decrypt_derive_key(uint32_t key) 
{
    // Aloca um vetor com 3 posições para armazenar as chaves das 3 rodadas
    uint32_t *list = malloc(sizeof(uint32_t) * 3);

    // Primeira chave é a original
    list[0] = key;

    // Segunda chave é derivada da primeira
    list[1] = derive_key(list[0], 1);

    // Terceira chave é derivada da segunda
    list[2] = derive_key(list[1], 2);

    // Retorna o vetor com as 3 chaves (uma para cada rodada)
    return list;
}
