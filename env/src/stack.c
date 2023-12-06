/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stack_private.h"
#include <stdio.h>
#include <stdlib.h>


upo_stack_t upo_stack_create()
{
    upo_stack_t stack = malloc(sizeof(struct upo_stack_s));
    if (stack == NULL)
    {
        perror("Unable to create a stack");
        abort();
    }

    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void upo_stack_destroy(upo_stack_t stack, int destroy_data)
{
    if (stack != NULL)
    {
        upo_stack_clear(stack, destroy_data);
        free(stack);
    }
}

void upo_stack_push(upo_stack_t stack, void *data)
{
    if(stack != NULL){
        upo_stack_node_t * stored_t = malloc(sizeof(upo_stack_node_t));
        stored_t->data = data;
        stored_t->next = stack->top;
        stack->size++;

        stack->top = stored_t;
    }


}

void upo_stack_pop(upo_stack_t stack, int destroy_data)
{
    if(stack != NULL){
        upo_stack_node_t * stored_t = NULL;
        stored_t = stack->top;
        stack->top = stack->top->next;
        stack->size--;
        if(destroy_data != 0){
          free(stored_t->data);
        }
        free(stored_t);
    }
}

void* upo_stack_top(const upo_stack_t stack)
{
    if(upo_stack_is_empty(stack)) return NULL;
    return stack->top->data;

}

int upo_stack_is_empty(const upo_stack_t stack)
{
    if(stack != NULL){
        if(stack->size != 0) return 0;
    }
    return 1;

}

size_t upo_stack_size(const upo_stack_t stack)
{
    if(stack != NULL){
        return stack->size;
    }
    return 0;
}

void upo_stack_clear(upo_stack_t stack, int destroy_data)
{
    if(stack != NULL){
      upo_stack_node_t * stored_t = NULL;
      while(stack->top != NULL){
        stored_t = stack->top;
        stack->top = stack->top->next;
        if(destroy_data != 0){
          free(stored_t->data);
        }
        free(stored_t);
      }
      stack->size = 0;
    }

}
