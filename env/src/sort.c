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

#include <assert.h>
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void * val1P, void * val2P, size_t size){
    if(val1P == val2P) return;
    void *e = malloc(size);
    memcpy(e, val1P, size);
    memcpy(val1P, val2P, size);
    memcpy(val2P, e, size);
    free(e);
}

void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    char * basePtr = (char*) base;
    for(size_t i=1; i<n; i++){
        int j=i;
        while((j>0) && cmp((basePtr + (j-1)*size), (basePtr + j*size))>0){
            swap(basePtr + (j-1)*size, (basePtr + j*size), size);
            j--;
        }
    }
}

void upo_merge(void *base, size_t n1, size_t n2, size_t size, upo_sort_comparator_t cmp){
    char * arrayCopy = malloc(size*(n1+n2));
    char * arrayCopyPtr = arrayCopy;
    char * basePtr = (char*) base;
    char * ptr1 = basePtr;
    char * ptr2 = basePtr + size*n1;


    while((ptr1 != basePtr + size*n1) && (ptr2 != basePtr + size*(n1+n2))) {
        if (cmp(ptr1, ptr2)<0) {    //se maggiore *ptr1
            memcpy(arrayCopyPtr, ptr1, size);
            arrayCopyPtr = arrayCopyPtr + size;
            ptr1 = ptr1 + size;
        } else {
            memcpy(arrayCopyPtr, ptr2, size);
            arrayCopyPtr = arrayCopyPtr + size;
            ptr2 = ptr2 + size;
        }
    }

    while(ptr1 != basePtr + size*n1){
        memcpy(arrayCopyPtr, ptr1, size);
        arrayCopyPtr = arrayCopyPtr + size;
        ptr1 = ptr1 + size;
    }
    while(ptr2 != basePtr + size*(n1+n2)){
        memcpy(arrayCopyPtr, ptr2, size);
        arrayCopyPtr = arrayCopyPtr + size;
        ptr2 = ptr2 + size;
    }

    memcpy(basePtr, arrayCopy, size*(n1+n2));
    free(arrayCopy);
}

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if(n <= 1) return;  //caso base
    size_t n1 = n/2;    //lunghezza sub-array sinistro
    size_t n2 = n-n1;   //lunghezza sub-array destro

    upo_merge_sort((char*)base, n1, size, cmp);
    upo_merge_sort((char*)base + n1*size, n2, size, cmp);
    upo_merge((char*)base, n1, n2, size, cmp);
}

int partition(void *base, size_t n, size_t size, upo_sort_comparator_t cmp){
    void *pivot = base;
    size_t pivotPos = 0;
    swap(base, (char*)base+n/2*size, size);
    for(size_t i=1; i<n; i++){
        if(cmp((char*)base+i*size, base)<0){
            swap((char*)base+(++pivotPos)*size, (char*)base+i*size, size);
        }
    }
    swap(pivot, (char*)base+pivotPos*size, size);
    return pivotPos;
}


void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{

  if(n <= 1) return;
  int q = partition(base, n, size, cmp);
  int n1 = q;
  int n2 = n-q;
  upo_quick_sort(base, n1, size, cmp);
  upo_quick_sort((char*)base+q*size, n2, size, cmp);
}
