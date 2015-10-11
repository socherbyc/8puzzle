/**
 * Bitset Structure
 *
 * @author socherbyc
 * @license GPL v2
 * @version 1.0
 */

#ifndef BITSET_H_
#define BITSET_H_

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bisset Bitset;

// se o tamanho disto for diferente de 1 byte,
// create_bitset_from_bits e bitset_set_all
// deixam de funcionar
typedef uint8_t Byte;
extern const int LENGHT_BYTE;
extern const int BYTE_BIT;
extern const int ALL_BYTE;

/*
 |--------------------------------------------------------------------------
 | Visible
 |--------------------------------------------------------------------------
 */

Bitset* create_bitset(size_t length);

Bitset* create_bitset_from_bits(Byte *bytes, size_t length);

Bitset* create_bitset_from_str(char *str);

void free_bitset(Bitset *bitset);

int bitset_count(Bitset *bitset);

size_t bitset_length(Bitset *bitset);

int bitset_test(Bitset *bitset, int position);

int bitset_any(Bitset *bitset);

int bitset_none(Bitset *bitset);

int bitset_all(Bitset *bitset);

void bitset_set(Bitset *bitset, int position);

void bitset_set_with(Bitset *bitset, int position, int value);

void bitset_set_all(Bitset *bitset, void* value, size_t length);

void bitset_set_all_true(Bitset *bitset);

void bitset_reset(Bitset *bitset, int position);

void bitset_reset_all(Bitset *bitset);

void bitset_flip(Bitset *bitset, int position);

void bitset_flip_all(Bitset *bitset);

char* bitset_to_str(Bitset *bitset);

int bitset_count_part(Bitset *bitset, int start, int end);

int bitset_nth_bit_true(Bitset *bitset, int order);

#endif