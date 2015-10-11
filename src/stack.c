/**
 * Stack Implementation
 *
 * @author socherbyc
 * @license GPL v2
 * @version 1.0
 */

#include <stack.h>

struct node {
  Element value;
  Node *next;
};

struct stack {
  Node *head;
  size_t length;
};

/*
 |--------------------------------------------------------------------------
 | Invisible
 |--------------------------------------------------------------------------
 */

static Stack* _create_stack_from_range_step(Stack *stack, int index, int end) {
  if (index < end) {
    stack_push(stack, index);
    return _create_stack_from_range_step(stack, index + 1, end);
  }
  return stack;
}

static void _free_nodes(Node *node) {
  if (node != NULL) {
    Node *tmp = node->next;
    free(node);
    _free_nodes(tmp);
  }
}

static Stack* _node_reverse(Node *node, Stack *stack) {
  if (node != NULL) {
    stack_push(stack, node->value);
    return _node_reverse(node->next, stack);
  }
  return stack;
}

static void _node_each(Node *node, int index, int (*f)(Element, int)) {
  if (node != NULL && f(node->value, index) != -1) {
    _node_each(node->next, index + 1, f);
  }
}

static Stack* _node_map(Node *node, int index, Element (*f)(Element, int), Stack *result) {
  Stack *reverse;
  if (node != NULL) {
    stack_push(result, f(node->value, index));
    return _node_map(node->next, index + 1, f, result);
  }
  reverse = stack_reverse(result);
  free_stack(result);
  return reverse;
}

static Stack* _node_filter(Node *node, int index, int (*f)(Element, int), Stack *result) {
  Stack *reverse;
  if (node != NULL) {
    if (f(node->value, index)) {
      stack_push(result, node->value);
    }
    return _node_filter(node->next, index + 1, f, result);
  }
  reverse = stack_reverse(result);
  free_stack(result);
  return reverse;
}

static Element _node_reduce(Node *node, int index, Element (*f) (Element, Element, int), Element result) {
  Element e;
  if (node != NULL) {
    e = f(result, node->value, index);
    return _node_reduce(node->next, index + 1, f, e);
  }
  return result;
}

static Element _node_search(Node *node, int index, int (*f)(Element, int), Element otherwise) {
  if (node != NULL) {
    if (f(node->value, index)) {
      return node->value;
    }
    return _node_search(node->next, index + 1, f, otherwise);
  }
  return otherwise;
}

static int _node_key_at(Node *node, int i, Element target) {
  if (node == NULL) {
    return -1;
  }
  if (node->value == target) {
    return i;
  }
  return _node_key_at(node->next, i + 1, target);
}

static Element _node_value_at(Node *node, int index) {
  if (index > 0) {
    return _node_value_at(node->next, index - 1);
  }
  return node->value;
}

static Stack* _node_clone(Node *node, Stack *copy) {
  Stack *reverse;
  if (node != NULL) {
    stack_push(copy, node->value);
    return _node_clone(node->next, copy);
  }
  reverse = stack_reverse(copy);
  free_stack(copy);
  return reverse;
}

/*
 |--------------------------------------------------------------------------
 | Visible
 |--------------------------------------------------------------------------
 */

Stack* create_stack(void) {
  Stack *stack = (Stack*) malloc(sizeof(Stack));
  stack->head = NULL;
  stack->length = 0;
  return stack;
}

Stack* create_stack_from_range(int start, int end) {
  Stack *stack = create_stack();
  return _create_stack_from_range_step(stack, start, end);
}

void free_stack(Stack *stack) {
  if (stack != NULL) {
    _free_nodes(stack->head);
    free(stack);
  }
}

void stack_push(Stack *stack, Element e) {
  Node *node = (Node*) malloc(sizeof(Node));
  node->value = e;
  node->next = stack->head;
  stack->head = node;
  stack->length++;
}

Element stack_pop(Stack *stack) {
  Element e;
  Node *node;
  if (!stack_empty(stack)) {
    node = stack->head;
    stack->head = node->next;
    stack->length--;
    e = node->value;
    free(node);
    return e;
  }
  return 0;
}

int stack_empty(Stack *stack) {
  return stack->head == NULL;
}

Stack* stack_reverse(Stack *stack) {
  Stack *copy = create_stack();
  return _node_reverse(stack->head, copy);
}

void stack_each(Stack *stack, int (*f)(Element, int)) {
  return _node_each(stack->head, 0, f);
}

Stack* stack_map(Stack *stack, Element (*f)(Element, int)) {
  Stack *copy = create_stack();
  return _node_map(stack->head, 0, f, copy);
}

Stack* stack_filter(Stack *stack, int (*f)(Element, int)) {
  Stack *copy = create_stack();
  return _node_filter(stack->head, 0, f, copy);
}

Element stack_reduce(Stack *stack, Element (*f) (Element, Element, int), Element first) {
  return _node_reduce(stack->head, 0, f, first);
}

Element stack_search(Stack *stack, int (*f)(Element, int), Element otherwise)
{
  return _node_search(stack->head, 0, f, otherwise);
}

int stack_key_at(Stack *stack, Element target) {
  return _node_key_at(stack->head, 0, target);
}

Element stack_value_at(Stack *stack, int index, Element otherwise) {
  if (index >= stack->length) {
    return otherwise;
  }
  return _node_value_at(stack->head, index);
}

Stack* stack_remove_by_value(Stack *stack, Element value) {
  // closure style
  int element_not_equal_value(Element a, int index) {
    return a != value;
  }
  return stack_filter(stack, element_not_equal_value);
}

Stack* stack_clone(Stack *stack) {
  Stack *copy = create_stack();
  return _node_clone(stack->head, copy);
}

size_t stack_length(Stack *stack) {
  return stack->length;
}