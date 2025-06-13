#include "MyAES.h"


// utilizando shift do bit wise e ou para preencher as posições com os bits do char *
uint32_t build_block(char *bloco_de_4) {
    return (bloco_de_4[0] << 24) |
           (bloco_de_4[1] << 16) |
           (bloco_de_4[2] << 8)  |
           bloco_de_4[3];
}

// converto os blocos char * em uma lista de uint32_t *
uint32_t *convert_to_32_bits(char **matrix, int len)
{
    uint32_t    *new_matrix;
    int         i;

    new_matrix = malloc(sizeof(uint32_t) * (len + 1)); // malloc da lista
    new_matrix[len] = 0;
    for(i = 0; i < len; i++)
        new_matrix[i] = build_block(matrix[i]); // adiciono os bits para a posição
    return(new_matrix);
}

// essa func pega o txt é converte ele em blocos de 4 bytes
uint32_t *convert_to_block(char *str)
{
    int  len;
    int     i;
    int     j;
    int     matrix_i;
    char    **matrix;

    i = 0;
    j = 0;
    matrix_i = 0;
    matrix = NULL;
    len = (strlen(str) + 3) / 4;
    matrix = malloc(sizeof(char *) * (len + 1));  // malloc o tamanho da lista
    matrix[len] = NULL;
    matrix[j] = calloc(5, sizeof(char)); // calloco a string
    // loop para adicionar os char para as posições na lista
    while (str[i])
    {
        if(matrix_i < 4)
            matrix[j][matrix_i++] = str[i++];
        else
        {
            matrix_i = 0;
            j++;
            matrix[j] = calloc(5, sizeof(char));
        } 
    }
    // caso o ultimo bloco termine prencher os 4bytes , preencho com ~
    if(matrix_i > 0 )
    {
        while (matrix_i < 4)
            matrix[j][matrix_i++] = '~';        
    }
    return(convert_to_32_bits(matrix, len));
}
