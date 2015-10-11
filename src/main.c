#include <stdio.h>
#include <stdlib.h>
#include <puzzle.h>
#include <stack.h>
#include <factoradic.h>

void run() {
  int dataSolution[] = {
    1, 2, 3,
    8, 0, 4,
    7, 6, 5
  };
  Puzzle *puzzle, *solution;
  solution = create_puzzle(dataSolution, 3, 3);

  int data1[] = {
    1, 2, 3,
    8, 4, 0,
    7, 6, 5
  };
  puzzle = create_puzzle(data1, 3, 3);
  printf("1 steps = %d\n", puzzle_solve(puzzle, solution));
  free_puzzle(puzzle);

  int data2[] = {
    1, 2, 3,
    8, 4, 5,
    7, 6, 0
  };
  puzzle = create_puzzle(data2, 3, 3);
  printf("2 steps = %d\n", puzzle_solve(puzzle, solution));
  free_puzzle(puzzle);

  int data3[] = {
    1, 2, 3,
    8, 6, 0,
    7, 5, 4
  };
  puzzle = create_puzzle(data3, 3, 3);
  printf("3 steps = %d\n", puzzle_solve(puzzle, solution));
  free_puzzle(puzzle);

  int data6[] = {
    1, 3, 4,
    8, 0, 5,
    7, 2, 6
  };
  puzzle = create_puzzle(data6, 3, 3);
  printf("6 steps = %d\n", puzzle_solve(puzzle, solution));
  free_puzzle(puzzle);

  int data14[] = {
    2, 3, 1,
    7, 0, 8,
    6, 5, 4
  };
  puzzle = create_puzzle(data14, 3, 3);
  printf("14 steps = %d\n", puzzle_solve(puzzle, solution));
  free_puzzle(puzzle);

  int data16[] = {
    2, 3, 1,
    8, 0, 4,
    7, 6, 5
  };
  puzzle = create_puzzle(data16, 3, 3);
  printf("16 steps = %d\n", puzzle_solve(puzzle, solution));
  free_puzzle(puzzle);

  int data28[] = {
    8, 7, 6,
    1, 0, 5,
    2, 3, 4
  };
  puzzle = create_puzzle(data28, 3, 3);
  printf("28 steps = %d\n", puzzle_solve(puzzle, solution));
  free_puzzle(puzzle);

  int dataInsoluble[] = {
    1, 2, 3,
    7, 0, 4,
    8, 6, 5
  };
  puzzle = create_puzzle(dataInsoluble, 3, 3);
  printf("Insoluble steps = %d\n", puzzle_solve(puzzle, solution));
  free_puzzle(puzzle);

  free_puzzle(solution);
}

int main() {
  run();
  return 0;
}