/**
 * @file Stack.c
 * @brief Implementation de la pile de CarState.
 *
 * La pile sert a reconstruire et a parcourir le chemin renvoye par A* :
 * le sommet correspond toujours au prochain mouvement a jouer.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "stack.h"
#include "list.h"
#include "carState.h"

Stack* createStack(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->first = NULL;
    stack->last  = NULL;
    stack->size  = 0;

    return stack;
}

void pushStack(Stack* stack, CarState value) {
    Node* newNode;
    if (!stack) return;

    newNode = createNode(value, NULL);
    if (!newNode) return;

    if (isEmpty(stack)) {
        stack->first = newNode;
        stack->last  = newNode;
    } else {
        newNode->next = stack->first;
        stack->first  = newNode;
    }
    stack->size++;
}

CarState popStack(Stack* stack) {
    Node* temp;
    CarState value;

    if (!stack || isEmpty(stack)) {
        fprintf(stderr, "Erreur : depilement d'une pile vide.\n");
        exit(EXIT_FAILURE);
    }

    temp  = stack->first;
    value = temp->data;

    stack->first = temp->next;
    if (stack->first == NULL) {
        stack->last = NULL;
    }
    free(temp);
    stack->size--;

    return value;
}

void freeStack(Stack *s) {
    freeList(s);
}
