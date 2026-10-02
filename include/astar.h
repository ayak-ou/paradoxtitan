/**
 * @file astar.h
 * @brief Recherche de chemin optimal par l'algorithme A*.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef ASTAR_H
#define ASTAR_H

#include "graph.h"
#include "stack.h"
#include "fibonacciHeap.h"

Stack *aStar(Graph *G, Track T, CarState p, CarState q, double a, double b);

#endif
