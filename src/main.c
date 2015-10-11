/**
 * Main Function
 *
 * @author socherbyc
 * @license GPL v2
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <puzzle.h>

typedef struct puzzleTest {
  int steps;
  int *data;
} PuzzleTest;

void printf_steps(int expected, int value) {
  printf("%s - ", (expected == value)? "✔" : "✘");
  (expected < 0)? printf("∞") : printf("%d", expected);
  printf("/");
  (value < 0)? printf("∞") : printf("%d", value);
  printf(" steps\n");
}

void test(Puzzle *solution, PuzzleTest *puzzleTests, int remnant) {
  if (remnant > 0) {
    int steps;
    Puzzle *puzzle = create_puzzle((*puzzleTests).data, 3, 3);

    steps = puzzle_solve(puzzle, solution);
    printf_steps((*puzzleTests).steps, steps);

    return test(solution, puzzleTests + 1, remnant - 1);
  }
}

int main() {

  Puzzle *solution = create_puzzle((int[]) {
    1, 2, 3,
    8, 0, 4,
    7, 6, 5
  }, 3, 3);

  PuzzleTest puzzleTests[] = {
    {
      .steps = 1,
      .data = (int[]) {
        1, 2, 3,
        8, 4, 0,
        7, 6, 5
      }
    },
    {
      .steps = 2,
      .data = (int[]) {
        1, 2, 3,
        8, 4, 5,
        7, 6, 0
      }
    },
    {
      .steps = 3,
      .data = (int[]) {
        1, 2, 3,
        8, 6, 0,
        7, 5, 4
      }
    },
    {
      .steps = 4,
      .data = (int[]) {
        2, 8, 3,
        1, 0, 4,
        7, 6, 5
      }
    },
    {
      .steps = 6,
      .data = (int[]) {
        1, 3, 4,
        8, 0, 5,
        7, 2, 6
      }
    },
    {
      .steps = 8,
      .data = (int[]) {
        0, 1, 2,
        7, 8, 3,
        6, 5, 4
      }
    },
    {
      .steps = 14,
      .data = (int[]) {
        2, 3, 1,
        7, 0, 8,
        6, 5, 4
      }
    },
    {
      .steps = 16,
      .data = (int[]) {
        2, 3, 1,
        8, 0, 4,
        7, 6, 5
      }
    },
    {
      .steps = 27,
      .data = (int[]) {
        6, 5, 7,
        4, 8, 0,
        2, 3, 1
      }
    },
    {
      .steps = 28,
      .data = (int[]) {
        8, 7, 6,
        1, 0, 5,
        2, 3, 4
      }
    },
    {
      .steps = 29,
      .data = (int[]) {
        5, 4, 7,
        2, 6, 8,
        3, 0, 1
      }
    },
    {
      .steps = 30,
      .data = (int[]) {
        0, 8, 7,
        2, 1, 6,
        3, 4, 5
      }
    },
    {
      .steps = 30,
      .data = (int[]) {
        6, 5, 7,
        2, 0, 8,
        3, 4, 1
      }
    },
    {
      .steps = 30,
      .data = (int[]) {
        5, 6, 7,
        4, 0, 8,
        3, 2, 1
      }
    },
    {
      .steps = 30,
      .data = (int[]) {
        5, 4, 3,
        6, 1, 2,
        7, 8, 0
      }
    },
    {
      .steps = -1,
      .data = (int[]) {
        1, 2, 3,
        7, 0, 4,
        8, 6, 5
      }
    },
    {
      .steps = -1,
      .data = (int[]) {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
      }
    },
    {
      .steps = -1,
      .data = (int[]) {
        5, 4, 7,
        6, 1, 2,
        3, 8, 0
      }
    },
    {
      .steps = -1,
      .data = (int[]) {
        5, 2, 0,
        7, 4, 1,
        8, 6, 3
      }
    },
    {
      .steps = -1,
      .data = (int[]) {
        1, 2, 3,
        4, 5, 6,
        7, 8, 0
      }
    },
  };

  test(solution, puzzleTests, sizeof(puzzleTests) / sizeof(PuzzleTest));
  return 0;
}