#include "MyAES.h"

// converte um char HEX para valor numérico (0-15)
int hex_char_to_int(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return 10 + (c - 'a');
    if ('A' <= c && c <= 'F') return 10 + (c - 'A');
    return -1;
}

// converte string hex (ex: "48656C") para bytes
// retorna array mallocado e coloca tamanho em *out_len
uint8_t* hex_string_to_bytes(const char* hex_str, size_t* out_len) {
    size_t len = strlen(hex_str);
    if (len % 2 != 0) return NULL; // deve ter número par de chars

    *out_len = len / 2;
    uint8_t* bytes = malloc(*out_len);
    if (!bytes) return NULL;

    for (size_t i = 0; i < *out_len; i++) {
        int hi = hex_char_to_int(hex_str[2*i]);
        int lo = hex_char_to_int(hex_str[2*i + 1]);
        if (hi == -1 || lo == -1) {
            free(bytes);
            return NULL; // caractere inválido
        }
        bytes[i] = (hi << 4) | lo;
    }
    return bytes;
}

uint32_t *bytes_to_uint32_array(uint8_t* bytes, size_t byte_len, size_t *out_len) {
    *out_len = (byte_len + 3) / 4;
    uint32_t *arr = calloc(*out_len, sizeof(uint32_t));
    if (!arr) return NULL;

    for (size_t i = 0; i < byte_len; i++) {
        size_t idx = i / 4;
        int shift = 8 * (3 - (i % 4)); // big endian
        arr[idx] |= ((uint32_t)bytes[i]) << shift;
    }
    return arr;
}
