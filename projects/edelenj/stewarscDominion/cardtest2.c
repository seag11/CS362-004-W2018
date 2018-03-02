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
	printf("*         cardtest2.c: cutpurse            *\n");
	printf("********************************************\n");
	int seed = 1000, line;
    int numPlayers = 4;
    int expected, observed;
    int handpos = 0, bonus = 0;
    int player = 0;
	struct gameState state;
	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
                           
    memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
    
    //Test 1: +2 coins, each player discards a copper
    //all players dealt 5 coppers
    int i, j;
    for (i=0; i<numPlayers; i++){
		state.handCount[i] = 5;
		for (j=0; j<5; j++){
			state.hand[i][j] = copper;			
		}
		updateCoins(i, &state, bonus);	
	}
	
	//player 1 plays cutpurse
	cardEffect(cutpurse, 0, 0, 0, &state, handpos, &bonus);
	
	//test +2 coins for player 1
	printf("Testing +2 coins for player 1 after player 1 plays cutpurse\n");
	line = __LINE__;
	oracle(state.coins, 7, line);
	
	//test -1 coppers for players 2-4
	line = __LINE__;
	int a;
	for (a=1; a<numPlayers; a++){
		printf("Testing -1 coppers in player %d's hand after player 1 plays cutpurse\n", a+1);
		int numCoppers = 0;
		for (i=0; i<state.handCount[a]; i++){
			if (state.hand[a][i] == copper){
			numCoppers++;
			}
		}
		oracle(numCoppers,4,line);	
	}
	
	//Test 2: Reveal hand with no copper
	printf("Testing players 2-4 reveal hand with no copper\n");
	memset(&state, '\0', sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, k, seed, &state);
	
	//all players dealt 5 gold
    for (i=0; i<numPlayers; i++){
		state.handCount[i] = 5;
		for (j=0; j<5; j++){
			state.hand[i][j] = gold;			
		}
		updateCoins(i, &state, bonus);	
	}
	   
	//player 1 plays cutpurse
	cardEffect(cutpurse, 0, 0, 0, &state, handpos, &bonus);
	
	//test 0 discards for players 2-4
	for (i=1; i<numPlayers; i++){
		printf("Testing 0 discards for player %d\n", i+1);
		oracle(state.handCount[i], 5, line);		
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

