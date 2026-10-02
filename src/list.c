/**
 * @file list.c
 * @brief Implementation de la liste simplement chainee de CarState.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "list.h"
#include "carState.h"

Node* createNode(CarState value, Node* next) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;

    newNode->data = value;
    newNode->next = next;

    return newNode;
}

bool isEmpty(List* list) {
    return list->size == 0;
}

void freeList(List* L) {
    Node *current, *tmp;
    if (L == NULL) return;
    current = L->first;
    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    free(L);
}
