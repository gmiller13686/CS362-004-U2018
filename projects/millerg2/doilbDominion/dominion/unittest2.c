/* -----------------------------------------------------------------------
 * Unit test for updateCoins()
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
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
    int player = 0;
    int bonus = 1;
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int maxHandCount = 5;

    for (int i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    int k[10] = {adventurer, steward, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};

    printf("**************************************\n");
    printf("Testing updateCoins()\n");
    printf("**************************************\n");
    for (int handCount = 1; handCount <= maxHandCount; handCount++){
        memset(&G, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);
        G.handCount[player] = handCount;

        memcpy(G.hand[player],coppers,sizeof(int)*handCount);
        updateCoins(player, &G, bonus);
        printf("Test: All Copper Hand\n");
        printf("HandCount: %d: Actual, Expected: %d, %d\n",handCount, G.coins, handCount*1+bonus);
        testEquiv(G.coins, handCount*1+bonus);

        memcpy(G.hand[player],silvers,sizeof(int)*handCount);
        updateCoins(player, &G, bonus);
        printf("Test: All Silver Hand\n");
        printf("HandCount: %d: Actual, Expected: %d, %d\n",handCount, G.coins, handCount*2+bonus);
        testEquiv(G.coins, handCount*2+bonus);

        memcpy(G.hand[player],golds,sizeof(int)*handCount);
        updateCoins(player, &G, bonus);
        printf("Test: All Gold Hand\n");
        printf("HandCount: %d: Actual, Expected: %d, %d\n",handCount, G.coins, handCount*3+bonus);
        testEquiv(G.coins, handCount*3+bonus);

        bonus++;
    }
 



    printf("\n\n**************************************\n");
    printf("Total Tests Run: %d\n", testCount);
    printf("Tests Failed: %d\n", failedTests);
    if (failedTests) {
        printf("CARD TEST FAILED\n");
    } else {printf("PASSED\n");}
    return 0;
}


