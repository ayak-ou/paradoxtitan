/**
 * @file mouvement.c
 * @brief Validation geometrique des deplacements par l'algorithme de Bresenham.
 *
 * Verifie qu'une trajectoire rectiligne entre deux etats ne traverse
 * aucune case hors-piste, conformement a la regle d'interdiction de
 * couper la route.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "mouvement.h"

int isPositionInTrack(Track T, CarState p) {
    return (p.x >= 0 && p.x < T->width &&
            p.y >= 0 && p.y < T->height);
}

int checkPointType(Track T, CarState p, char c) {
    return T->track[p.y][p.x] == c;
}

int isMovementValid(Track T, CarState p, CarState q) {
    int deltaX, deltaY, stepX, stepY, currX, currY, error, i;
    char cell;

    if (!isPositionInTrack(T, q))
        return 0;

    cell = T->track[q.y][q.x];
    if (cell == HORS_PISTE)
        return 0;

    deltaX = q.x - p.x;
    deltaY = q.y - p.y;
    stepX  = (deltaX > 0) - (deltaX < 0);
    stepY  = (deltaY > 0) - (deltaY < 0);
    deltaX = abs(deltaX);
    deltaY = abs(deltaY);
    currX  = p.x;
    currY  = p.y;

    if (deltaX >= deltaY) {
        error = deltaX / 2;
        for (i = 0; i < deltaX; i++) {
            if (T->track[currY][currX] == HORS_PISTE)
                return 0;
            error -= deltaY;
            if (error < 0) {
                currY += stepY;
                error += deltaX;
            }
            currX += stepX;
        }
    } else {
        error = deltaY / 2;
        for (i = 0; i < deltaY; i++) {
            if (T->track[currY][currX] == HORS_PISTE)
                return 0;
            error -= deltaX;
            if (error < 0) {
                currX += stepX;
                error += deltaY;
            }
            currY += stepY;
        }
    }
    return 1;
}
