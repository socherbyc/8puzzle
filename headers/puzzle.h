/**
 * Puzzle Structure
 *
 * @author socherbyc
 * @license GPL v2
 * @version 1.0
 */

#ifndef PUZZLE_H_
#define PUZZLE_H_

#define PUZZLE_VOID 0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <bitset.h>
#include <stack.h>
#include <factoradic.h>

typedef struct puzzle Puzzle;

/*
 |--------------------------------------------------------------------------
 | Creation & Destruction
 |--------------------------------------------------------------------------
 */

/**
 * Create a instance of puzzle
 */
Puzzle* create_puzzle(int data[], int width, int height);

/**
 * Destroy a instance of puzzle
 */
void free_puzzle(Puzzle *puzzle);

/*
 |--------------------------------------------------------------------------
 | Movimentation
 |--------------------------------------------------------------------------
 */

/**
 * @return 1 if true
 */
int puzzle_can_go_to_left(Puzzle *puzzle);

/**
 * @return 1 if true
 */
int puzzle_can_go_to_right(Puzzle *puzzle);

/**
 * @return 1 if true
 */
int puzzle_can_go_to_up(Puzzle *puzzle);

/**
 * @return 1 if true
 */
int puzzle_can_go_to_down(Puzzle *puzzle);

/**
 * @return NULL on error
 */
Puzzle* puzzle_left(Puzzle *puzzle);

/**
 * @return NULL on error
 */
Puzzle* puzzle_right(Puzzle *puzzle);

/**
 * @return NULL on error
 */
Puzzle* puzzle_up(Puzzle *puzzle);

/**
 * @return NULL on error
 */
Puzzle* puzzle_down(Puzzle *puzzle);

/*
 |--------------------------------------------------------------------------
 | Util
 |--------------------------------------------------------------------------
 */

/**
 * formatted print of puzzle
 */
void puzzle_printf(Puzzle *puzzle);

/**
 * Compact puzzle to number
 */
int puzzle_zip(Puzzle *puzzle);

/**
 * Extract puzzle from number
 */
Puzzle* puzzle_unzip(int hash, int width, int height);

Puzzle* puzzle_clone(Puzzle *puzzle);

/*
 |--------------------------------------------------------------------------
 | Other
 |--------------------------------------------------------------------------
 */

/**
 * Return number of steps to finish game
 */
int puzzle_solve(Puzzle *puzzle, Puzzle *solution);

#endif