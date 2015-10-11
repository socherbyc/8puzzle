#ifndef FACTORADIC_H
#define FACTORADIC_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <bitset.h>

/*
 |--------------------------------------------------------------------------
 | Visible
 |--------------------------------------------------------------------------
 */

/**
 * More information in https://en.wikipedia.org/wiki/Factorial_number_system
 * @example:
 *   463(10) ->
 *     463 ÷ 1 = 463, remainder 0
 *     463 ÷ 2 = 231, remainder 1
 *     231 ÷ 3 = 77, remainder  0
 *     77 ÷ 4 = 19, remainder   1
 *     19 ÷ 5 = 3, remainder    4
 *     3 ÷ 6 = 0, remainder     3
 *   -> 463(10) = 341010(!)
 *
 * @param  number
 * @param  length  pass -1 if you don't know
 * @return factoradic
 */
int* int_to_factoradic(int number, int length);

/**
 * More information in https://en.wikipedia.org/wiki/Factorial_number_system
 * @example:
 *   341010(!) =
 *     3×5! + 4×4! + 1×3! + 0×2! + 1×1! + 0×0! =
 *     ((((3×5 + 4)×4 + 1)×3 + 0)×2 + 1)×1 + 0 =
 *     363(10)
 * @param  data    factoradic
 * @param  length  length of factoradic
 * @return number
 */ 
int factoradic_to_int(int *data, int length);

/**
 * Lehmer Code.
 * More information in https://en.wikipedia.org/wiki/Factorial_number_system
 * @example:
 *                              [1]         [3]   [2] [0] (permutatin)
 *                            (0 1 2 3) (0 2 3) (0 2) (0)  |
 *                               1º          2º    1º  0º  V
 *   (1,3,2,0) (permutation) =   1           2     1   0  (!)
 *
 * @param  data    permutation
 * @param  length  length of permutation
 * @return factoradic of permutation
 */
int* permutation_to_factoradic(int *data, int length);

/**
 * More information in https://en.wikipedia.org/wiki/Factorial_number_system
 * @example:
 *                1           2     1   0  (!)
 *                |           |     |   |    |
 *             (0 1 2 3) (0 2 3) (0 2) (0)   V
 *   1210(!) = (  1,          3,    2,  0) (permutation)
 *
 * @param data  permutation
 * @param length  length of permutation
 * @return factoradic of permutation
 */
int* factoradic_to_permutation(int *data, int length);

/**
 * More information in https://en.wikipedia.org/wiki/Factorial
 * @example:
 *   9! = 9×8×7×6×5×4×3×2×1
 *   8! =   8×7×6×5×4×3×2×1
 *   7! =     7×6×5×4×3×2×1
 *   6! =       6×5×4×3×2×1
 *   5! =         5×4×3×2×1
 *   4! =           4×3×2×1
 *   3! =             3×2×1
 *   2! =               2×1
 *   1! =                 1
 *   0! =                 1
 *
 * @param  num
 * @return factorial
 */
uint64_t factorial(uint32_t num);

#endif