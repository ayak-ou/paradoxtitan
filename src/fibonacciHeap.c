/**
 * @file fibonacciHeap.c
 * @brief Tas de Fibonacci servant de file de priorite a l'algorithme A*.
 *
 * Insertion en temps constant amorti et extraction du minimum en temps
 * logarithmique amorti. L'operation de diminution de cle n'est pas
 * implementee : A* reinsere les etats ameliores et ignore les entrees
 * obsoletes grace au marquage des etats deja traites (suppression
 * paresseuse).
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "fibonacciHeap.h"
#include <stdlib.h>
#include <math.h>

#define FIB_MAX_DEGREE 64

static void remove_from_list(FibonacciNode *node) {
    if (!node) return;
    node->left->right = node->right;
    node->right->left = node->left;
    node->left  = node;
    node->right = node;
}

static void add_to_root_list(FibonacciHeap *heap, FibonacciNode *node) {
    if (!heap || !node) return;
    node->parent = NULL;
    node->marked = 0;
    node->left   = node;
    node->right  = node;
    if (heap->roots == NULL) {
        heap->roots = node;
        heap->min   = node;
    } else {
        node->right              = heap->roots;
        node->left               = heap->roots->left;
        heap->roots->left->right = node;
        heap->roots->left        = node;
        if (node->key < heap->min->key)
            heap->min = node;
    }
}

static void link(FibonacciNode *child, FibonacciNode *parent) {
    remove_from_list(child);
    child->parent = parent;
    child->marked = 0;
    if (parent->child == NULL) {
        parent->child = child;
        child->left   = child;
        child->right  = child;
    } else {
        child->right               = parent->child;
        child->left                = parent->child->left;
        parent->child->left->right = child;
        parent->child->left        = child;
    }
    parent->degree++;
}

static void free_node_list(FibonacciNode *start) {
    FibonacciNode *cur, *nxt;
    if (!start) return;
    cur = start;
    do {
        nxt = cur->right;
        if (cur->child) free_node_list(cur->child);
        free(cur);
        cur = nxt;
    } while (cur != start);
}

FibonacciHeap *createFibonacciHeap(void) {
    FibonacciHeap *h = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
    if (!h) return NULL;
    h->min = h->roots = NULL;
    h->size = 0;
    return h;
}

FibonacciNode *createFibonacciNode(CarState p, int key) {
    FibonacciNode *n = (FibonacciNode*)malloc(sizeof(FibonacciNode));
    if (!n) return NULL;
    n->p      = p;
    n->key    = key;
    n->degree = 0;
    n->marked = 0;
    n->parent = n->child = NULL;
    n->left   = n->right = n;
    return n;
}

void fh_insert(FibonacciHeap *heap, CarState p, int key) {
    FibonacciNode *node;
    if (!heap) return;
    node = createFibonacciNode(p, key);
    if (!node) return;
    add_to_root_list(heap, node);
    heap->size++;
}

void fh_link(FibonacciHeap *heap, FibonacciNode *y, FibonacciNode *x) {
    (void)heap;
    if (!y || !x || y == x) return;
    link(y, x);
}

void consolidate(FibonacciHeap *heap) {
    FibonacciNode *A[FIB_MAX_DEGREE];
    FibonacciNode **roots;
    FibonacciNode *x, *y, *tmp, *node;
    int i, d, n;

    if (!heap || !heap->roots) return;

    for (i = 0; i < FIB_MAX_DEGREE; i++) A[i] = NULL;

    n = 0;
    x = heap->roots;
    do { n++; x = x->right; } while (x != heap->roots);

    roots = (FibonacciNode**)malloc(n * sizeof(FibonacciNode*));
    if (!roots) return;

    x = heap->roots;
    for (i = 0; i < n; i++) { roots[i] = x; x = x->right; }

    for (i = 0; i < n; i++) {
        x = roots[i];
        d = x->degree;
        while (d < FIB_MAX_DEGREE && A[d]) {
            y = A[d];
            if (x->key > y->key) { tmp = x; x = y; y = tmp; }
            link(y, x);
            A[d++] = NULL;
        }
        if (d < FIB_MAX_DEGREE) A[d] = x;
    }
    free(roots);

    heap->roots = heap->min = NULL;
    for (i = 0; i < FIB_MAX_DEGREE; i++) {
        if (!A[i]) continue;
        node        = A[i];
        node->left  = node;
        node->right = node;
        node->parent = NULL;
        if (!heap->roots) {
            heap->roots = heap->min = node;
        } else {
            node->right              = heap->roots;
            node->left               = heap->roots->left;
            heap->roots->left->right = node;
            heap->roots->left        = node;
            if (node->key < heap->min->key) heap->min = node;
        }
    }
}

FibonacciNode *fh_extract_min(FibonacciHeap *heap) {
    FibonacciNode *z, *c, *start;
    FibonacciNode **children;
    int nchildren, i;

    if (!heap || !heap->min) return NULL;
    z = heap->min;

    nchildren = z->degree;
    children  = (FibonacciNode**)malloc(nchildren * sizeof(FibonacciNode*));
    if (nchildren > 0 && children) {
        start = z->child;
        c     = start;
        for (i = 0; i < nchildren; i++) {
            children[i] = c;
            c = c->right;
        }
        for (i = 0; i < nchildren; i++) {
            children[i]->left   = children[i];
            children[i]->right  = children[i];
            children[i]->parent = NULL;
            children[i]->marked = 0;
            add_to_root_list(heap, children[i]);
        }
        z->child  = NULL;
        z->degree = 0;
    }
    if (children) free(children);

    if (z->right == z) {
        heap->roots = heap->min = NULL;
    } else {
        z->left->right = z->right;
        z->right->left = z->left;
        heap->roots = z->right;
        heap->min   = z->right;
        z->left = z->right = z;
        consolidate(heap);
    }

    heap->size--;
    return z;
}

void freeFibonacciNode(FibonacciNode *node) {
    if (node) free(node);
}

void freeFibonacciHeap(FibonacciHeap *heap) {
    if (!heap) return;
    if (heap->roots) free_node_list(heap->roots);
    free(heap);
}
