#include "dominion.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

//Unit test for getCost function
int main() {
    int i;
    int result = -1;
    struct gameState* state;

    //Test 1: Get cost of Silver
    result = getCost(5);

    if (result == 3) {
        printf("getCost Test 1 successful\n");
    }
    else {
        printf("getCost Test 1 failed\n");
    }

    //Test 2: Get cost of Minion
    result = -1;
    result = getCost(17);
    
    if (result == 5) {
        printf("getCost Test 2 successful\n");
    }
    else {
        printf("getCost Test 2 failed\n");
    }

    //Test 3: Get cost of a non-existent card
    result = 0;
    result = getCost(90);
    
    if (result == -1) {
        printf("getCost Test 3 successful\n");
    }
    else {
        printf("getCost Test 3 failed\n");
    }

    return 0;    
}
