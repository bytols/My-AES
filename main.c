#include "MyAES.h"


void convert_to_32_bits()
{
    
}
uint32_t **convert_to_block(char *str)
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
    matrix[j] = calloc(sizeof(char), 5);
    while (str[i])
    {
        if(matrix_i < 4)
            matrix[j][matrix_i++] = str[i++];
        else
        {
            matrix_i = 0;
            j++;
            matrix[j] = calloc(sizeof(char), 5);
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
    return(matrix);
}

int main(int argc, char *argv[])
{
    char **matrix;
    (void) argc;

    matrix = convert_to_block(argv[1]);
    (void) matrix;
    return (0);
}