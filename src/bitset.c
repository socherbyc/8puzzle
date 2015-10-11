/**
 * Bitset Implementation
 *
 * @author socherbyc
 * @license GPL v2
 * @version 1.0
 */

#include <bitset.h>

struct bisset {
  Byte *bytes;
  size_t length;
};

const int LENGHT_BYTE = sizeof(Byte);
const int BYTE_BIT = sizeof(Byte) << 3;
const int ALL_BYTE = ~(~0 >> (sizeof(Byte) << 3) << (sizeof(Byte) << 3));

/*
 |--------------------------------------------------------------------------
 | Invisible
 |--------------------------------------------------------------------------
 */

static int _byte_count_step(Byte byte, int count) {
  if (!byte) {
    return count;
  }
  return _byte_count_step(byte & (byte - 1), count + 1);
}

static int _byte_count(Byte byte) {
  return _byte_count_step(byte, 0);
}

static int _bytes_count_step(Byte *bytes, size_t length, int count) {
  if (length > 1) {
    return _bytes_count_step(bytes + 1, length - 1, count + _byte_count(*bytes));
  }
  return count;
}

static int bytes_count(Byte *bytes, size_t length) {
  return _bytes_count_step(bytes, length, 0);
}

static int _bytes_any(Byte *bytes, size_t length) {
  if (*bytes) {
    return 1;
  }
  if (((length + BYTE_BIT) / BYTE_BIT) > 1) {
    return _bytes_any(bytes + 1, length - 1);
  }
  return 0;
}

static int _bytes_all(Byte *bytes, size_t length) {
  if (*bytes != ALL_BYTE) {
    return 0;
  }
  if (((length + BYTE_BIT) / BYTE_BIT) > 1) {
    return _bytes_all(bytes + 1, length - 1);
  }
  return 1;
}

static char* _bitset_to_str_step(Bitset *bitset, int index, char *str) {
  if (index >= 0) {
    *str = bitset_test(bitset, index) + '0';
    return _bitset_to_str_step(bitset, index - 1, str + 1);
  }
  *str = '\0';
  return str - bitset->length;
}

static void _bitset_set_all_true_step(Bitset *bitset, int index) {
  if (index < ((bitset->length + BYTE_BIT) / BYTE_BIT)) {
    bitset->bytes[index] = ALL_BYTE;
    _bitset_set_all_true_step(bitset, index + 1);
  }
}

static void _bitset_reset_all_step(Bitset *bitset, int index) {
  if (index < ((bitset->length + BYTE_BIT) / BYTE_BIT)) {
    bitset->bytes[index] = 0;
    _bitset_reset_all_step(bitset, index + 1);
  }
}

static void _bitset_flip_all_step(Bitset *bitset, int index) {
  if (index < ((bitset->length + BYTE_BIT) / BYTE_BIT)) {
    bitset->bytes[index] = ~bitset->bytes[index];
    return _bitset_flip_all_step(bitset, index + 1);
  }
}

static void _bitset_set_all_step(Bitset *bitset, uint8_t *bytes, size_t length, int index) {
  if (index < length / BYTE_BIT) {
    bitset->bytes[index] = bytes[index];
    _bitset_set_all_step(bitset, bytes, length, index + 1);
  } else if (index < ((length + BYTE_BIT) / BYTE_BIT)) {
    uint8_t masc = ~0 >> (length % BYTE_BIT) << (length % BYTE_BIT);
    bitset->bytes[index] &= masc;
    bitset->bytes[index] |= (bytes[index] & ~masc);
  }
}

static Bitset* _str_to_bitset_step(Bitset *bitset, char* str, int count) {
  if (*str) {
    bitset_set_with(bitset, count, *str & 1);
    return _str_to_bitset_step(bitset, str + 1, count - 1);
  }
  return bitset;
}

static int _bitset_count_part_step(Bitset *bitset, int index, int end, int accumulator) {
  if (index <= end) {
    int nextAccumulator = accumulator + bitset_test(bitset, index);
    return _bitset_count_part_step(bitset, index + 1, end, nextAccumulator);
  }
  return accumulator;
}

static int _bytes_nth_bit_true_step(Bitset *bitset, int order, int accumulator, int index) {
  if (order == accumulator) {
    return index - 1;
  }
  if (index < bitset_length(bitset)) {
    while (!bitset_test(bitset, index) && index < bitset_length(bitset)) {
      ++index;
    }
    return _bytes_nth_bit_true_step(bitset, order,
      accumulator + bitset_test(bitset, index), index + 1);
  }
  if (bitset_test(bitset, index - 1)) {
    return accumulator;
  }
  return -1;
}

