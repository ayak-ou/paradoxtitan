/**
 * @file track.h
 * @brief Lecture et representation de la carte de course.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef TRACK_H
#define TRACK_H

#include <stdio.h>
#include <stdlib.h>

#define PISTE   '#'
#define SABLE   '~'   
#define HORS_PISTE '.' 
#define FINISH  '='
#define START_1 '1'
#define START_2 '2'
#define START_3 '3'


typedef struct track {
    int width;
    int height;
    int gasLevel;
    char **track;
} *Track;


Track createTrack(FILE *input, FILE *output);
void freeTrack(Track T);
char getCell(Track T, int x, int y);
int isFinish(Track T, int x, int y);
int isSable(Track T, int x, int y);
int isPiste(Track T, int x, int y);

#endif