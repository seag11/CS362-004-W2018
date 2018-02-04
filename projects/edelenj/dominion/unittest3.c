
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int numPassed = 0;
int countTotal(int arr[], int size, struct gameState *state, int player);
void oracle(int observed, int expected, int line);
void printArr(int arr[], int size);

int main(int argc, char **argv)
{
	printf("********************************************\n");
	printf("*           unittest3.c: scoreFor          *\n");
	printf("********************************************\n");
	
	int score, line;
	int seed = 10;  //10
	int numPlayer = 2;
	int functionTotal;
	int numTests;
	
	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
	
	numTests = 0;	
	struct gameState state;
	
	// toFlag = 0 : add to discard
	// toFlag = 1 : add to deck
	// toFlag = 2 : add to hand
		
	int i;
	for(i=0; i<3; i++){	//iterate coins
		//Test 1:  evaluate basic victory cards in hand
		line = __LINE__;
		printf("Test Player 1: add %d estate, %d duchy, %d province to hand at round 1\n", i+1, i+1, i+1);
		memset(&state, '\0', sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &state);  //initialize game
		state.deckCount[0] = 0; 
		state.discardCount[0] = 0;
		state.handCount[0] = 0;   
		int z;
		for (z=0; z<i+1; z++){										
			gainCard(estate, &state, 2, 0);
			gainCard(duchy, &state, 2, 0);
			gainCard(province, &state, 2, 0);
		}
		functionTotal = 0;
		functionTotal += countTotal(state.hand[0], state.handCount[0], &state, 0);
		score = scoreFor (0, &state);
		oracle(score, functionTotal, line);
		numTests++;
		
		
		//Test 2: evaluate basic victory cards in deck
		line = __LINE__;
		printf("Test Player 1: add %d estate, %d duchy, %d province to deck at round 1\n", i+1, i+1, i+1);
		memset(&state, '\0', sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &state);  //initialize game
		state.deckCount[0] = 0; 
		state.discardCount[0] = 0;
		state.handCount[0] = 0; 
		for (z=0; z<i+1; z++){
			gainCard(estate, &state, 1, 0);
			gainCard(duchy, &state, 1, 0);
			gainCard(province, &state, 1, 0);
		}
		functionTotal = 0;
		functionTotal = functionTotal + countTotal(state.deck[0], state.deckCount[0], &state, 0);
		score = scoreFor (0, &state);
		oracle(score, functionTotal, line);
		numTests++;
		
		//Test 3: evaluate basic victory cards in discard
		line = __LINE__;
		printf("Test Player 1: add %d estate, %d duchy, %d province to discard at round 1\n", i+1, i+1, i+1);
		memset(&state, '\0', sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &state);  //initialize game
		state.discardCount[0] = 0;  
		state.deckCount[0] = 0; 
		state.handCount[0] = 0; 
		for (z=0; z<i+1; z++){
			gainCard(estate, &state, 0, 0);
			gainCard(duchy, &state, 0, 0);
			gainCard(province, &state, 0, 0);
		}
		functionTotal = 0;
		functionTotal += countTotal(state.discard[0], state.discardCount[0], &state, 0);
		score = scoreFor (0, &state);
		oracle(score, functionTotal, line);
		numTests++;
		
		//Test 4: evaluate gardens
		line = __LINE__;
		printf("Test Player 1: add %d garden to hand and 10 coppers to deck at round 1\n", i+1);
		memset(&state, '\0', sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &state);  //initialize game
		state.deckCount[0] = 0;  
		state.discardCount[0] = 0;
		state.handCount[0] = 0; 
		for (z=0; z<i+1; z++){
			gainCard(gardens, &state, 2, 0);
		}
		int j;
		for (j=0; j<10; j++){
			gainCard(copper, &state, 1, 0);
		}
		
		functionTotal = 0;
		functionTotal += countTotal(state.hand[0], state.handCount[0], &state, 0);
		functionTotal += countTotal(state.deck[0], state.deckCount[0], &state, 0);
		functionTotal += countTotal(state.discard[0], state.discardCount[0], &state, 0);
		score = scoreFor (0, &state);
		oracle(score, functionTotal, line);
		numTests++;
		
		//Test 5: evaluate great_hall
		line = __LINE__;
		printf("Test Player 1: add %d great hall to hand and %d great hall to deck at round 1\n", i+1, i+1);
		memset(&state, '\0', sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &state);  //initialize game
		state.deckCount[0] = 0;  
		state.discardCount[0] = 0;
		state.handCount[0] = 0; 
		for (z=0; z<i+1; z++){
			gainCard(great_hall, &state, 2, 0);
			gainCard(great_hall, &state, 1, 0);
		}
		
		functionTotal = 0;
		functionTotal += countTotal(state.hand[0], state.handCount[0], &state, 0);
		functionTotal += countTotal(state.deck[0], state.deckCount[0], &state, 0);
		functionTotal += countTotal(state.discard[0], state.discardCount[0], &state, 0);
		score = scoreFor (0, &state);
		oracle(score, functionTotal, line);
		numTests++;
		
	}
	
	printf("%d tests passed out of %d\n", numPassed, numTests);
		
	return 0;
}

int countTotal(int arr[], int size, struct gameState *state, int player){
	int runningTotal = 0;
	int i;
	//printArr(arr, size);
		
	for (i=0; i<size; i++){
		if (arr[i] == estate || arr[i] == great_hall){
			//printf("estate registered\n");
			runningTotal += 1;
		}
		else if(arr[i] == duchy){
			//printf("duchy registered\n");
			runningTotal += 3;
		}
		else if(arr[i] == province){
			//printf("province registered\n");
			runningTotal += 6;
		}
		else if(arr[i] == gardens){
			int numCards = 0;
			numCards += state->handCount[player];
			numCards += state->discardCount[player];
			numCards += state->deckCount[player];
			//printf("** Gardens invoked ** Total cards: %d\n", numCards);
			runningTotal += (numCards / 10);
		}
	}
	//printf("Returning running total: %d\n",runningTotal);
	return runningTotal;	
}

void oracle(int observed, int expected, int line){
	printf("Observed = %d, Expected = %d ", observed, expected);
	if(observed == expected){
		printf("\t\t+ TEST SUCCESSFUL +\n");
		numPassed++;
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

