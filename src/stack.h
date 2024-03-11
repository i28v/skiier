#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct {
    void** data;
    size_t top;
    size_t size;
} stack;

void stack_init(stack* self, size_t starting_size);
void stack_delete(stack* self, int free_elements);
void stack_check_increase(stack* self);
void stack_check_decrease(stack* self);
void stack_push(stack* self, void* element);
void stack_pop(stack* self, int free_element);
void* stack_get(stack*self, size_t index);
void stack_remove(stack* self, size_t index, int free_element);
void stack_insert(stack* self, void* element, size_t index);

#endif /* STACK_H */
