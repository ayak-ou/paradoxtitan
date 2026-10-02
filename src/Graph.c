/**
 * @file Graph.c
 * @brief Construction du graphe d'etats et indexation des sommets.
 *
 * Le graphe est bati par un parcours en largeur depuis l'etat courant
 * du pilote. Pour chaque etat, les neuf accelerations elementaires sont
 * testees et seules les transitions valides (vitesse, terrain, Bresenham)
 * sont ajoutees. Le cout d'un arc correspond a la consommation de
 * carburant qu'il entraine.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "graph.h"
#include "mouvement.h"

Graph *createGraph(Track T) {
    int i, vRange;
    Graph *G = malloc(sizeof(Graph));
    if (!G) { fprintf(stderr, "Erreur malloc Graph\n"); exit(1); }

    G->width  = T->width;
    G->height = T->height;
    G->vmax   = VMAX;
    vRange    = 2 * G->vmax + 1;
    G->size   = G->width * G->height * vRange * vRange * (BOOST_MAX + 1);

    G->arcs    = calloc(G->size, sizeof(Arc *));
    G->visited = calloc(G->size, sizeof(int));
    G->dist    = malloc(G->size * sizeof(int));
    G->parents = malloc(G->size * sizeof(CarState));

    if (!G->arcs || !G->visited || !G->dist || !G->parents) {
        fprintf(stderr, "Erreur malloc Graph membres\n"); exit(1);
    }

    for (i = 0; i < G->size; i++) {
        G->dist[i]    = INT_MAX;
        G->visited[i] = 0;
    }
    return G;
}

int calculateVertexIndex(Graph *g, CarState p) {
    int vRange = 2 * g->vmax + 1;
    int vx     = p.vx + g->vmax;
    int vy     = p.vy + g->vmax;
    return (((p.y * g->width + p.x) * vRange + vx) * vRange + vy)
           * (BOOST_MAX + 1) + p.boost;
}

void addArc(Graph *g, int srcIndex, CarState dest, int cost, int ax, int ay) {
    Arc *a = malloc(sizeof(Arc));
    if (!a) { fprintf(stderr, "Erreur malloc Arc\n"); exit(1); }
    a->destination = dest;
    a->cost        = cost;
    a->ax          = ax;
    a->ay          = ay;
    a->next        = g->arcs[srcIndex];
    g->arcs[srcIndex] = a;
}

void setParent(Graph *g, CarState dest, CarState src, int cost, int ax, int ay) {
    (void)cost; (void)ax; (void)ay;
    g->parents[calculateVertexIndex(g, dest)] = src;
}

static int isCellPassable(char c) {
    return (c == PISTE || c == SABLE || c == FINISH ||
            c == START_1 || c == START_2 || c == START_3);
}

void loadGraph(Graph *g, Track T, CarState pilot, int *boosts) {
    int ax, ay, speedSq, cost, inSand, srcIndex, destIndex;
    char destCell, srcCell;
    CarState current, next;
    Queue *q = createQueue();

    pilot.boost = (*boosts > 0) ? 1 : 0;

    srcIndex = calculateVertexIndex(g, pilot);
    enqueue(q, pilot);
    g->visited[srcIndex] = 1;

    while (!isEmpty(q)) {
        current  = dequeue(q);
        srcIndex = calculateVertexIndex(g, current);
        srcCell  = T->track[current.y][current.x];
        inSand   = (srcCell == SABLE) ? 1 : 0;

        for (ax = -1; ax <= 1; ax++) {
            for (ay = -1; ay <= 1; ay++) {
                next.vx    = current.vx + ax;
                next.vy    = current.vy + ay;
                next.boost = current.boost;

                speedSq = next.vx * next.vx + next.vy * next.vy;
                if (speedSq > 25) continue;
                if (inSand && speedSq > 1) continue;

                next.x = current.x + next.vx;
                next.y = current.y + next.vy;

                if (next.x < 0 || next.x >= g->width ||
                    next.y < 0 || next.y >= g->height)
                    continue;

                destCell = T->track[next.y][next.x];
                if (!isCellPassable(destCell)) continue;
                if (!isMovementValid(T, current, next)) continue;

                cost = ax * ax + ay * ay
                     + (int)(sqrt((double)speedSq) * 1.5)
                     + inSand;

                destIndex = calculateVertexIndex(g, next);
                addArc(g, srcIndex, next, cost, ax, ay);

                if (g->visited[destIndex] == 0 && destCell != FINISH) {
                    g->visited[destIndex] = 1;
                    enqueue(q, next);
                }
            }
        }
        g->visited[srcIndex] = 2;
    }

    for (ax = 0; ax < g->size; ax++)
        g->visited[ax] = 0;

    freeQueue(q);
}

CarState findClosestFinish(Track T, CarState pilot) {
    int x, y;
    double dist, minDist = DBL_MAX, dx, dy;
    CarState best;

    best.x = -1; best.y = -1; best.vx = 0; best.vy = 0; best.boost = 0;

    for (y = 0; y < T->height; y++) {
        for (x = 0; x < T->width; x++) {
            if (T->track[y][x] == FINISH) {
                dx = (double)(x - pilot.x);
                dy = (double)(y - pilot.y);
                dist = sqrt(dx * dx + dy * dy);
                if (dist < minDist) {
                    minDist = dist;
                    best.x  = x;
                    best.y  = y;
                }
            }
        }
    }
    return best;
}

void freeGraph(Graph *g) {
    int i;
    Arc *cur, *tmp;
    if (!g) return;
    for (i = 0; i < g->size; i++) {
        cur = g->arcs[i];
        while (cur) { tmp = cur; cur = cur->next; free(tmp); }
    }
    free(g->arcs);
    free(g->visited);
    free(g->dist);
    free(g->parents);
    free(g);
}
