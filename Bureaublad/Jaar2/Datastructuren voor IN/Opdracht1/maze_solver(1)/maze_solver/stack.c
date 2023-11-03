#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int stack_empty(const struct stack *s);

struct stack
{
    int top;
    size_t capacity;
    int *array;
    int num_pops;
    int num_push;
    long unsigned int stack_variable_memory;
};

struct stack *stack_init(size_t capacity)
{
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    if (stack == NULL) {
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    stack->num_pops = 0;
    stack->num_push = 0;
    stack->stack_variable_memory = 5;
    return stack;
}

void allocate_extra_mem(struct stack *s)
{
    s->array = (int *)realloc(s->array, s->stack_variable_memory * sizeof(int));
    s = (struct stack *)realloc(s, s->stack_variable_memory * sizeof(struct stack));
    s->stack_variable_memory += 5;
    s->capacity += 5;
}

void stack_cleanup(struct stack *s)
{
    free(s->array);
    free(s);
}

void stack_stats(const struct stack *s)
{
    printf("Number of pushes: %d\n", s->num_push);
    printf("Number of pops: %d\n", s->num_pops);
    printf("Max Elements: %ld\n", s->capacity);
}

int stack_full(struct stack *s)
{
    if (s == NULL)
    {
        return -1;
    }
    if(s->capacity == 0) {
        return -1;
    }
    // Valid? Assumes only when first entry top = -1
    // Zijn er meer inputs dat bij de start een error kan veroorzaken buiten NULL?
    if (s->top == -1)
    {
        return 0;
    }
    if (s->capacity == 1)
    {
        return 1;
    }
    return s->top == (int)s->capacity - 1;
}

int stack_push(struct stack *s, int c)
{
    int result = stack_full(s);
    if (result == 1)
    {
        allocate_extra_mem(s);
    }
    if (result == -1){
        return 1;
    }
    s->top++;
    s->array[s->top] = c;
    s->num_push++;

    return 0;
}

int stack_pop(struct stack *s)
{
    if (stack_empty(s))
    {
        return -1;
    }
    s->num_pops++;
    return s->array[s->top--];
}

int stack_peek(const struct stack *s)
{
    if (stack_empty(s))
    {
        return -1;
    }
    return s->array[s->top];
}

int stack_empty(const struct stack *s)
{
    if (s == NULL)
    {
        return -1;
    }
    return s->top == -1;
}

size_t stack_size(const struct stack *s)
{
    return s->capacity;
}
