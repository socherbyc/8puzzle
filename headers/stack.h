#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

typedef struct node Node;

typedef struct stack Stack;

typedef int Element;

/*
 |--------------------------------------------------------------------------
 | Visible
 |--------------------------------------------------------------------------
 */

Stack* create_stack(void);

Stack* create_stack_from_range(int start, int end);

void free_stack(Stack *stack);

void stack_push(Stack *stack, Element e);

Element stack_pop(Stack *stack);

int stack_empty(Stack *stack);

Stack* stack_reverse(Stack *stack);

void stack_each(Stack *stack, int (*f)(Element, int));

Stack* stack_map(Stack *stack, Element (*f)(Element, int));

Stack* stack_filter(Stack *stack, int (*f)(Element, int));

Element stack_reduce(Stack *stack, Element (*f) (Element, Element, int), Element first);

Element stack_search(Stack *stack, int (*f)(Element, int), Element otherwise);

int stack_key_at(Stack *stack, Element target);

Element stack_value_at(Stack *stack, int index, Element otherwise);

Stack* stack_remove_by_value(Stack *stack, Element value);

Stack* stack_clone(Stack *stack);

size_t stack_length(Stack *stack);

#endif