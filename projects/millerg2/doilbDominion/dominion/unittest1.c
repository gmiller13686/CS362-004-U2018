/* -----------------------------------------------------------------------
 * Unit test for isGameOver()
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int failedTests = 0;
int testCount = 0;

void testEquiv(int a, int b) {
    testCount++;
    if (a == b) {printf("Passed\n");}
    else {
        printf("Failed\n");
        failedTests++;
    }
}

int main() {
    
    struct gameState G;
    int seed = 1000;
    int numPlayer = 2;

    int k[10] = {adventurer, steward, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};

    printf("**************************************\n");
    printf("Testing isGameOver()\n");
    printf("**************************************\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    printf("Test: Game Initialized\n");
    testEquiv(isGameOver(&G), 0);

    G.supplyCount[province] = 0;
    printf("Test: Province Card Stack Empty\n");
    testEquiv(isGameOver(&G), 1);

    //Change province stack to 1
    G.supplyCount[province] = 1;
    //Empty 3 other supply piles
    G.supplyCount[curse] = 0;
    G.supplyCount[estate] = 0;
    G.supplyCount[duchy] = 0;
    printf("Test: Supply Piles Empty\n");
    testEquiv(isGameOver(&G), 1);

    printf("Test: Supply & Province Piles Full\n");
    G.supplyCount[province] = 1;
    G.supplyCount[curse] = 1;
    G.supplyCount[estate] = 1;
    G.supplyCount[duchy] = 1;
    testEquiv(isGameOver(&G), 0);


    printf("\n\n**************************************\n");
    printf("Total Tests Run: %d\n", testCount);
    printf("Tests Failed: %d\n", failedTests);
    if (failedTests) {
        printf("CARD TEST FAILED\n");
    } else {printf("PASSED\n");}
    return 0;
}


