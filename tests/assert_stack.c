#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stack.h>

void assert_basic() {
  Stack *stack = create_stack();
  free_stack(stack);

  printf("✓ assert_basic\n");
}

void assert_push_pop() {
  Stack *stack = create_stack();

  stack_push(stack, 778);
  assert(stack_pop(stack) == 778);

  stack_push(stack, 945);
  stack_push(stack, 186);
  assert(stack_pop(stack) == 186);
  assert(stack_pop(stack) == 945);

  free_stack(stack);
  printf("✓ assert_push_pop\n");
}

void assert_empty() {
  Stack *stack = create_stack();
  assert(stack_empty(stack) == 1);

  stack_push(stack, 778);
  assert(stack_empty(stack) == 0);

  stack_pop(stack);
  assert(stack_empty(stack) == 1);

  free_stack(stack);
  printf("✓ assert_empty\n");
}

void assert_each() {
  int data[] = {456, 370, 316};
  Stack *stack = create_stack();
  stack_push(stack, 316);
  stack_push(stack, 370);
  stack_push(stack, 456);

  int test(Element e, int i) {
    assert(e == data[i]);
    return 0;
  }
  stack_each(stack, test);

  free_stack(stack);
  printf("✓ assert_each\n");
}

void assert_map() {
  Stack *stack = create_stack(), *stack2;
  stack_push(stack, 316);
  stack_push(stack, 370);
  stack_push(stack, 456);

  Element test(Element e, int i) {
    return e * (i + 1);
  }
  stack2 = stack_map(stack, test);

  assert(stack_pop(stack2) == 456);
  assert(stack_pop(stack2) == 370 * 2);
  assert(stack_pop(stack2) == 316 * 3);

  free_stack(stack);
  free_stack(stack2);
  printf("✓ assert_map\n");
}

void assert_filter() {
  Stack *stack = create_stack(), *stack2;
  stack_push(stack, 412);
  stack_push(stack, 584);
  stack_push(stack, 910);

  int test(Element e, int i) {
    return i <= 1;
  }
  stack2 = stack_filter(stack, test);
  assert(stack_pop(stack2) == 910);
  assert(stack_pop(stack2) == 584);
  assert(stack_empty(stack2));

  free_stack(stack);
  free_stack(stack2);
  printf("✓ assert_filter\n");
}

void assert_reduce() {
  Element result;
  Stack *stack = create_stack();
  stack_push(stack, 3);
  stack_push(stack, 5);
  stack_push(stack, 7);

  int test(Element a, Element b, int i) {
    return a + b * b;
  }
  result = stack_reduce(stack, test, 0);
  assert(result == 3*3 + 5*5 + 7*7);

  free_stack(stack);
  printf("✓ assert_reduce\n");
}

void assert_search() {
  Element result;
  Stack *stack = create_stack();
  stack_push(stack, 786);
  stack_push(stack, 518);
  stack_push(stack, 411);

  int test(Element e, int i) {
    return i > 0;
  }
  result = stack_search(stack, test, 0);
  assert(result == 518);

  free_stack(stack);
  printf("✓ assert_search\n");
}

void assert_key_at() {
  Stack *stack = create_stack();
  stack_push(stack, 613);
  stack_push(stack, 14);
  stack_push(stack, 5721);

  assert(stack_key_at(stack, 14) == 1);
  assert(stack_key_at(stack, 613) == 2);
  assert(stack_key_at(stack, 5721) == 0);

  free_stack(stack);
  printf("✓ assert_key_at\n");
}

void assert_value_at() {
  Stack *stack = create_stack();
  stack_push(stack, 613);
  stack_push(stack, 14);
  stack_push(stack, 5721);

  assert(stack_value_at(stack, 1, -1) == 14);
  assert(stack_value_at(stack, 0, -1) == 5721);
  assert(stack_value_at(stack, 2, -1) == 613);

  free_stack(stack);
  printf("✓ assert_value_at\n");
}

void assert_remove_by_value() {
  Stack *stack = create_stack(), *stack2;
  stack_push(stack, 613);
  stack_push(stack, 14);
  stack_push(stack, 5721);

  stack2 = stack_remove_by_value(stack, 14);
  assert(stack_pop(stack2) == 5721);
  assert(stack_pop(stack2) == 613);

  assert(stack_pop(stack) == 5721);
  assert(stack_pop(stack) == 14);
  assert(stack_pop(stack) == 613);

  free_stack(stack);
  free_stack(stack2);
  printf("✓ assert_remove_by_value\n");
}

void assert_length() {
  Stack *stack = create_stack();
  assert(stack_length(stack) == 0);

  stack_push(stack, 613);
  assert(stack_length(stack) == 1);

  stack_pop(stack);
  assert(stack_length(stack) == 0);

  stack_push(stack, 14);
  assert(stack_length(stack) == 1);
  stack_push(stack, 5721);
  assert(stack_length(stack) == 2);

  free_stack(stack);
  printf("✓ assert_length\n");
}

int main(void) {
  assert_basic();
  assert_push_pop();
  assert_empty();
  assert_each();
  assert_map();
  assert_filter();
  assert_reduce();
  assert_search();
  assert_key_at();
  assert_value_at();
  assert_remove_by_value();
  assert_length();

  return 0;
}