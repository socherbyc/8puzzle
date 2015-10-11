#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <bitset.h>

void assert_basic() {
  Bitset *bitset1, *bitset2, *bitset3;
  Byte data[] = {0b111};
  bitset1 = create_bitset(10);
  free_bitset(bitset1);

  bitset2 = create_bitset_from_bits(data, 3);
  free_bitset(bitset2);

  bitset3 = create_bitset_from_str("10101");
  free_bitset(bitset3);

  printf("✓ assert_basic\n");
}

void assert_count() {
  Bitset *bitset = create_bitset_from_str("1111");
  assert(bitset_count(bitset) == 4);

  bitset_flip_all(bitset);
  assert(bitset_count(bitset) == 0);

  bitset_set(bitset, 0);
  assert(bitset_count(bitset) == 1);

  bitset_set_all_true(bitset);
  assert(bitset_count(bitset) == 4);

  free_bitset(bitset);

  printf("✓ assert_count\n");
}

void assert_length() {
  Bitset *bitset1, *bitset2, *bitset3;
  Byte data[] = {0b00000111};

  bitset1 = create_bitset(11);
  assert(bitset_length(bitset1) == 11);
  free_bitset(bitset1);

  bitset2 = create_bitset_from_bits(data, 3);
  assert(bitset_length(bitset2) == 3);
  free_bitset(bitset2);

  bitset3 = create_bitset_from_str("11111");
  assert(bitset_length(bitset3) == 5);
  free_bitset(bitset3);

  printf("✓ assert_length\n");
}

void assert_test() {
  Bitset *bitset1, *bitset2;
  int i;

  bitset1 = create_bitset(10);
  for (i = 0; i < 10; i++) {
    assert(bitset_test(bitset1, 0) == 0);
  }

  bitset_set_all_true(bitset1);

  for (i = 0; i < 10; i++) {
    assert(bitset_test(bitset1, 0) == 1);
  }

  bitset2 = create_bitset_from_str("101");
  assert(bitset_test(bitset2, 0) == 1);
  assert(bitset_test(bitset2, 1) == 0);
  assert(bitset_test(bitset2, 2) == 1);

  bitset_flip_all(bitset2);

  assert(bitset_test(bitset2, 0) == 0);
  assert(bitset_test(bitset2, 1) == 1);
  assert(bitset_test(bitset2, 2) == 0);

  free_bitset(bitset1);
  free_bitset(bitset2);

  printf("✓ assert_test\n");
}

void assert_any() {
  int i;
  Bitset *bitset;

  bitset = create_bitset_from_str("01101");
  assert(bitset_any(bitset) != 0);

  bitset_reset_all(bitset);
  assert(bitset_any(bitset) == 0);

  bitset_flip_all(bitset);
  assert(bitset_any(bitset) != 0);

  for (i = 0; i < 5; i++) {
    bitset_set_with(bitset, i, 1);
  }
  assert(bitset_any(bitset) != 0);

  bitset_set_all_true(bitset);
  for (i = 0; i < 5; i++) {
    bitset_set_with(bitset, i, 0);
  }
  assert(bitset_any(bitset) == 0);

  free_bitset(bitset);
  printf("✓ assert_any\n");
}

void assert_none() {
  int i;
  Bitset *bitset;

  bitset = create_bitset_from_str("01101");
  assert(bitset_none(bitset) == 0);

  bitset_set_all_true(bitset);
  assert(bitset_none(bitset) == 0);

  bitset_flip_all(bitset);
  assert(bitset_none(bitset) != 0);

  for (i = 0; i < 5; i++) {
    bitset_set_with(bitset, i, 1);
  }
  assert(bitset_none(bitset) == 0);

  bitset_set_all_true(bitset);
  for (i = 0; i < 5; i++) {
    bitset_set_with(bitset, i, 0);
  }
  assert(bitset_none(bitset) != 0);

  free_bitset(bitset);
  printf("✓ assert_none\n");
}

void assert_all() {
  int i;
  Bitset *bitset;

  bitset = create_bitset_from_str("01101");
  assert(bitset_all(bitset) == 0);

  bitset_set_all_true(bitset);
  assert(bitset_all(bitset) != 0);

  bitset_flip_all(bitset);
  assert(bitset_all(bitset) == 0);

  for (i = 0; i < 5; i++) {
    bitset_set_with(bitset, i, 1);
  }
  assert(bitset_all(bitset) != 0);

  bitset_set_all_true(bitset);
  for (i = 0; i < 5; i++) {
    bitset_set_with(bitset, i, 0);
  }
  assert(bitset_all(bitset) == 0);

  free_bitset(bitset);
  printf("✓ assert_all\n");
}

