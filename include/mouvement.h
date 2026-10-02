/**
 * @file mouvement.h
 * @brief Validation geometrique des deplacements (Bresenham).
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <stdlib.h>

#include "track.h"
#include "carState.h" 


/**
  * @brief Checks if a CarState lies within the track boundaries.
  * @param p The coordinates of the CarState.
  * @param T the track .
  * @return 1 if the CarState is in the track, 0 otherwise.
  */
 int isPositionInTrack(Track T, CarState p);



/**
  * @brief Determines the type of a CarState on the track based on a given character.
  * @param T The track.
  * @param p The coordinates of the CarState.
  * @param c The character to check against.
  * @return 1 if the type matches, 0 otherwise.
  */

 int  checkPointType(Track T, CarState p , char c );


/**
  * @brief Checks if a move from CarState p to CarState q is valid on the track.
  * @param T The track.
  * @param p The starting CarState.
  * @param q The destination CarState.
  * @return 1 if the move is valid, 0 otherwise.
  */
 int isMovementValid( Track T, CarState p, CarState q);
 

#endif
