
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
	printf("********************************************\n");
	printf("*           unittest2.c: isGameOver         *\n");
	printf("********************************************\n");
	
	int res;
	int seed = 10;
	int numPlayer = 2;
	
	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
	
	struct gameState state;
	memset(&state, '\0', sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &state);  //initialize game

	//Test province card to determine end game
	printf("-> Deplete Province card to determine end game\n");
	int tempProvince = state.supplyCount[province];  //store province
		
	int i;
	for (i=8; i>=0; i--){
		state.supplyCount[province] = i;
		res = isGameOver(&state);
		printf("Testing isGameOver at %d province cards left\n",i);
		if (i >= 1 && res == 0){
			printf("+ TEST SUCCESSFUL +\n"); 
		}
		else if (i >= 1 && res == 1){
			printf("-TEST FAILED-\n");
		}
		else if (i < 1 && res == 1){
			printf("+ TEST SUCCESSFUL +\n"); 
		}
		else if (i < 1 && res == 0){
			printf("-TEST FAILED-\n");
		}
	}

	state.supplyCount[province] = tempProvince;  //restore province
	
	//Test supply piles to determine end game 
	printf("-> Test supply piles to determine end game\n");
	//printf("Treasure map = %d\n", treasure_map);
	
	//int i;
	for (i=0; i<treasure_map+1; i+=3){
		//temporarily store card supplies
		int temp1 = state.supplyCount[i];
		int temp2 = state.supplyCount[i+1];
		int temp3 = state.supplyCount[i+2];
		
		state.supplyCount[i] = 0;
		state.supplyCount[i+1] = 0;
		state.supplyCount[i+2] = 0;
		res = isGameOver(&state);
		printf("Deplete supply cards %d, %d, %d \n", i, i+1, i+2);
		if (res == 1){
			printf("+ TEST SUCCESSFUL +\n"); 
		}
		else{
			printf("-TEST FAILED-\n");
		}
		//restore card supplies
		state.supplyCount[i] = temp1;
		state.supplyCount[i+1] = temp2;
		state.supplyCount[i+2] = temp3;
	}
	
	return 0;
}

