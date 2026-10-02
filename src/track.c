/**
 * @file track.c
 * @brief Lecture de la carte depuis l'entree standard et accesseurs.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#include "track.h"

Track createTrack(FILE *input, FILE *output) {
    char c;
    int row, j;
    Track T = malloc(sizeof(struct track));
    if (T == NULL) {
        fprintf(output, "Erreur d'allocation de memoire pour la piste.\n");
        exit(EXIT_FAILURE);
    }

    if (fscanf(input, "%d %d %d\n", &T->width, &T->height, &T->gasLevel) != 3) {
        fprintf(output, "Erreur de lecture des dimensions de la piste.\n");
        free(T);
        exit(EXIT_FAILURE);
    }

    if (T->width <= 0 || T->height <= 0 || T->gasLevel <= 0) {
        fprintf(output, "Dimensions de la piste invalides.\n");
        free(T);
        exit(EXIT_FAILURE);
    }

    T->track = calloc(T->height, sizeof(char *));
    if (T->track == NULL) {
        fprintf(output, "Erreur d'allocation de memoire pour les lignes de la piste.\n");
        free(T);
        exit(EXIT_FAILURE);
    }

    fprintf(output, "=== >Map< ===\n");
    fprintf(output, "Size %d x %d\n", T->width, T->height);
    fprintf(output, "Gas at start %d \n\n", T->gasLevel);

    for (row = 0; row < T->height; row++) {
        T->track[row] = calloc(T->width + 1, sizeof(char));
        if (T->track[row] == NULL) {
            fprintf(output, "Erreur d'allocation memoire pour la ligne %d.\n", row);
            for (j = 0; j < row; j++) {
                free(T->track[j]);
            }
            free(T->track);
            free(T);
            exit(EXIT_FAILURE);
        }
        fread(T->track[row], sizeof(char), T->width, input);
        while (fread(&c, sizeof(char), 1, input) == 1 && c != '\n');
        fprintf(output, "%s\n", T->track[row]);
    }

    fflush(output);

    return T;
}

char getCell(Track T, int x, int y) {
    return T->track[y][x];
}

int isFinish(Track T, int x, int y) {
    return T->track[y][x] == FINISH;
}

int isSable(Track T, int x, int y) {
    return T->track[y][x] == SABLE;
}

int isPiste(Track T, int x, int y) {
    return T->track[y][x] == PISTE;
}

void freeTrack(Track T) {
    int i;
    if (T == NULL) return;
    for (i = 0; i < T->height; i++) {
        free(T->track[i]);
    }
    free(T->track);
    free(T);
}
