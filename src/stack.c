#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stack_init(stack* self, size_t starting_size)
{
    self->size = starting_size;
    self->top = 0;
    self->data = malloc(sizeof(void*) * self->size);
}

void stack_delete(stack* self, int free_elements)
{
    if(free_elements) {
        for(size_t i = 0; i < self->top; i++) {
            free(self->data[i]);
            self->data[i] = NULL;
        }
    }
    free(self->data);
    self->data = NULL;
    self->top = 0;
    self->size = 0;
}

void stack_check_increase(stack* self)
{
    if(self->top == self->size) {
        self->size *= 2;
        void** new_ptr = realloc(self->data, sizeof(void*) * self->size);
        self->data = new_ptr;
    }
}

void stack_check_decrease(stack* self)
{
    if(self->top == self->size / 4) {
        self->size /= 2;
        void** new_ptr = realloc(self->data, sizeof(void*) * self->size);
        self->data = new_ptr;
    }
}

void stack_push(stack* self, void* element)
{
    self->data[self->top] = element;
    self->top++;
    stack_check_increase(self);
}

void stack_pop(stack* self, int free_element)
{
    if(self->top != 0) {
        if(free_element) {
            free(self->data[self->top-1]);
        }
        self->data[self->top-1] = NULL;
        self->top--;
        stack_check_decrease(self);
    }
}

void* stack_get(stack*self, size_t index)
{
    void* ptr = self->data[index];
    return ptr;
}

void stack_remove(stack* self, size_t index, int free_element)
{
    if(self->top != 0) {
        if(free_element) {
            free(self->data[index]);
        }
        self->data[index] = NULL;
        for(int i = index; i < self->top - 1; i++) {
            self->data[i] = self->data[i+1];
        }
        self->data[self->top-1] = NULL;
        self->top--;
        stack_check_decrease(self);
    }
}

void stack_insert(stack* self, void* element, size_t index)
{
    for(int i = self->top; i > index; i--) {
        self->data[i] = self->data[i-1];
    }
    self->data[index] = element;
    self->top++;
    stack_check_increase(self);
}
