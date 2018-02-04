#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void oracle(int observed, int expected, int line);

int main(int argc, char **argv)
{
	printf("********************************************\n");
	printf("*        cardtest1.c: council_room         *\n");
	printf("********************************************\n");
	int seed = 1000, line;
    int numPlayers = 4;
    int expected, observed;
    int handpos = 0, bonus = 0;
    int player = 0;
	struct gameState state, testState;
	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
                
    //+4 newcards
    line = __LINE__;
    int newcards = 4;
    int discard = 1;
    memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
    memcpy(&testState, &state, sizeof(struct gameState));		// copy game state to test
    cardEffect(council_room, 0, 0, 0, &testState, handpos, &bonus);
    printf("Testing +4 new cards to hand\n");
    observed = testState.handCount[player];
    expected = state.handCount[player] + newcards - discard;
    oracle(observed,expected,line);
    printf("Testing -4 cards from deck\n");
    observed = testState.deckCount[player];
    expected = state.deckCount[player] - newcards;
    oracle(observed,expected,line);
	
	
	//+1 buy
	line = __LINE__;
    memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
    memcpy(&testState, &state, sizeof(struct gameState));		// copy game state to test
    cardEffect(council_room, 0, 0, 0, &testState, handpos, &bonus);
    printf("Testing +1 buy\n");
    observed = testState.numBuys;
    expected = state.numBuys + 1;
    oracle(observed,expected,line);
    
	
	//each other player draws card
	line = __LINE__;
	memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
    memcpy(&testState, &state, sizeof(struct gameState));		// copy game state to test
    cardEffect(council_room, 0, 0, 0, &testState, handpos, &bonus);
	int i;
	for (i=1; i<numPlayers; i++){
		printf("Testing player %d draws a card\n", i+1);
		observed = testState.handCount[i];
		expected = state.handCount[i]+1;
		oracle(observed, expected, line);
	}
	
	return 0;
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
