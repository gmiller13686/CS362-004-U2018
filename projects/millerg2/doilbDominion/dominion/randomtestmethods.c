#include "randomtestmethods.h"




void randomizeSupply(struct gameState* gameSt){
    gameSt->supplyCount[curse] = rand() % 11;

    gameSt->supplyCount[estate] = rand() % 9;
    gameSt->supplyCount[duchy] = rand() % 9;
    gameSt->supplyCount[province] = rand() % 9;

    gameSt->supplyCount[copper] = rand() % 47;
    gameSt->supplyCount[silver] = rand() % 41;
    gameSt->supplyCount[gold] = rand() % 31;
}

void randomizeDeck(struct gameState* gameSt, int player){
    gameSt->deckCount[player] = 0;
    int i = 0;
    int randCard = 0;
    //Keep max size to 0 - 50
    int deckSize = (int) (rand() % 51);
    assert(deckSize >= 0);

    for (i = 0; i < deckSize; i++){
        randCard = rand() % treasure_map + 1;
        gameSt->deck[player][i] = randCard;
        gameSt->deckCount[player]++;
    }

    shuffle(player,gameSt);

}

void randomizeHand(struct gameState* gameSt, int player){
    gameSt->handCount[player] = 0;
    int i = 0;
    int randCard = 0;
    //Keep hand size to 0 - 20
    int handSize = (int) (rand() % 21);
    assert(handSize >= 0);

    for (i = 0; i < handSize; i++){
        randCard = rand() % treasure_map + 1;
        gameSt->hand[player][i] = randCard;
        gameSt->handCount[player]++;
    }
}

void randomizeDiscard(struct gameState* gameSt, int player){
    gameSt->discardCount[player] = 0;
    int i = 0;
    int randCard = 0;
    //Keep discard size to 5 - 50 
    //Make floor 5 to avoid case of deck = hand = discard = 0 
    int discardSize = (int) ((rand() % 51)) + 5;
    assert(discardSize >= 5);

    for (i = 0; i < discardSize; i++){
        randCard = rand() % treasure_map + 1;
        gameSt->discard[player][i] = randCard;
        gameSt->discardCount[player]++;
    }
}

void randomizePlayerState(struct gameState* gameSt, int player){
    gameSt->whoseTurn = player;
    //0 - 4
    gameSt->playedCardCount = rand() % 5;
    gameSt->numActions = rand() % 5;
    gameSt->numBuys = rand() % 5;

}

void randomizeGameState(struct gameState* gameSt, int player){

    randomizeSupply(gameSt);
    randomizeDeck(gameSt, player);
    randomizeHand(gameSt,player);
    randomizeDiscard(gameSt,player);
    randomizePlayerState(gameSt,player);
}

void setDeck(struct gameState* gameSt, int player){    
    gameSt->deckCount[player] = 0;

    //Leave deck empty 10% of the time
    int r = rand() % 100;
    if (r < 10) return;

    int i = 0;
    int randCard = 0;

    //enums 3-4-5 for copper, silver, gold
    for (i = 0; i < SUPPLY_CARDS; i++){
        randCard = (rand() % 3) + copper;
        gameSt->deck[player][i] = randCard;
         gameSt->deckCount[player]++;
    }

    for (i = SUPPLY_CARDS; i < SUPPLY_CARDS + KINGDOM_CARDS; i++){
        //enums 8 - 26 for kingdom cards.
        randCard = (rand() % (treasure_map - adventurer) + council_room);
        gameSt->deck[player][i] = randCard;
        gameSt->deckCount[player]++;
    }
    //shuffle player deck
    shuffle(player, gameSt);

}
 




void randomizeAdventurerTest(struct gameState* gameSt, int player){

    randomizeSupply(gameSt);
    setDeck(gameSt, player);
    randomizeHand(gameSt,player);
    randomizeDiscard(gameSt,player);
    randomizePlayerState(gameSt,player);
}


