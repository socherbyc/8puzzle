#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <factoradic.h>

int* full_loop_test(int *permutation, int length) {
  int *factoradic, *factoradic2, index, *result;

  factoradic = permutation_to_factoradic(permutation, length);
  index = factoradic_to_int(factoradic, length);
  factoradic2 = int_to_factoradic(index, length);
  result = factoradic_to_permutation(factoradic2, length);
  free(factoradic);
  free(factoradic2);

  return result;
}

void assert_int_to_factoradic() {
  int *factoradic;

  factoradic = int_to_factoradic(17, 4);
  assert(factoradic[0] == 2);
  assert(factoradic[1] == 2);
  assert(factoradic[2] == 1);
  assert(factoradic[3] == 0);
  free(factoradic);

  factoradic = int_to_factoradic(23, 4);
  assert(factoradic[0] == 3);
  assert(factoradic[1] == 2);
  assert(factoradic[2] == 1);
  assert(factoradic[3] == 0);
  free(factoradic);

  factoradic = int_to_factoradic(24, 5);
  assert(factoradic[0] == 1);
  assert(factoradic[1] == 0);
  assert(factoradic[2] == 0);
  assert(factoradic[3] == 0);
  assert(factoradic[4] == 0);
  free(factoradic);

  printf("✓ assert_int_to_factoradic\n");
}

void assert_factoradic_to_int() {
  int data1[] = {2, 2, 1, 0},
      data2[] = {3, 2, 1, 0},
      data3[] = {1, 0, 0, 0, 0};

  assert(factoradic_to_int(data1, 4) == 17);
  assert(factoradic_to_int(data2, 4) == 23);
  assert(factoradic_to_int(data3, 5) == 24);

  printf("✓ assert_factoradic_to_int\n");
}

void assert_permutation_to_factoradic() {
  int *factoradic,
      permutation1[] = {2, 3, 1, 0},
      permutation2[] = {3, 2, 1, 0},
      permutation3[] = {1, 0, 2, 3, 4};

  factoradic = permutation_to_factoradic(permutation1, 4);
  assert(factoradic[0] == 2);
  assert(factoradic[1] == 2);
  assert(factoradic[2] == 1);
  assert(factoradic[3] == 0);
  free(factoradic);

  factoradic = permutation_to_factoradic(permutation2, 4);
  assert(factoradic[0] == 3);
  assert(factoradic[1] == 2);
  assert(factoradic[2] == 1);
  assert(factoradic[3] == 0);
  free(factoradic);

  factoradic = permutation_to_factoradic(permutation3, 5);
  assert(factoradic[0] == 1);
  assert(factoradic[1] == 0);
  assert(factoradic[2] == 0);
  assert(factoradic[3] == 0);
  assert(factoradic[4] == 0);
  free(factoradic);

  printf("✓ assert_permutation_to_factoradic\n");
}

void assert_factoradic_to_permutation() {
  int *permutation,
      factoradic1[] = {1, 0, 0, 0, 0},
      factoradic2[] = {2, 2, 1, 0},
      factoradic3[] = {3, 2, 1, 0};

  permutation = factoradic_to_permutation(factoradic1, 5);
  assert(permutation[0] == 1);
  assert(permutation[1] == 0);
  assert(permutation[2] == 2);
  assert(permutation[3] == 3);
  assert(permutation[4] == 4);
  free(permutation);

  permutation = factoradic_to_permutation(factoradic2, 4);
  assert(permutation[0] == 2);
  assert(permutation[1] == 3);
  assert(permutation[2] == 1);
  assert(permutation[3] == 0);
  free(permutation);

  permutation = factoradic_to_permutation(factoradic3, 4);
  assert(permutation[0] == 3);
  assert(permutation[1] == 2);
  assert(permutation[2] == 1);
  assert(permutation[3] == 0);
  free(permutation);

  printf("✓ assert_factoradic_to_permutation\n");
}

void assert_cross() {
  int *permutation, *permutation2;

  {
    permutation = (int*) malloc(sizeof(int) * 10);
    permutation[0] = 9;
    permutation[1] = 2;
    permutation[2] = 3;
    permutation[3] = 4;
    permutation[4] = 5;
    permutation[5] = 8;
    permutation[6] = 1;
    permutation[7] = 6;
    permutation[8] = 7;
    permutation[9] = 0;
    permutation2 = full_loop_test(permutation, 10);
    assert(permutation[0] == permutation2[0]);
    assert(permutation[1] == permutation2[1]);
    assert(permutation[2] == permutation2[2]);
    assert(permutation[3] == permutation2[3]);
    assert(permutation[4] == permutation2[4]);
    assert(permutation[5] == permutation2[5]);
    assert(permutation[6] == permutation2[6]);
    assert(permutation[7] == permutation2[7]);
    assert(permutation[8] == permutation2[8]);
    assert(permutation[9] == permutation2[9]);
    free(permutation);
    free(permutation2);
  }

  printf("✓ assert_cross\n");
}

int main(void) {
  assert_int_to_factoradic();
  assert_factoradic_to_int();
  assert_permutation_to_factoradic();
  assert_factoradic_to_permutation();
  assert_cross();

  return 0;
}