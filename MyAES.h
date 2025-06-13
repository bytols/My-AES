#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdint.h>
# include <fcntl.h>
# include <ctype.h>

typedef enum e_mode{
    CRYPT,
    DECRYPT,
} t_mode;

uint32_t    *convert_to_block(char *str);
uint32_t    *convert_to_32_bits(char **matrix, int len);
void        print_binary(uint32_t num);
uint32_t    build_block(char *bloco_de_4);
uint32_t    build_block_key(char *str);
void        permutacao(uint32_t *matrix, int len, uint32_t key);
void        sbox(uint32_t *matrix, int len, uint32_t key, t_mode mode);
uint32_t    derive_key(uint32_t key, int round);
uint32_t    *decrypt_derive_key(uint32_t key);
void        back_to_string(uint32_t *matrix, int len);
int hex_char_to_int(char c);
uint8_t* hex_string_to_bytes(const char* hex_str, size_t* out_len);
uint32_t *bytes_to_uint32_array(uint8_t* bytes, size_t byte_len, size_t *out_len);
void back_to_string_ascii(uint32_t *matrix, size_t len_blocks);

#endif