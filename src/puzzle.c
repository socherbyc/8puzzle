#include <puzzle.h>

struct puzzle {
  int *data;
  int voidPosition;
  int width;
  int height;
};

/*
 |--------------------------------------------------------------------------
 | Invisible
 |--------------------------------------------------------------------------
 */

static void _swap_data(int *a, int *b) {
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

static int _puzzle_solve_single(Element e, Stack *result, Bitset *old, int solutionZipped, int width, int height) {
    Puzzle *puzzle, *tmp;
    int zipped;

    if (e == solutionZipped) {
      return 1;
    }

    if (bitset_test(old, e)) {
      return 0;
    }
    bitset_set(old, e);

    puzzle = puzzle_unzip(e, width, height);

    tmp = puzzle_left(puzzle);
    if (tmp) {
      zipped = puzzle_zip(tmp);
      stack_push(result, zipped);
      free_puzzle(tmp);
    }

    tmp = puzzle_right(puzzle);
    if (tmp) {
      zipped = puzzle_zip(tmp);
      stack_push(result, zipped);
      free_puzzle(tmp);
    }

    tmp = puzzle_up(puzzle);
    if (tmp) {
      zipped = puzzle_zip(tmp);
      stack_push(result, zipped);
      free_puzzle(tmp);
    }

    tmp = puzzle_down(puzzle);
    if (tmp) {
      zipped = puzzle_zip(tmp);
      stack_push(result, zipped);
      free_puzzle(tmp);
    }

    free_puzzle(puzzle);

    return 0;
}

static int _puzzle_solve(Stack *edge, int steps, Bitset *old, int solutionZipped, int width, int height) {
  Stack *result = create_stack();
  Element target = 0;

  int search(Element e, int index) {
    return _puzzle_solve_single(e, result, old, solutionZipped, width, height);
  };
  target = stack_search(edge, search, 0);

  free_stack(edge);
  if (target) {
    free_stack(result);
    return steps; // anwser
  }

  if (stack_empty(result)) {
    free_stack(result);
    return -1; // insoluble
  }

  return _puzzle_solve(result, steps + 1, old, solutionZipped, width, height);
}

/*
 |--------------------------------------------------------------------------
 | Creation & Destruction
 |--------------------------------------------------------------------------
 */

Puzzle* create_puzzle(int data[], int width, int height) {
  int i, length;
  Puzzle *puzzle = (Puzzle*) malloc(sizeof(Puzzle));
  if (puzzle == NULL) {
    return NULL;
  }

  puzzle->width = width;
  puzzle->height = height;
  puzzle->voidPosition = -1;

  length = width * height;
  puzzle->data = (int*) malloc(sizeof(int) * length);
  if (puzzle->data == NULL) {
    return NULL;
  }

  for (i = 0; i < length; i++) {
    puzzle->data[i] = data[i];
    if (data[i] == PUZZLE_VOID) {
      puzzle->voidPosition = i;
    }
  }

  // void position not found
  if (puzzle->voidPosition < 0) {
    return NULL;
  }
  return puzzle;
}

void free_puzzle(Puzzle *puzzle) {
  free(puzzle->data);
  free(puzzle);
}

/*
 |--------------------------------------------------------------------------
 | Movimentation
 |--------------------------------------------------------------------------
 */

int puzzle_can_go_to_left(Puzzle *puzzle) {
  return (puzzle->voidPosition % puzzle->width) >= 1;
}

int puzzle_can_go_to_right(Puzzle *puzzle) {
  return (puzzle->voidPosition % puzzle->width) < puzzle->width - 1;
}

int puzzle_can_go_to_up(Puzzle *puzzle) {
  return (puzzle->voidPosition - puzzle->width) >= 0;
}

int puzzle_can_go_to_down(Puzzle *puzzle) {
  int length = puzzle->width * puzzle->height;
  return (puzzle->voidPosition + puzzle->width) < length;
}

Puzzle* puzzle_left(Puzzle *puzzle) {
  Puzzle *copy;
  if (!puzzle_can_go_to_left(puzzle)) {
    return NULL;
  }

  copy = puzzle_clone(puzzle);

  _swap_data(
    copy->data + copy->voidPosition,
    copy->data + copy->voidPosition - 1
  );

  copy->voidPosition -= 1;
  return copy;
}

Puzzle* puzzle_right(Puzzle *puzzle) {
  Puzzle *copy;
  if (!puzzle_can_go_to_right(puzzle)) {
    return NULL;
  }

  copy = puzzle_clone(puzzle);

  _swap_data(
    copy->data + copy->voidPosition,
    copy->data + copy->voidPosition + 1
  );

  copy->voidPosition += 1;
  return copy;
}

Puzzle* puzzle_up(Puzzle *puzzle) {
  Puzzle *copy;
  if (!puzzle_can_go_to_up(puzzle)) {
    return NULL;
  }

  copy = puzzle_clone(puzzle);

  _swap_data(
    copy->data + copy->voidPosition,
    copy->data + copy->voidPosition - copy->width
  );

  copy->voidPosition -= copy->width;
  return copy;
}

Puzzle* puzzle_down(Puzzle *puzzle) {
  Puzzle *copy;
  if (!puzzle_can_go_to_down(puzzle)) {
    return NULL;
  }

  copy = puzzle_clone(puzzle);

  _swap_data(
    copy->data + copy->voidPosition,
    copy->data + copy->voidPosition + copy->width
  );

  copy->voidPosition += copy->width;
  return copy;
}

/*
 |--------------------------------------------------------------------------
 | Util
 |--------------------------------------------------------------------------
 */

void puzzle_printf(Puzzle *puzzle) {
  int i, j, tmp;

  for (i = 0; i < puzzle->width; i++) {
    if (i == 0) {
      printf("[");
    } else {
      printf(" ");
    }
    
    for (j = 0; j < puzzle->height; j++) {
      tmp = puzzle->data[i * puzzle->width + j];

      if (tmp == PUZZLE_VOID) {
        printf(" * ");
      } else {
        printf("%2d ", tmp);
      }
    }

    if (i + 1 == puzzle->width) {
      printf("]");
    }
    printf("\n");
  }

  printf("void: %d | width: %d | height: %d | encoded: %d \n",
    puzzle->voidPosition,
    puzzle->width,
    puzzle->height,
    puzzle_zip(puzzle)
  );
}

int puzzle_zip(Puzzle *puzzle) {
  int length, *factoradic, zipped;
  length = puzzle->width * puzzle->height;
  factoradic = permutation_to_factoradic(puzzle->data, length);
  zipped = factoradic_to_int(factoradic, length);
  free(factoradic);
  return zipped;
}

Puzzle* puzzle_unzip(int hash, int width, int height) {
  int length, *factoradic, *permutation;
  Puzzle *puzzle;

  length = width * height;

  factoradic = int_to_factoradic(hash, length);
  permutation = factoradic_to_permutation(factoradic, length);
  free(factoradic);

  puzzle = create_puzzle(permutation, width, height);
  free(permutation);

  return puzzle;
}

Puzzle* puzzle_clone(Puzzle *puzzle) {
  Puzzle *copy = create_puzzle(puzzle->data, puzzle->width, puzzle->height);
  return copy;
}

/*
 |--------------------------------------------------------------------------
 | Other
 |--------------------------------------------------------------------------
 */

int puzzle_solve(Puzzle *puzzle, Puzzle *solution) {
  Stack *edge;
  int solutionZipped, zipped, steps;
  Bitset *old;

  edge = create_stack();
  solutionZipped = puzzle_zip(solution);
  old = create_bitset((int) factorial(puzzle->width * puzzle->height));
  zipped = puzzle_zip(puzzle);
  stack_push(edge, zipped);
  steps = _puzzle_solve(edge, 0, old, solutionZipped, puzzle->width, puzzle->height);
  return steps;
}