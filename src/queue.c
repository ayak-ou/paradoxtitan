/**
 * @file queue.c
 * @brief Implementation de la file de CarState.
 *
 * La file est utilisee par loadGraph pour explorer le graphe d'etats
 * en largeur (BFS) depuis la position courante du pilote.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "queue.h"
#include "carState.h"

Queue* createQueue(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) return NULL;

    queue->first = NULL;
    queue->last  = NULL;
    queue->size  = 0;

    return queue;
}

void enqueue(Queue* queue, CarState value) {
    Node* newNode;
    if (!queue) return;

    newNode = createNode(value, NULL);
    if (!newNode) return;

    if (isEmpty(queue)) {
        queue->first = newNode;
        queue->last  = newNode;
    } else {
        queue->last->next = newNode;
        queue->last       = newNode;
    }
    queue->size++;
}

CarState dequeue(Queue* queue) {
    Node* temp;
    CarState value;

    if (!queue || isEmpty(queue)) {
        fprintf(stderr, "Erreur : defilement d'une file vide.\n");
        exit(EXIT_FAILURE);
    }

    temp  = queue->first;
    value = temp->data;

    queue->first = temp->next;
    if (queue->first == NULL) {
        queue->last = NULL;
    }
    free(temp);
    queue->size--;

    return value;
}

void freeQueue(Queue *q) {
    freeList(q);
}
