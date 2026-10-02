/**
 * @file utils.c
 * @brief Fonctions utilitaires : carburant, dialogue GDC, gestion des adversaires.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "utils.h"

int gasConsumption(int accX, int accY, int speedX, int speedY, int inSand) {
    int gas = accX * accX + accY * accY;
    gas += (int)(sqrt((double)(speedX * speedX + speedY * speedY) * 1.5));
    if (inSand) {
        gas += 1;
    }
    return -gas;
}

void sendAcceleration(int ax, int ay, int fuel, FILE *log) {
    fprintf(stdout, "%d %d\n", ax, ay);
    fflush(stdout);
    fprintf(log, "\t%d %d (carburant restant %d)\n", ax, ay, fuel);
    fflush(log);
}

void estimerVitesse(CarState adv, CarState advOld, int *vx, int *vy) {
    *vx = adv.x - advOld.x;
    *vy = adv.y - advOld.y;
}



void bloquerZoneDanger(Track T, CarState adv, int advVx, int advVy, char *oldCells) {
    int probX, probY;

    oldCells[0] = T->track[adv.y][adv.x];
    T->track[adv.y][adv.x] = HORS_PISTE;

    probX = adv.x + advVx;
    probY = adv.y + advVy;
    oldCells[1] = HORS_PISTE;

    if (probX >= 0 && probX < T->width &&
        probY >= 0 && probY < T->height &&
        (probX != adv.x || probY != adv.y)) {
        oldCells[1] = T->track[probY][probX];
        T->track[probY][probX] = HORS_PISTE;
    }
}

void restaurerCases(Track T, CarState adv, int advVx, int advVy, char *oldCells) {
    int probX, probY;

    T->track[adv.y][adv.x] = oldCells[0];

    probX = adv.x + advVx;
    probY = adv.y + advVy;

    if (probX >= 0 && probX < T->width &&
        probY >= 0 && probY < T->height &&
        (probX != adv.x || probY != adv.y)) {
        T->track[probY][probX] = oldCells[1];
    }
}
