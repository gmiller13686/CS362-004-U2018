/* -----------------------------------------------------------------------
 * Unit test for cardSmithy()
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

int failedTests = 0;
int testCount = 0;

void testEquiv(int expected, int actual) {
    testCount++;
    printf("Expected: %d Actual: %d\n", expected, actual);
    if (expected == actual) {printf("Passed\n");}
    else {
        printf("Failed\n");
        failedTests++;
    }
}

int main() {
    
    struct gameState originalGameState;
    struct gameState postGameState;
    int seed = 1000;
    int numPlayer = 2;
    int player0 = 0;
    int choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0, handPos = 0;
    int expected = 0, actual = 0, supplyMismatch = 0, i = 0;
    int expectedNewCards = 3;
    int expectedCardsPlayed = 1;

    int k[10] = {adventurer, steward, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};


    printf("**************************************\n");
    printf("Testing cardSmithy()\n");
    printf("**************************************\n");

    memset(&originalGameState, 23, sizeof(struct gameState));
    memset(&postGameState, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &originalGameState);
    addCardToHand(player0, smithy, &originalGameState);
    handPos = 5;
    memcpy(&postGameState,&originalGameState,sizeof(struct gameState));

    cardEffect(smithy,choice1,choice2,choice3,&postGameState,handPos,&bonus);

    printf("Test: Player hand count.\n");
    expected = originalGameState.handCount[player0] + expectedNewCards - expectedCardsPlayed;
    actual = postGameState.handCount[player0];
    testEquiv(expected, actual);

    printf("Test: Played card count.\n");
    expected = originalGameState.playedCardCount + expectedCardsPlayed;
    actual = postGameState.playedCardCount;
    testEquiv(expected, actual);

    expected = originalGameState.coins;
    actual = postGameState.coins;
    printf("Test: Coin count.\n");
    testEquiv(expected, actual);


    printf("Test: Discard count.\n");
    expected = expectedNewCards + originalGameState.handCount[player0] - expectedCardsPlayed;
    endTurn(&postGameState);
    endTurn(&originalGameState);
    actual = postGameState.discardCount[player0];
    testEquiv(expected, actual);


    printf("Test: Supply card counts unchanged.\n");
    for (i = 0; i < treasure_map + 1; i++) {
	    if (originalGameState.supplyCount[i] != postGameState.supplyCount[i]) {
		supplyMismatch = 1;
		break;
	    }
	}
	if (!supplyMismatch) {
        testCount++;
	    printf("PASSED: Supply counts unchanged\n");
	} else {
        testCount++;
        failedTests++;
	    printf("FAILED: Supply counts don't match at %d\n", i);
	}  

    printf("\n\n**************************************\n");
    printf("Totel Tests Run: %d\n", testCount);
    printf("Tests Failed: %d\n", failedTests);
    if (failedTests) {
        printf("CARD TEST FAILED\n");
    } else {printf("PASSED\n");}
    return 0;

}
