#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void oracle(int observed, int expected, int line);
void printArr(int arr[], int size);

int main(int argc, char **argv)
{
	printf("********************************************\n");
	printf("*        cardtest4.c: adventurer           *\n");
	printf("********************************************\n");
	int seed = 1000, line;
    int numPlayers = 2;
    int expected, observed;
    int handpos = 0, bonus = 0;
    int player = 0;
	struct gameState state, testState;
	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
                
    memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
    memcpy(&testState, &state, sizeof(struct gameState));		// copy game state to test
    
    //player starts with 7 coppers and 3 estates
    
    //+2 cards
    line = __LINE__;
    printf("Evaluate +2 cards when playing adventurer\n");
    cardEffect(adventurer, 0, 0, 0, &testState, handpos, &bonus);
    observed = testState.handCount[player];
    expected = state.handCount[player] + 2 - 1;  //(+2 minus discard)
    oracle(observed, expected, line);
    
    //+2 coins
    line = __LINE__;
    printf("Evaluate +2 coins when playing adventurer\n");
    observed = testState.coins;
    expected = state.coins + 2;
    oracle(observed, expected, line);
    
    //test total number of cards are the same
    line = __LINE__;
    printf("Ensure overall card count stays same after playing adventurer\n");
    memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
    
    expected = state.handCount[player] + state.discardCount[player] + state.deckCount[player];
    cardEffect(adventurer, 0, 0, 0, &state, handpos, &bonus);
    observed = state.handCount[player] + state.discardCount[player] + state.deckCount[player];
    oracle(observed,expected,line);
    
    //test when deck is empty
    line = __LINE__;
    printf("Evaluate discard -> shuffle -> deck behavior when deck is empty\n");
    memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
    state.deckCount[player] = 0;
    
    
    state.discardCount[player] = 10;
    int i;
    for (i=0; i<state.discardCount[player]; i++){
		state.discard[player][i] = i;
	}
    
    printf("Hand before playing adventurer: ");
    printArr(state.hand[player], state.handCount[player]);
    
    cardEffect(adventurer, 0, 0, 0, &state, handpos, &bonus);
    
    printf("Hand after playing adventurer: ");
    printArr(state.hand[player], state.handCount[player]);	
    
}


void oracle(int observed, int expected, int line){
	printf("Observed = %d, Expected = %d ", observed, expected);
	if(observed == expected){
		printf("\t\t+ TEST SUCCESSFUL +\n");
	}
	else{
		printf("\t\t-TEST FAILED- (line nbr %d)\n", line);
	}
	
}

void printArr(int arr[], int size){
	int i;
	for(i=0;i<size;i++){
		printf("%d\t", arr[i]);
	}
	printf("\n");
}