void assert_set() {
  Bitset *bitset;
  bitset = create_bitset_from_str("01101");

  bitset_set(bitset, 0);
  assert(bitset_test(bitset, 0) != 0);
  assert(bitset_test(bitset, 1) == 0);
  assert(bitset_test(bitset, 2) != 0);
  assert(bitset_test(bitset, 3) != 0);
  assert(bitset_test(bitset, 4) == 0);

  bitset_set(bitset, 1);
  assert(bitset_test(bitset, 1) != 0);

  bitset_set(bitset, 2);
  assert(bitset_test(bitset, 2) != 0);

  bitset_set(bitset, 3);
  assert(bitset_test(bitset, 3) != 0);

  bitset_set(bitset, 4);
  assert(bitset_test(bitset, 4) != 0);

  free_bitset(bitset);
  printf("✓ assert_set\n");
}

void assert_set_with() {
  Bitset *bitset;
  bitset = create_bitset_from_str("01101");

  bitset_set_with(bitset, 0, 0);
  assert(bitset_test(bitset, 0) == 0);
  assert(bitset_test(bitset, 1) == 0);
  assert(bitset_test(bitset, 2) != 0);
  assert(bitset_test(bitset, 3) != 0);
  assert(bitset_test(bitset, 4) == 0);

  bitset_set_with(bitset, 0, 1);
  assert(bitset_test(bitset, 0) != 0);
  assert(bitset_test(bitset, 1) == 0);
  assert(bitset_test(bitset, 2) != 0);
  assert(bitset_test(bitset, 3) != 0);
  assert(bitset_test(bitset, 4) == 0);

  bitset_set_with(bitset, 1, 1);
  assert(bitset_test(bitset, 1) != 0);

  bitset_set_with(bitset, 2, 0);
  assert(bitset_test(bitset, 2) == 0);

  bitset_set_with(bitset, 3, 0);
  assert(bitset_test(bitset, 3) == 0);

  bitset_set_with(bitset, 4, 1);
  assert(bitset_test(bitset, 4) != 0);

  free_bitset(bitset);
  printf("✓ assert_set_with\n");
}

void assert_set_all() {
  uint8_t data[] = {0, 0};
  Bitset *bitset1, *bitset2;

  data[0] = 0b10010;
  bitset1 = create_bitset_from_str("01101");

  bitset_set_all(bitset1, data, 5);
  assert(bitset_test(bitset1, 0) == 0);
  assert(bitset_test(bitset1, 1) != 0);
  assert(bitset_test(bitset1, 2) == 0);
  assert(bitset_test(bitset1, 3) == 0);
  assert(bitset_test(bitset1, 4) != 0);

  data[0] = 0b11001100;
  data[1] = 0b10101010;
  bitset2 = create_bitset_from_str("01110000000000001110");

  bitset_set_all(bitset2, data, 15);
  assert(bitset_test(bitset2, 0) == 0);
  assert(bitset_test(bitset2, 1) == 0);
  assert(bitset_test(bitset2, 2) != 0);
  assert(bitset_test(bitset2, 3) != 0);
  assert(bitset_test(bitset2, 4) == 0);
  assert(bitset_test(bitset2, 5) == 0);
  assert(bitset_test(bitset2, 6) != 0);
  assert(bitset_test(bitset2, 7) != 0);
  assert(bitset_test(bitset2, 8) == 0);
  assert(bitset_test(bitset2, 9) != 0);
  assert(bitset_test(bitset2, 10) == 0);
  assert(bitset_test(bitset2, 11) != 0);
  assert(bitset_test(bitset2, 12) == 0);
  assert(bitset_test(bitset2, 13) != 0);
  assert(bitset_test(bitset2, 14) == 0);
  assert(bitset_test(bitset2, 15) == 0);
  assert(bitset_test(bitset2, 16) != 0);
  assert(bitset_test(bitset2, 17) != 0);
  assert(bitset_test(bitset2, 18) != 0);
  assert(bitset_test(bitset2, 19) == 0);

  free_bitset(bitset1);
  free_bitset(bitset2);
  printf("✓ assert_set_all\n");
}

void assert_set_all_true() {
  Bitset *bitset = create_bitset_from_str("01101");

  bitset_set_all_true(bitset);
  assert(bitset_test(bitset, 0) != 0);
  assert(bitset_test(bitset, 1) != 0);
  assert(bitset_test(bitset, 2) != 0);
  assert(bitset_test(bitset, 3) != 0);
  assert(bitset_test(bitset, 4) != 0);

  free_bitset(bitset);
  printf("✓ assert_set_all_true\n");
}

