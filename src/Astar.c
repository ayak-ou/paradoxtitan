/**
 * @file Astar.c
 * @brief Recherche du chemin optimal par l'algorithme A*.
 *
 * A* explore le graphe d'etats en minimisant f(n) = g(n) + h(n), ou
 * g(n) est le cout accumule (a * consommation + b * (5 - vitesse)) et
 * h(n) la distance euclidienne vers l'arrivee. La file de priorite est
 * un tas de Fibonacci. Le chemin est reconstruit en remontant les
 * parents memorises durant la recherche.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "astar.h"
#include <math.h>
#include <limits.h>

Stack *aStar(Graph *G, Track T, CarState p, CarState q, double a, double b) {
    Stack *path;
    FibonacciHeap *openSet;
    FibonacciNode *currentNode;
    Arc *neighbor;
    CarState currentPoint, finishReached;
    int startIndex, currentIndex, neighborIndex, idx;
    int found;
    double dx, dy, speed, tentativeCost, heuristic;

    path    = createStack();
    openSet = createFibonacciHeap();

    startIndex = calculateVertexIndex(G, p);

    G->dist[startIndex]    = 0;
    G->parents[startIndex] = p;

    fh_insert(openSet, p, 0);

    found = 0;
    finishReached = p;

    while (openSet->size > 0 && !found) {
        currentNode = fh_extract_min(openSet);
        if (!currentNode) break;

        currentPoint = currentNode->p;
        currentIndex = calculateVertexIndex(G, currentPoint);

        if (T->track[currentPoint.y][currentPoint.x] == FINISH) {
            finishReached = currentPoint;
            found = 1;
            freeFibonacciNode(currentNode);
            break;
        }

        if (G->visited[currentIndex] == 2) {
            freeFibonacciNode(currentNode);
            continue;
        }
        G->visited[currentIndex] = 2;

        neighbor = G->arcs[currentIndex];
        while (neighbor != NULL) {
            neighborIndex = calculateVertexIndex(G, neighbor->destination);

            if (G->visited[neighborIndex] == 2) {
                neighbor = neighbor->next;
                continue;
            }

            speed = sqrt((double)(
                neighbor->destination.vx * neighbor->destination.vx +
                neighbor->destination.vy * neighbor->destination.vy));

            tentativeCost = (double)G->dist[currentIndex]
                          + a * (double)neighbor->cost
                          + b * (5.0 - speed);

            dx = (double)(neighbor->destination.x - q.x);
            dy = (double)(neighbor->destination.y - q.y);
            heuristic = tentativeCost + sqrt(dx * dx + dy * dy);

            if (tentativeCost < (double)G->dist[neighborIndex]) {
                G->dist[neighborIndex]    = (int)tentativeCost;
                G->parents[neighborIndex] = currentPoint;
                fh_insert(openSet, neighbor->destination, heuristic);
            }

            neighbor = neighbor->next;
        }
        freeFibonacciNode(currentNode);
    }

    freeFibonacciHeap(openSet);

    if (!found) {
        pushStack(path, p);
        return path;
    }

    currentPoint = finishReached;
    while (calculateVertexIndex(G, currentPoint) != startIndex) {
        idx = calculateVertexIndex(G, currentPoint);
        if (G->dist[idx] == INT_MAX) break;
        pushStack(path, currentPoint);
        currentPoint = G->parents[idx];
    }
    pushStack(path, p);

    return path;
}
