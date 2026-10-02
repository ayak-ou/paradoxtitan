/**
 * @file utils.h
 * @brief Fonctions utilitaires : carburant, dialogue GDC, adversaires.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef UTILS_H
#define UTILS_H
#define DANGER_ZONE_SIZE 2

#include <stdio.h>
#include <math.h>
#include "track.h"
#include "carState.h"

/**
 * @brief Calcule la consommation de carburant
 */
int gasConsumption(int accX, int accY, int aX, int aY, int inSand);

/**
 * @brief Envoie l'accélération au GDC via stdout
 */
void sendAcceleration(int ax, int ay, int fuel, FILE *log);

/**
 * @brief Estime la vitesse d'un adversaire
 * depuis ses deux dernières positions
 */
void estimerVitesse(CarState adv, CarState advOld, int *vx, int *vy);

/**
 * @brief Bloque la case actuelle et probable
 * d'un adversaire sur la carte
 */
void bloquerZoneDanger(Track T, CarState adv, int advVx, int advVy, char *oldCells);

/**
 * @brief Restaure les cases bloquées
 */
void restaurerCases(Track T, CarState adv, int advVx, int advVy, char *oldCells);

#endif