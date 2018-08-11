/* -----------------------------------------------------------------------
 * Unit test for shuffle()
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

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

int compare(const void* a, const void* b);

int main() {
    
    struct gameState G;
    struct gameState G2;
    int seed = 800;
    int numPlayer = 2;
    int player = 0;
    int post;

    int k[10] = {adventurer, steward, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};

    printf("**************************************\n");
    printf("Testing shuffle()\n");
    printf("**************************************\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    printf("Test: Shuffle empty deck.\n");
    G.deckCount[player] = 0;
    testEquiv(shuffle(player,&G), -1);

    printf("Test: Deck of 10. Check deckCount.\n");
    G.deckCount[player] = 10;
    shuffle(player,&G);
    testEquiv(G.deckCount[player],10);

    printf("Copy gameState and shuffle.\n");
    memcpy(&G2, &G, sizeof(struct gameState));
    post = shuffle(player, &G);
    if (post != -1){
        qsort((void*)(G.deck[player]), G.deckCount[player], sizeof(int), compare);
        qsort((void*)(G2.deck[player]), G2.deckCount[player], sizeof(int), compare);
    }    
    
    printf("Test: Game States Equivalent\n");
    if (memcmp(&G,&G2, sizeof(struct gameState)) == 0){
        testEquiv(1,1);
    } else {testEquiv(0,1);}

    
    printf("\n\n**************************************\n");
    printf("Total Tests Run: %d\n", testCount);
    printf("Tests Failed: %d\n", failedTests);
    if (failedTests) {
        printf("CARD TEST FAILED\n");
    } else {printf("PASSED\n");}
    return 0;
}
