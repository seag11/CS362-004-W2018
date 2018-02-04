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
	printf("*          cardtest3.c: smithy             *\n");
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
    
    //player 1 plays smithy - test number of cards in hand
    line = __LINE__;
	cardEffect(smithy, 0, 0, 0, &testState, handpos, &bonus);
	observed = testState.handCount[player];
	expected = state.handCount[player] + 3 - 1;
	printf("Evaluate number of cards in hand after smithy played (+3 cards and discard)\n");
	oracle(observed, expected, line);
	
	//player 1 plays smithy - test number of cards in deck
    line = __LINE__;
	observed = testState.deckCount[player];
	expected = state.deckCount[player] -3;
	printf("Evaluate number of cards in deck after smithy played (-3 cards)\n");
	oracle(observed, expected, line);
	
	//Player 1 plays smithy - test whether +3 cards originated from top of deck
	line = __LINE__;
	memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
	
	//fill deck with unique cards increasing from 0
	state.deckCount[0]=10;
	int i;
	for (i=0;i<state.deckCount[0];i++){
		state.deck[0][i] = i;
	}
	
	//fill hand with smithy cards
	state.handCount[0]=5;
	for (i=0; i<state.handCount[0];i++){
		state.hand[0][i] = 13;
		//printf("%d", state.hand[0][i]);
	}
		
	int expArr[] = {0,0,0};   //fill with cards from top of deck
	
	for(i=0;i<3;i++){
		expArr[i] = state.deck[0][state.deckCount[0]-1-i];
	}
	
	//Print the hand before playing smithy
	printf("Hand before player 1 plays smithy: ");
	for(i=0;i<state.handCount[0]; i++){
		printf("%d ", state.hand[0][i]);
	}
	printf("\n");
	
	cardEffect(smithy, 0, 0, 0, &state, handpos, &bonus);
	
	//Print the hand after playing smithy
	printf("Hand after player 1 plays smithy: ");
	for(i=0;i<state.handCount[0]; i++){
		printf("%d ", state.hand[0][i]);
	}
	printf("\n");
	
	int j;
	int flag;
	for(i=0; i<3; i++){
		printf("Search hand for card from top of deck: %d", expArr[i]);
		flag = 0;
		for (j=0; j<state.handCount[0]; j++){
			if (expArr[i] == state.hand[0][j]){
				printf("\t\t+ TEST SUCCESSFUL +\n");
				flag = 1;
				break;	
			}
		}
		if(flag == 0){
				printf("\t\t-TEST FAILED-\n");
		}
	}  
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
