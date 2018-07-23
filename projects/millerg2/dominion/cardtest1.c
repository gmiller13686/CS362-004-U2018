#include "dominion.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

//Unit test for villageCard function
int main() {
    int i;
    int* point;
    int result = -1;
    struct gameState* state;
    state->numPlayers = 2;
    for(i = 0; i < 25; i++) {
        state->supplyCount[i] = 10;
    }
    state->whoseTurn = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->hand[0][0] = 1;
    state->hand[0][1] = 6;
    state->hand[0][2] = 14;
    state->hand[1][0] = 3;
    state->hand[1][1] = 14;
    state->hand[1][2] = 15;
    state->hand[1][3] = 5;
    //state->handCount[0] = 3;
    //state->handCount[1] = 4;
    //state->discardCount[0] = 0;
    //state->discardCount[1] = 0;
    //state->playedCardCount = 0;

    //Test 1: Player 0 plays the village card from hand position 2
    result = villageCard(14, 1, 2, 3, state, 2, point, 0);


    return 0;    
}
