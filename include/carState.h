/**
 * @file carState.h
 * @brief Etat complet d'une voiture dans l'espace de recherche.
 *
 * Un CarState ne represente pas une simple coordonnee, mais l'etat
 * complet du pilote a un instant donne : sa position, son vecteur
 * vitesse et l'indicateur d'utilisation d'un boost. C'est l'unite de
 * base manipulee par le graphe d'etats et par l'algorithme A*.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef CAR_STATE_H
#define CAR_STATE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @struct CarState
 * @brief Etat d'une voiture : position, vitesse et boost.
 */
typedef struct carState {
    int x;      /**< Abscisse sur la grille. */
    int y;      /**< Ordonnee sur la grille. */
    int vx;     /**< Composante horizontale de la vitesse. */
    int vy;     /**< Composante verticale de la vitesse. */
    int boost;  /**< 1 si un boost est utilise pour la transition, 0 sinon. */
} CarState;

#endif
