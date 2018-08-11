#ifndef _RANDOMTESTMETHODS_H
#define _RANDOMTESTMETHODS_H

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define TESTS 1000000
#define SUPPLY_CARDS 5
#define KINGDOM_CARDS 10
#define VERBOSE 0

void randomizeAdventurerTest(struct gameState* gameSt, int player);
void randomizeGameState(struct gameState* gameSt, int player);
void randomizeSupply(struct gameState* gameSt);
void randomizeDeck(struct gameState* gameSt, int player);
void setDeck(struct gameState* gameSt, int player);
void randomizeHand(struct gameState* gameSt, int player);
void randomizeDiscard(struct gameState* gameSt, int player);
void randomizePlayerState(struct gameState* gameSt, int player);


#endif