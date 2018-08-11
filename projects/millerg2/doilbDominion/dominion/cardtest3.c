/* -----------------------------------------------------------------------
 * Unit test for cardSteward()
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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
    int numChoices = 3;
    int choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0, handPos = 0;
    int expected = 0, actual = 0;
    int expectedNewCards = 0;
    int expectedCardsPlayed = 1;
    int expectedNewCoins = 0;
    int expectedTrashedCards = 0;
    

    int k[10] = {adventurer, steward, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};

    printf("**************************************\n");
    printf("Testing cardSteward()\n");
    printf("**************************************\n");
    for (choice1 = 1; choice1 <= numChoices; choice1++){
        if (choice1 == 1) {
             printf("Testing Choice: +2 Cards.\n");
             expectedNewCards = 2;
             expectedNewCoins = 0;
             expectedTrashedCards = 0;
        }       
        else if (choice1 == 2) {
            printf("Testing Choice: +2 Coins.\n"); 
            expectedNewCards = 0;
            expectedNewCoins = 2;
            expectedTrashedCards = 0;
        }
        else {
            printf("Test: Trash 2 Cards From Hand.\n");
            expectedNewCards = 0;
            expectedNewCoins = 0;
            expectedTrashedCards = 2;
        }

        memset(&originalGameState, 23, sizeof(struct gameState));
        memset(&postGameState, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &originalGameState);
        memcpy(&postGameState,&originalGameState,sizeof(struct gameState));

        //printHand(player0, &postGameState);
        cardEffect(steward,choice1,choice2,choice3,&postGameState,handPos,&bonus);

        printf("Test: Player Hand Count.\n");
        expected = originalGameState.handCount[player0] + expectedNewCards - expectedCardsPlayed - expectedTrashedCards;
        actual = postGameState.handCount[player0];
        testEquiv(expected,actual);

        printf("Test: Player Deck Count.\n");
        expected = originalGameState.deckCount[player0] - expectedNewCards;
        actual = postGameState.deckCount[player0];
        testEquiv(expected, actual);

        printf("Test: Player Played Count.\n");
        expected = originalGameState.playedCardCount + expectedCardsPlayed;
        actual = postGameState.playedCardCount;
        testEquiv(expected, actual);

        printf("Test: Coin Count.\n");
        expected = originalGameState.coins + expectedNewCoins;
        actual = postGameState.coins;
        testEquiv(expected,actual);

        printf("Test: Player Discard Count.\n");
        expected = originalGameState.handCount[player0] + expectedNewCards - expectedCardsPlayed - expectedTrashedCards;
        endTurn(&originalGameState);
        endTurn(&postGameState);
        actual = postGameState.discardCount[player0];
        testEquiv(expected, actual);

    }
    printf("\n\n**************************************\n");
    printf("Totel Tests Run: %d\n", testCount);
    printf("Tests Failed: %d\n", failedTests);
    if (failedTests) {
        printf("CARD TEST FAILED\n");
    } else {printf("PASSED\n");}
    return 0;

}
