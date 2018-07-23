#include "dominion.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

//Unit test for supplyCount function
int main() {
    int i;
    int result = -1;
    struct gameState* state;

    //Test 1: Province supply count is greater than 0
    for(i = 0; i < 25; i++) {
        state->supplyCount[i] = i + 1;
    }

    result = supplyCount(province, state);

    if (result == 4) {
        printf("supplyCount Test 1 successful\n");
    }
    else {
        printf("supplyCount Test 1 failed\n");
    }

    //Test 2: Adventurer supply count is 0
    result = -1;
    state->supplyCount[7] = 0;

    result = supplyCount(adventurer, state);
    
    if (result == 0) {
        printf("supplyCount Test 2 successful\n");
    }
    else {
        printf("supplyCount Test 2 failed\n");
    }
    
    return 0;
}
