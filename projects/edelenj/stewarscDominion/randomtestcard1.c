#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void oracle(int observed, int expected, int *goodTests);

int main(int argc, char **argv)
{
	printf("********************************************\n");
	printf("*       randomtestcard1.c: cutpurse         *\n");
	printf("********************************************\n");
	int seed = 1000;
	int goodTests = 0;
    int numPlayers = 4;
    int handpos = 0, bonus = 0;
    int player = 0;
    int MAX_COINS = ((60-(7*numPlayers)) + 40 + 30);
	struct gameState after, before;
	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
    
    srand(seed);
    
    //Test + 2 coins for player 1
    int i;
    for (i=0; i<10000; i++){
		memset(&after, '\0', sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayers, k, seed, &after);

		//add random type and number of Kingdom cards hand
		after.handCount[player] = 0;
		int additionalCards = rand() % MAX_HAND;
		int j;
		for (j=0;j<additionalCards; j++){
			after.hand[player][after.handCount[player]] = (rand() % (treasure_map + 1 - 7)) + 7;
			after.handCount[player]++;
		}
		
		//add random type and number of Treasure cards to deck
		after.deckCount[player] = 0;
		int numCoins = rand() % MAX_COINS;
		int k;
		for (k=0;k<numCoins; k++){
			after.deck[player][after.deckCount[player]] = (rand() % 3) + copper;
			after.deckCount[player]++;
		}
		
		memcpy (&before, &after, sizeof(struct gameState));  //source = after, destination = before
		cardEffect(cutpurse, 0, 0, 0, &after, handpos, &bonus);
		updateCoins(player, &before, 0);
		
		oracle(after.coins, before.coins+2, &goodTests);
	} 
	printf("Tested +2 coins for player 1: %d passed out of %d\n", goodTests, i);
	
	goodTests=0;
	//Test -1 coppers for players 2-4
	for (i=0; i<10000; i++){
		memset(&after, '\0', sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayers, k, seed, &after);
		int j;
		for (j=1; j<numPlayers; j++){
			//add random type and number of cards to hand (includes Kingdom, Treasure, and Victory cards)
			after.handCount[j] = 0;
			int additionalCards = rand() % MAX_HAND;
			int c;
			for (c=0;c<additionalCards; c++){
				after.hand[j][after.handCount[j]] = rand() % (treasure_map + 1);
				after.handCount[j]++;
			}
		}

		memcpy (&before, &after, sizeof(struct gameState));  //source = after, destination = before

		//test for 0 coppers in hand
		int p;
		for (p=1; p<numPlayers; p++){
			updateCoins(p, &before, 0);
			int handCoppers = 0;
			int pos = 0;
			int x;
			for (x=0; x<before.handCount[p]; x++){
				if (before.hand[p][x] == copper){
					handCoppers++;
					pos = x;
				}
			}
			if(handCoppers == 0){
				//show hand
			}
			else{
				discardCard(pos, p, &before, 0);
			}
		}
		
		cardEffect(cutpurse, 0, 0, 0, &after, handpos, &bonus);
		
		for (p=1; p<numPlayers; p++){
			after.whoseTurn = before.whoseTurn = p;
			updateCoins(p, &before, 0);
			updateCoins(p, &after, 0);
			oracle(after.coins, before.coins, &goodTests);	
		}			
	}
	printf("Tested -1 coins for players 2-4: %d passed out of %d\n", goodTests, i*3);
	
	return 0;
}


void oracle(int observed, int expected, int *goodTests){
	//printf("Observed = %d, Expected = %d ", observed, expected);
	if(observed == expected){
		//printf("\t\t+ TEST SUCCESSFUL +\n");
		(*goodTests)++;
	}
	else{
		printf("\t\t-TEST FAILED- \n");
		printf("Observed = %d, Expected = %d ", observed, expected);
	}
	
}
