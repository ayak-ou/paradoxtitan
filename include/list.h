/**
 * @file list.h
 * @brief Liste simplement chainee de CarState.
 *
 * Structure de base servant de support a la pile (stack.h) et a la
 * file (queue.h). Fournit la creation de noeuds, le test de vacuite
 * et la liberation memoire.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef LIST_H
#define LIST_H

#include "track.h"
#include "carState.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/**
 * @struct Node
 * @brief Noeud d'une liste chainee.
 */
typedef struct Node {
    CarState data;          /**< Donnee stockee dans le noeud. */
    struct Node* next;      /**< Pointeur vers le noeud suivant. */
} Node;

/**
 * @struct List
 * @brief Liste simplement chainee.
 */
typedef struct list {
    Node* first;            /**< Premier noeud de la liste. */
    Node* last;             /**< Dernier noeud de la liste. */
    int size;               /**< Nombre de noeuds. */
} List;

/**
 * @brief Cree un nouveau noeud.
 * @param value Valeur a stocker.
 * @param next Pointeur vers le noeud suivant.
 * @return Pointeur vers le noeud cree.
 */
Node* createNode(CarState value, Node* next);

/**
 * @brief Indique si la liste est vide.
 * @param list Pointeur vers la liste.
 * @return true si la liste est vide, false sinon.
 */
bool isEmpty(List* list);

/**
 * @brief Libere la memoire d'une liste.
 * @param list Pointeur vers la liste.
 */
void freeList(List* list);

#endif
