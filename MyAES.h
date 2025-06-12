#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdint.h>

uint32_t    *convert_to_block(char *str);
uint32_t    *convert_to_32_bits(char **matrix, int len);
void        print_binary(uint32_t num);
uint32_t    build_block(char *bloco_de_4);
uint32_t    build_block_key(char *str);
void        permutacao(uint32_t *matrix, int len, uint32_t key);
void        sbox(uint32_t *matrix, int len, uint32_t key);

#endif