/*
 |--------------------------------------------------------------------------
 | Visible
 |--------------------------------------------------------------------------
 */

Bitset* create_bitset(size_t length) {
  Bitset *bitset = (Bitset*) malloc(sizeof(Bitset));
  bitset->length = length;
  bitset->bytes = (Byte*) calloc((length / BYTE_BIT) + 1, LENGHT_BYTE);
  return bitset;
}

Bitset* create_bitset_from_bits(Byte *bytes, size_t length) {
  Bitset *bitset = create_bitset(length);
  bitset_set_all(bitset, bytes, length);
  return bitset;
}

Bitset* create_bitset_from_str(char *str) {
  int length = strlen(str);
  Bitset *bitset = create_bitset(length);
  return _str_to_bitset_step(bitset, str, length - 1);
}

void free_bitset(Bitset *bitset) {
  if (bitset != NULL) {
    if (bitset->bytes != NULL) {
      free(bitset->bytes);
    }
    free(bitset);
  }
}

int bitset_count(Bitset *bitset) {
  Byte masc = ~(~0 >> (bitset->length % BYTE_BIT) << (bitset->length % BYTE_BIT));
  bitset->bytes[bitset->length / BYTE_BIT] &= masc;
  return bytes_count(bitset->bytes, bitset->length);
}

inline size_t bitset_length(Bitset *bitset) {
  return bitset->length;
}

inline int bitset_test(Bitset *bitset, int position) {
  if (position >= 0 && position < bitset->length) {
    return !!(bitset->bytes[position / BYTE_BIT] & (1 << (position % BYTE_BIT)));
  }
  return 0;
}

int bitset_any(Bitset *bitset) {
  Byte masc = ~(~0 >> (bitset->length % BYTE_BIT) << (bitset->length % BYTE_BIT));
  bitset->bytes[bitset->length / BYTE_BIT] &= masc;
  return !!_bytes_any(bitset->bytes, bitset->length);
}

int bitset_none(Bitset *bitset) {
  return !bitset_any(bitset);
}

int bitset_all(Bitset *bitset) {
  Byte masc = ~0 >> (bitset->length % BYTE_BIT) << (bitset->length % BYTE_BIT);
  bitset->bytes[bitset->length / BYTE_BIT] |= masc;
  return !!_bytes_all(bitset->bytes, bitset->length);
}

void bitset_set(Bitset *bitset, int position) {
  if (bitset->length > position) {
    bitset->bytes[position / BYTE_BIT] |= 1 << (position % BYTE_BIT);
  }
}

void bitset_set_with(Bitset *bitset, int position, int value) {
  if (value) {
    bitset_set(bitset, position);
  } else {
    bitset_reset(bitset, position);
  }
}

void bitset_set_all(Bitset *bitset, void* value, size_t length) {
  uint8_t *bytes = (uint8_t*) value;
  _bitset_set_all_step(bitset, bytes, length, 0);
}

void bitset_set_all_true(Bitset *bitset) {
  _bitset_set_all_true_step(bitset, 0);
}

void bitset_reset(Bitset *bitset, int position) {
  if (bitset->length > position) {
    bitset->bytes[position / BYTE_BIT] &= ~(1 << (position % BYTE_BIT));
  }
}

void bitset_reset_all(Bitset *bitset) {
  _bitset_reset_all_step(bitset, 0);
}

void bitset_flip(Bitset *bitset, int position) {
  if (bitset->length > position) {
    bitset->bytes[position / BYTE_BIT] ^= 1 << (position % BYTE_BIT);
  }
}

void bitset_flip_all(Bitset *bitset) {
  _bitset_flip_all_step(bitset, 0);
}

char* bitset_to_str(Bitset *bitset) {
  char *str = (char*) malloc(sizeof(char) * (bitset->length + 1));
  return _bitset_to_str_step(bitset, bitset->length - 1, str);
}

int bitset_count_part(Bitset *bitset, int start, int end) {
  if (start >= 0 && start <= end && end < bitset_length(bitset)) {
    return _bitset_count_part_step(bitset, start, end, 0);
  }
  return -1;
}

int bitset_nth_bit_true(Bitset *bitset, int order) {
  if (order > 0 && order <= bitset_length(bitset)) {
    return _bytes_nth_bit_true_step(bitset, order, 0, 0);
  }
  return -1;
}