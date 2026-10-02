/**
 * @file queue.h
 * @brief File de CarState pour le parcours en largeur du graphe.
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef QUEUE_H
 #define QUEUE_H
 
 #include "track.h"
 #include "list.h"
 #include <stdlib.h>
 #include <assert.h>
 
 /**
  * @typedef Queue
  * A queue is implemented as a wrapper around the List structure.
  */
 typedef List Queue;
 
 /**
  * @brief Creates a new empty queue.
  *
  * @return Pointer to the newly created queue.
  */
 Queue* createQueue(void);
 
 /**
  * @brief Enqueues a value into the queue (adds to the end).
  *
  * @param value The CarState to enqueue.
  * @param queue Pointer to the target queue.
  */
 void enqueue(Queue* queue, CarState value);
 
 /**
  * @brief Dequeues a value from the queue (removes from the front).
  *
  * @param queue Pointer to the queue.
  * @return The dequeued CarState.
  */
 CarState dequeue(Queue* queue);
 
 void freeQueue(Queue* q);



 
 #endif
 