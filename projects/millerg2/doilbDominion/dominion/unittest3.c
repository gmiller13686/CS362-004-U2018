/* -----------------------------------------------------------------------
 * Unit test for gainCard()
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int seed = 950;
    int numPlayer = 2;
    int player = 0;
    int deckCount;
    int handCount;
    int discardCount;
 

    int k[10] = {adventurer, steward, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};

    printf("**************************************\n");
    printf("Testing gainCard()\n");
    printf("**************************************\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    G.supplyCount[gold] = 30;
    deckCount = G.deckCount[player];
    gainCard(gold,&G,1,player);
    printf("Test: Player 0 gains gold card in deck\n");
    testEquiv(deckCount+1,G.deckCount[player]);
    player = 1;

    deckCount = G.deckCount[player];
    gainCard(gold,&G,1,player);
    printf("Test: Player 1 gains gold card in deck\n");
    testEquiv(deckCount+1,G.deckCount[player]);

    player = 0;
    handCount = G.handCount[player];
    gainCard(gold, &G, 2, player);
    printf("Test: Player 0 gains gold card in hand\n");
    testEquiv(handCount+1,G.handCount[player]);

    player = 1;
    handCount = G.handCount[player];
    gainCard(gold, &G, 2, player);
    printf("Test: Player 1 gains gold card in hand\n");
    testEquiv(handCount+1,G.handCount[player]);

    G.supplyCount[adventurer] = 10;
    discardCount = G.discardCount[0];
    printf("Adventurer Count = 10. Try to discard Adventurer 15 times. Should have discardCount = 10\n");
    for (int i = 1; i < 15; i++){
        gainCard(adventurer, &G, 0,0);
    }
  
    testEquiv(discardCount + 10, G.discardCount[0]);

    printf("Check supplyCount gold decreased correctly. Should be 26\n");
    printf("Actual, Expected: %d, %d\n", G.supplyCount[gold], 26);
    testEquiv(26,G.supplyCount[gold]);

    printf("Check supplyCount adventurer decreased correctly. Should be 0\n");
    printf("Actual, Expected: %d, %d\n", G.supplyCount[adventurer], 0);
    testEquiv(0,G.supplyCount[adventurer]);

    G.supplyCount[gold] = 0;
    printf("Test: Gold Empty, cannot gain gold card\n");
    testEquiv(gainCard(gold,&G,0,player), -1);

    printf("Test: Card not used in game\n");
    testEquiv(gainCard(sea_hag,&G,1,player), -1);

    printf("Test: Try to add card for player not in game\n");
    testEquiv(gainCard(gold,&G,0,2),-1);

    printf("\n\n**************************************\n");
    printf("Total Tests Run: %d\n", testCount);
    printf("Tests Failed: %d\n", failedTests);
    if (failedTests) {
        printf("CARD TEST FAILED\n");
    } else {printf("PASSED\n");}
    return 0;



}