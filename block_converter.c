#include "MyAES.h"

uint32_t build_block(char *bloco_de_4) {
    return (bloco_de_4[0] << 24) |
           (bloco_de_4[1] << 16) |
           (bloco_de_4[2] << 8)  |
           bloco_de_4[3];
}

uint32_t *convert_to_32_bits(char **matrix, int len)
{
    uint32_t    *new_matrix;
    int         i;

    new_matrix = malloc(sizeof(uint32_t) * (len + 1));
    new_matrix[len] = 0;
    for(i = 0; i < len; i++)
        new_matrix[i] = build_block(matrix[i]);
    return(new_matrix);
}
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
    printf("%d\n", len);
    matrix = malloc(sizeof(char *) * (len + 1));
    matrix[len] = NULL;
    matrix[j] = calloc(5, sizeof(char));
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
    if(matrix_i > 0 )
    {
        while (matrix_i < 4)
            matrix[j][matrix_i++] = '~';        
    }
    j = 0;
    while (matrix[j] != NULL)
    {
        printf("%s\n", matrix[j]);
        j++;
    }
    return(convert_to_32_bits(matrix, len));
}
