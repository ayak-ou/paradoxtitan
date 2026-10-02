/**
 * @file ParadoxTitan.c
 * @brief Programme principal du pilote ParadoxTitan.
 *
 * Boucle de course : a chaque tour, lit les positions des trois pilotes,
 * estime la vitesse des adversaires, puis decide s'il faut replanifier.
 * Une nouvelle recherche A* n'est lancee que si le plan courant n'est
 * plus valide (pathInvalid), si la case suivante est bloquee par un
 * adversaire (nextCellBlocked) ou si le carburant devient insuffisant.
 * Sinon, le pilote se contente de suivre le plan etabli.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "track.h"
#include "carState.h"
#include "graph.h"
#include "astar.h"
#include "stack.h"
#include "utils.h"
#include "mouvement.h"

#define BOOST_MAX 5

int main(void) {
    int accX, accY, gasLevel, inSand;
    int boosts = BOOST_MAX;
    int carburantInsuffisant, round, pathInvalid, nextCellBlocked;
    char oldCells1[DANGER_ZONE_SIZE];
    char oldCells2[DANGER_ZONE_SIZE];
    int opp1Vx, opp1Vy, opp2Vx, opp2Vy;
    CarState myPilote, next, opponent1, opponent2;
    CarState opponent1Old, opponent2Old, arrival;
    Stack *path;
    Graph *graph;
    FILE *log;
    Track T;

    myPilote.x = 0; myPilote.y = 0; myPilote.vx = 0; myPilote.vy = 0;
    myPilote.boost = 0;
    next.x = -1; next.y = -1; next.vx = 0; next.vy = 0; next.boost = 0;
    opponent1.x = 0; opponent1.y = 0; opponent1.vx = 0; opponent1.vy = 0;
    opponent1.boost = 0;
    opponent2    = opponent1;
    opponent1Old = opponent1;
    opponent2Old = opponent2;
    arrival.x = 0; arrival.y = 0; arrival.vx = 0; arrival.vy = 0;
    arrival.boost = 0;

    carburantInsuffisant = 0;
    round           = 0;
    pathInvalid     = 1;
    nextCellBlocked = 0;
    path            = NULL;
    graph           = NULL;
    log             = stderr;
    opp1Vx = opp1Vy = opp2Vx = opp2Vy = 0;

    T = createTrack(stdin, log);
    gasLevel = T->gasLevel;

    fprintf(log, "=== Debut de la course ===\n\n");
    fflush(log);

    do {
        round++;
        fprintf(log, "=== Round %d ===\n", round);

        opponent1Old = opponent1;
        opponent2Old = opponent2;

        fscanf(stdin, "%d %d\t%d %d\t%d %d",
               &myPilote.x, &myPilote.y,
               &opponent1.x, &opponent1.y,
               &opponent2.x, &opponent2.y);

        opponent1.vx = 0; opponent1.vy = 0; opponent1.boost = 0;
        opponent2.vx = 0; opponent2.vy = 0; opponent2.boost = 0;

        fprintf(log, "Positions: A(%d,%d) B(%d,%d) C(%d,%d)\n",
                myPilote.x, myPilote.y,
                opponent1.x, opponent1.y,
                opponent2.x, opponent2.y);

        if (round > 1) {
            estimerVitesse(opponent1, opponent1Old, &opp1Vx, &opp1Vy);
            estimerVitesse(opponent2, opponent2Old, &opp2Vx, &opp2Vy);
        }

        if (round == 1 || myPilote.x != next.x || myPilote.y != next.y) {
            pathInvalid    = 1;
            myPilote.vx    = 0;
            myPilote.vy    = 0;
            myPilote.boost = (boosts > 0) ? 1 : 0;
        } else {
            myPilote.vx    = next.vx;
            myPilote.vy    = next.vy;
            myPilote.boost = next.boost;
            if (path != NULL && path->size > 0) {
                next = popStack(path);
            } else {
                pathInvalid    = 1;
                myPilote.boost = (boosts > 0) ? 1 : 0;
            }
            pathInvalid = 0;
        }

        nextCellBlocked = (next.x == opponent1.x && next.y == opponent1.y) ||
                          (next.x == opponent2.x && next.y == opponent2.y);

        if (pathInvalid || nextCellBlocked || carburantInsuffisant) {
            double ca, cb;
            int gasRatio;

            fprintf(log, "Recalcul (pathInvalid=%d nextCellBlocked=%d carbInsuf=%d)\n",
                    pathInvalid, nextCellBlocked, carburantInsuffisant);

            bloquerZoneDanger(T, opponent1, opp1Vx, opp1Vy, oldCells1);
            bloquerZoneDanger(T, opponent2, opp2Vx, opp2Vy, oldCells2);

            if (graph) { freeGraph(graph); graph = NULL; }
            if (path)  { freeStack(path);  path  = NULL; }
            carburantInsuffisant = 0;

            graph   = createGraph(T);
            loadGraph(graph, T, myPilote, &boosts);
            arrival = findClosestFinish(T, myPilote);

            gasRatio = (gasLevel * 100) / (T->gasLevel > 0 ? T->gasLevel : 1);

            if      (gasRatio > 70) { ca = 2.0; cb = 2.5; } /* mode rapide */
            else if (gasRatio > 50) { ca = 2.5; cb = 2.5; }
            else if (gasRatio > 40) { ca = 3.0; cb = 0.5; }
            else                    { ca = 3.5; cb = 0.3; } /* mode survie */

            fprintf(log, "Gas %d/%d (%d%%) -> ca=%.1f cb=%.1f\n",
                    gasLevel, T->gasLevel, gasRatio, ca, cb);
            path = aStar(graph, T, myPilote, arrival, ca, cb);

            fprintf(log, "Chemin: %d etapes vers (%d,%d)\n",
                    path ? path->size : 0, arrival.x, arrival.y);

            if (path != NULL && path->size >= 2) {
                myPilote = popStack(path);
                next     = popStack(path);
                fprintf(log, "Acc prevu: (%d,%d)\n",
                        next.vx - myPilote.vx, next.vy - myPilote.vy);
            } else {
                next    = myPilote;
                next.vx = 0;
                next.vy = 0;
                fprintf(log, "Pas de chemin trouve.\n");
            }

            restaurerCases(T, opponent1, opp1Vx, opp1Vy, oldCells1);
            restaurerCases(T, opponent2, opp2Vx, opp2Vy, oldCells2);

            pathInvalid     = 0;
            nextCellBlocked = 0;
        }

        accX = next.vx - myPilote.vx;
        accY = next.vy - myPilote.vy;

        if (accX >  1) accX =  1;
        if (accX < -1) accX = -1;
        if (accY >  1) accY =  1;
        if (accY < -1) accY = -1;

        inSand = checkPointType(T, myPilote, SABLE);

        gasLevel += gasConsumption(accX, accY, myPilote.vx, myPilote.vy, inSand);

        sendAcceleration(accX, accY, gasLevel, log);

    } while (!feof(stdin));

    if (graph) freeGraph(graph);
    if (path)  freeStack(path);
    freeTrack(T);
    return 0;
}
