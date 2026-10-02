/**
 * @file graph.h
 * @brief Graphe d'etats pour la planification de trajectoire.
 *
 * Chaque sommet du graphe est un CarState complet (position, vitesse,
 * boost), indexe de maniere unique par calculateVertexIndex. Le graphe
 * est construit dynamiquement par un parcours en largeur depuis la
 * position courante du pilote (loadGraph).
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#include "track.h"
#include "carState.h"
#include "queue.h"
#include "fibonacciHeap.h"

#define VMAX 5
#define BOOST_MAX 5

/**
 * @struct arc
 * @brief Transition entre deux etats : destination, cout et acceleration.
 */
typedef struct arc {
    CarState destination;   /**< Etat atteint par la transition. */
    int cost;               /**< Cout de la transition (consommation). */
    int ax, ay;             /**< Acceleration appliquee. */
    struct arc *next;       /**< Arc suivant dans la liste d'adjacence. */
} Arc;

/**
 * @struct graph
 * @brief Graphe d'etats represente par listes d'adjacence.
 */
typedef struct graph {
    int size;               /**< Nombre total d'etats possibles. */
    int width;              /**< Largeur de la carte. */
    int height;             /**< Hauteur de la carte. */
    int vmax;               /**< Vitesse maximale autorisee. */
    Arc **arcs;             /**< Listes d'adjacence indexees par etat. */
    int *visited;           /**< Statut de visite (0/1/2) de chaque etat. */
    int *dist;              /**< Meilleur cout connu pour atteindre chaque etat. */
    CarState *parents;      /**< Parent de chaque etat (reconstruction du chemin). */
} Graph;

Graph *createGraph(Track T);
int calculateVertexIndex(Graph *g, CarState p);
void addArc(Graph *g, int srcIndex, CarState dest, int cost, int ax, int ay);
void setParent(Graph *g, CarState dest, CarState src, int cost, int ax, int ay);
void loadGraph(Graph *g, Track T, CarState pilot, int *boosts);
CarState findClosestFinish(Track T, CarState pilot);
void freeGraph(Graph *g);

#endif
