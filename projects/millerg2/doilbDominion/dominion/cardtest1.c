/* -----------------------------------------------------------------------
 * Unit test for cardAdventurer()
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
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

#define VERBOSE 0

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
    //int player1 = 1;
    int choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0, handPos = 0;
    int expected = 0, actual = 0, supplyMismatch = 0, i = 0;
    int expectedNewCards = 2;
    int expectedCardsPlayed = 1;
    
    int k[10] = {adventurer, steward, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};

    printf("**************************************\n");
    printf("Testing cardAdventurer()\n");
    printf("**************************************\n");

    memset(&originalGameState, 23, sizeof(struct gameState));
    memset(&postGameState, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &originalGameState);
    //Add the card to hand
    memcpy(&postGameState,&originalGameState,sizeof(struct gameState));

    printf("Player 0 plays adventurer.\n");    
    cardEffect(adventurer,choice1,choice2,choice3,&postGameState,handPos,&bonus);

    printf("Test: Player hand count.\n");
    expected = originalGameState.handCount[player0] + expectedNewCards - expectedCardsPlayed;
    if (VERBOSE) printHand(player0, &originalGameState);
    actual = postGameState.handCount[player0];
    if (VERBOSE) printHand(player0, &postGameState);
    testEquiv(expected, actual);

    printf("Test: Played card count.\n");
    expected = originalGameState.playedCardCount + expectedCardsPlayed;
    if (VERBOSE) printPlayed(player0, &originalGameState);
    actual = postGameState.playedCardCount;
    if (VERBOSE) printPlayed(player0, &postGameState);
    testEquiv(expected, actual);

    expected = originalGameState.coins;
    actual = postGameState.coins;
    printf("Test: Coin count.\n");
    testEquiv(expected, actual);

    printf("Test: Discard count.\n");
    expected = expectedNewCards + originalGameState.handCount[player0] - expectedCardsPlayed;
    endTurn(&postGameState);
    endTurn(&originalGameState);
    if (VERBOSE) printDiscard(player0, &originalGameState);
    if (VERBOSE) printDiscard(player0, &postGameState);
    actual = postGameState.discardCount[player0];
    testEquiv(expected, actual);

    if (VERBOSE) printSupply(&originalGameState);
    if (VERBOSE) printSupply(&postGameState);
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
