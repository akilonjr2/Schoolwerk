#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct queue
{
    int top;
    int bottom;
    int size;
    size_t capacity;
    int *array;
    int num_pops;
    int num_push;
};

int queue_variable_memory = 5;
int queue_empty(const struct queue *q);

struct queue *queue_init(size_t capacity)
{
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->capacity = capacity;
    queue->top = 0;
    queue->size = 0;
    queue->bottom = (int)capacity - 1;
    queue->array = (int *)malloc(queue->capacity * sizeof(int));
    return queue;
}

void queue_cleanup(struct queue *q)
{
    free(q->array);
    free(q);
}

void queue_stats(const struct queue *q)
{
    printf("stats: \n");
    printf("num_of_pushes: %d\n", q->num_push);
    printf("num_of_pops: %d\n", q->num_pops);
    printf("num_of_elem: %d\n", q->size);
}

int queue_full(struct queue *q)
{
    if (q == NULL)
    {
        return 1;
    }
    // Valid? Assumes only when first entry top = -1
    // Zijn er meer inputs dat bij de start een error kan veroorzaken buiten NULL?
    if (q->top == -1)
    {
        return 0;
    }
    if (q->capacity == 1)
    {
        return 1;
    }
    return q->top == (int)q->capacity - 1;
}

int queue_push(struct queue *q, int e)
{
    if (queue_full(q))
    {
        return 1;
    }
    q->bottom = (q->bottom + 1) % (int)q->capacity;
    q->array[q->bottom] = e;
    q->size = q->size + 1;
    q->num_push++;
    return 0;
}

int queue_pop(struct queue *q)
{
    if (queue_empty(q))
    {
        return -1;
    }
    int result = q->array[q->top];
    q->top = (q->top + 1) % (int)q->capacity;
    q->size = q->size - 1;
    q->num_pops++;
    return result;
}

int queue_peek(const struct queue *q)
{
    if (queue_empty(q)) {
        return -1;
    }
    return q->array[q->top];
}

int queue_empty(const struct queue *q)
{ 
    if (q == NULL)
    {
        return -1;
    }
    return (q->size == 0);
}

size_t queue_size(const struct queue *q)
{
    return q->capacity;
}
