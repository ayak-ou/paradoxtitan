/**
 * @file stack.h
 * @brief Pile de CarState (sommet = prochain mouvement a jouer).
 *
 * Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
 * Equipe ParadoxTitan.
 * Auteurs : Khalil Anbari, Aya Khouya.
 * Date : mai 2026.
 */

#ifndef STACK_H
 #define STACK_H
 
 #include "track.h"
 #include "list.h"
 #include <stdlib.h>
 #include <assert.h>
 
 /**
  * @typedef Stack
  * A stack is implemented as a wrapper around the List structure.
  */
 typedef List Stack;
 
 /**
  * @brief Creates a new empty stack.
  *
  * @return Pointer to the newly created stack.
  */
 Stack* createStack(void);
 
 /**
  * @brief Pushes a value onto the top of the stack.
  *
  * @param value The CarState to push.
  * @param stack Pointer to the target stack.
  */
 void pushStack(Stack* stack, CarState value);
 
 /**
  * @brief Pops the top value from the stack.
  *
  * @param stack Pointer to the stack.
  * @return The popped CarState.
  */
 CarState popStack(Stack* stack);


 void freeStack(Stack *s);
 
 
 #endif
 