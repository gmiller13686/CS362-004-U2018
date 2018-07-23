#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

//Unit test for isGameOver function
int main() {
    int i;
    int result = -1;
    struct gameState* state;

    //Test 1: province card pile is empty

    for (i = 0; i < 25; i++) {
        state->supplyCount[i] = 10;
    }
    state->supplyCount[3] = 0;

    result = isGameOver(state);

    if (result == 1) { 
        printf("isGameOver Test 1 successful!\n");
    }
    else {
        printf("isGameOver Test 1 failed.\n");
    }

    //Test 2: 3 card piles are empty (not including province cards)
    result = -1;
    state->supplyCount[3] = 10;
    state->supplyCount[5] = 0;
    state->supplyCount[10] = 0;
    state->supplyCount[18] = 0;

    result = isGameOver(state);

    if (result == 1) { 
        printf("isGameOver Test 2 successful!\n");
    }
    else {
        printf("isGameOver Test 2 failed.\n");
    }

    //Test 3: No card piles are empty
    result = -1;
    state->supplyCount[5] = 10;
    state->supplyCount[10] = 10;
    state->supplyCount[15] = 10;

    result = isGameOver(state);


    if (result == 0) { 
        printf("isGameOver Test 3 successful!\n");
    }
    else {
        printf("isGameOver Test 3 failed.\n");
    }

    return 0;
}
