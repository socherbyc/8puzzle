#include <factoradic.h>

/*
 |--------------------------------------------------------------------------
 | Invisible
 |--------------------------------------------------------------------------
 */

static int _order_factorial_step(int limit, int result, int order) {
  if (limit < result) {
    return order - 1;
  }
  return _order_factorial_step(limit, result * (order + 1), order + 1);
}

static int _order_factorial(int limit) {
  return _order_factorial_step(limit, 1, 1);
}

static int* _int_to_factoradic_step(int number, int *result, int length, int index) {
  if (number > 0) {
    result[length - index] = number % index;
    return _int_to_factoradic_step(number / index, result, length, index + 1);
  }
  return result;
}

static int _factoradic_to_int_step(int *data, int length, int prev) {
  int now = prev * length + *data;
  if (length <= 1) {
    return prev;
  }
  return _factoradic_to_int_step(data + 1, length - 1, now);
}

static int* _permutation_to_factoradic_step(int *data, int length, int index, int *result, Bitset* old) {
  if (index < length) {
    int count = bitset_count_part(old, 0, data[index] - 1);
    if (count < 0) count = 0;
    result[index] = count;
    bitset_reset(old, data[index]);
    return _permutation_to_factoradic_step(data, length, index + 1, result, old);
  }
  free_bitset(old);
  return result;
}

static int* _factoradic_to_permutation_step(int *data, int length, int *result, int index, Bitset *old) {
  if (index < length) {
    int nth = bitset_nth_bit_true(old, data[index] + 1);
    result[index] = nth;
    bitset_reset(old, nth);
    return _factoradic_to_permutation_step(data, length, result, index + 1, old);
  }
  free_bitset(old);
  return result;
}

static uint64_t _factorial_step(uint32_t num, uint32_t result) {
  if (num > 0) {
    return _factorial_step(num - 1, result * num);
  }
  return result;
}

/*
 |--------------------------------------------------------------------------
 | Visible
 |--------------------------------------------------------------------------
 */

int* int_to_factoradic(int number, int length) {
  int *result = (int*) calloc(length, sizeof(int));
  if (length == -1) {
    length = _order_factorial(number);
  }
  return _int_to_factoradic_step(number, result, length, 1);
} 

int factoradic_to_int(int *data, int length) {
  return _factoradic_to_int_step(data, length, 0);
}

int* permutation_to_factoradic(int *data, int length) {
  int *result = (int*) malloc(sizeof(int) * length);
  Bitset *bitset = create_bitset(length);
  bitset_set_all_true(bitset);
  return _permutation_to_factoradic_step(data, length, 0, result, bitset);
}

int* factoradic_to_permutation(int *data, int length) {
  int *result = (int*) malloc(sizeof(int) * length);
  Bitset *bitset = create_bitset(length);
  bitset_set_all_true(bitset);
  return _factoradic_to_permutation_step(data, length, result, 0, bitset);
}

uint64_t factorial(uint32_t num) {
  return _factorial_step(num, 1);
}