void assert_reset() {
  Bitset *bitset = create_bitset_from_str("01101");

  bitset_reset(bitset, 0);
  assert(bitset_test(bitset, 0) == 0);
  assert(bitset_test(bitset, 1) == 0);
  assert(bitset_test(bitset, 2) != 0);
  assert(bitset_test(bitset, 3) != 0);
  assert(bitset_test(bitset, 4) == 0);

  bitset_reset(bitset, 1);
  assert(bitset_test(bitset, 1) == 0);

  bitset_reset(bitset, 2);
  assert(bitset_test(bitset, 2) == 0);

  bitset_reset(bitset, 3);
  assert(bitset_test(bitset, 3) == 0);

  bitset_reset(bitset, 4);
  assert(bitset_test(bitset, 4) == 0);

  free_bitset(bitset);
  printf("✓ assert_reset\n");
}

void assert_reset_all() {
  Bitset *bitset = create_bitset_from_str("01101");

  bitset_reset_all(bitset);
  assert(bitset_test(bitset, 0) == 0);
  assert(bitset_test(bitset, 1) == 0);
  assert(bitset_test(bitset, 2) == 0);
  assert(bitset_test(bitset, 3) == 0);
  assert(bitset_test(bitset, 4) == 0);

  free_bitset(bitset);
  printf("✓ assert_reset_all\n");
}

void assert_flip() {
  Bitset *bitset = create_bitset_from_str("01101");

  bitset_flip(bitset, 0);
  assert(bitset_test(bitset, 0) == 0);
  assert(bitset_test(bitset, 1) == 0);
  assert(bitset_test(bitset, 2) != 0);
  assert(bitset_test(bitset, 3) != 0);
  assert(bitset_test(bitset, 4) == 0);

  bitset_flip(bitset, 1);
  assert(bitset_test(bitset, 1) != 0);

  bitset_flip(bitset, 2);
  assert(bitset_test(bitset, 2) == 0);

  bitset_flip(bitset, 3);
  assert(bitset_test(bitset, 3) == 0);

  bitset_flip(bitset, 4);
  assert(bitset_test(bitset, 4) != 0);

  free_bitset(bitset);
  printf("✓ assert_flip\n");
}

void assert_flip_all() {
  Bitset *bitset = create_bitset_from_str("01101");

  bitset_flip_all(bitset);
  assert(bitset_test(bitset, 0) == 0);
  assert(bitset_test(bitset, 1) != 0);
  assert(bitset_test(bitset, 2) == 0);
  assert(bitset_test(bitset, 3) == 0);
  assert(bitset_test(bitset, 4) != 0);

  free_bitset(bitset);
  printf("✓ assert_flip_all\n");
}

void assert_to_str() {
  Bitset *bitset = create_bitset_from_str("01101");

  assert(strcmp(bitset_to_str(bitset), "01101") == 0);

  bitset_set(bitset, 1);
  assert(strcmp(bitset_to_str(bitset), "01111") == 0);

  bitset_set_with(bitset, 0, 0);
  assert(strcmp(bitset_to_str(bitset), "01110") == 0);

  printf("✓ assert_to_str\n");
}

void assert_count_part() {
  Bitset *bitset = create_bitset_from_str("01101");
  assert(bitset_count_part(bitset, 1, 3) == 2);

  bitset_set_all_true(bitset);
  bitset_reset(bitset, 1);
  bitset_reset(bitset, 4);
  assert(bitset_count_part(bitset, 1, 3) == 2);

  bitset_reset_all(bitset);
  bitset_set(bitset, 0);
  bitset_set(bitset, 2);
  bitset_set(bitset, 3);
  assert(bitset_count_part(bitset, 1, 3) == 2);

  free_bitset(bitset);

  printf("✓ assert_count_part\n");
}

int main() {
  assert_basic();
  assert_count();
  assert_length();
  assert_test();
  assert_any();
  assert_none();
  assert_all();
  assert_set();
  assert_set_with();
  assert_set_all();
  assert_set_all_true();
  assert_reset();
  assert_reset_all();
  assert_flip();
  assert_flip_all();
  assert_to_str();
  assert_count_part();
  printf("\nfinish..\n");

  return 0;
}

/*

https://docs.docker.com/installation/ubuntulinux/
https://arthurleon.wordpress.com/2014/09/04/comecando-com-docker-eu-x-docker-x-rails/
http://internerd.blog.br/vagrant/docker/linux/2014/09/05/ambiente-dev-vagrant-docker.html

https://lucabolognese.wordpress.com/2013/01/04/functional-programming-in-c/
https://github.com/Snaipe/libcsptr

*/