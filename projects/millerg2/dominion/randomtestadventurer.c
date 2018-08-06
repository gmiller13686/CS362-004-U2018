#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



//Random test generator for Adventurer card
int main() {

int index;
int inputError = 0;
int handcountError = 0;
int discardcountError = 0;
int successfulTest = 0;

//Seed the random number generator
srand(time(NULL));

//Begin randomizing and testing
for(index = 0; index < 2000; index++) {
    int currentPlayer;
    int i;
    int handPos;
    int result;
    int expectedHandcount;
    int expectedDiscardcount;
    struct gameState state;
    struct gameState* pointState;

    //Set random person's turn (Range 0-3)
    state.whoseTurn = rand() % 4; 
    currentPlayer = state.whoseTurn;

    //Set player's played card count (Range 0-20)
    state.playedCardCount = rand() % 21;

    //Set player's deck count (Range 0-20)
    state.deckCount[currentPlayer] = rand() % 21;

    //Set player's discard count (Range 0-20)
    state.discardCount[currentPlayer] = rand() % 21;

    //Assign cards to the discard pile
    for(i = 0; i < state.discardCount[currentPlayer]; i++) {
        state.discard[currentPlayer][i] = rand() % 27;
    }

    //Set player's hand count (Range 1-10) and the expectedHandcount after card is played
    state.handCount[currentPlayer] = (rand() % 10) + 1;
    expectedHandcount = state.handCount[currentPlayer] + 2;    

    //Set cards in player's hand (Range 0-26)
    for(i = 0; i < state.handCount[currentPlayer]; i++) {
        state.hand[currentPlayer][i] = rand() % 27;
    }

    //Set handPos of the card being played
    handPos = rand() % state.handCount[currentPlayer];

    //Set handPos index in player's hand to the card being played (Adventurer Card is 7)
    state.hand[currentPlayer][handPos] = 7;

    //Set the expected discard count for after card is played
    if (state.deckCount[currentPlayer] == 0) {
        expectedDiscardcount = 0;
    }
    else {
        expectedDiscardcount = state.discardCount[currentPlayer];
    }

    //Call the adventurerCard function
    result = -1;
    pointState = &state;
    result = adventurerCard(pointState, handPos, currentPlayer);
    
    //Get results
    if (result != 0) {
        inputError++;
    }
    else if(state.handCount[currentPlayer] != expectedHandcount) {
        handcountError++;
    }
    else if(state.discardCount[currentPlayer] != expectedDiscardcount) {
        discardcountError++;
    }
    else {
        successfulTest++;
    }
}
    //Print results
    printf("Results for Adventurer card test: \n");
    printf("Number of successful tests: %d\n", successfulTest);
    printf("Number of input errors: %d\n", inputError);

    return 0;
}
