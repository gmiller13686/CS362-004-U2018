#include "dominion.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

//Unit test for whoseTurn function
int main() {
    int i;
    int result = -1;
    struct gameState* state;

    //Test 1: Player 1's turn
    state->whoseTurn = 1;

    result = whoseTurn(state);

    if (result == 1) {
        printf("whoseTurn Test 1 successful\n");
    }
    else {
        printf("whoseTurn Test 1 failed\n");
    }

    //Test 2: Player 0's turn
    result = -1;
    state->whoseTurn = 0;

    result = whoseTurn(state);
    
    if (result == 0) {
        printf("whoseTurn Test 2 successful\n");
    }
    else {
        printf("whoseTurn Test 2 failed\n");
    }

    return 0;
}
