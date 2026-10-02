/**
 * @file fibonacciHeap.h
 * @brief Tas de Fibonacci servant de file de priorite a A*.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <stdlib.h>
#include "carState.h"

typedef struct FibonacciNode {
    CarState p;
    int key;
    int degree;
    int marked;       
    struct FibonacciNode *parent;
    struct FibonacciNode *child;
    struct FibonacciNode *left;
    struct FibonacciNode *right;
} FibonacciNode;

typedef struct FibonacciHeap {
    FibonacciNode *min;
    FibonacciNode *roots;
    int size;
} FibonacciHeap;

FibonacciHeap *createFibonacciHeap(void);
FibonacciNode *createFibonacciNode(CarState p, int key);
void fh_insert(FibonacciHeap *heap, CarState p, int key);
FibonacciNode *fh_extract_min(FibonacciHeap *heap);
void consolidate(FibonacciHeap *heap);
void fh_link(FibonacciHeap *heap, FibonacciNode *y, FibonacciNode *x);
void freeFibonacciHeap(FibonacciHeap *heap);
void freeFibonacciNode(FibonacciNode *node);

#endif