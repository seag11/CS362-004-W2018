#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void oracle(int observed, int expected, int *goodTests, struct gameState state);

int main(int argc, char **argv)
{
	printf("********************************************\n");
	printf("*        randomtestcard2.c: smithy         *\n");
	printf("********************************************\n");
	int seed = 99;
	int goodTests = 0;
    int numPlayers = 4;
    int handpos = 0, bonus = 0;
    int player = 0;
	struct gameState after, before;
	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
    
    srand(seed);
    
    int i;
    for (i=0; i<100000; i++){
		memset(&after, '\0', sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayers, k, seed, &after);

		//add random type and number of cards to hand
		after.handCount[player] = 0;
		int handcards = rand() % MAX_HAND;
		int j;
		for (j=0;j<handcards; j++){
			after.hand[player][after.handCount[player]] = (rand() % (treasure_map + 1));
			after.handCount[player]++;
		}
		
		//add random type and number of cards to deck
		after.deckCount[player] = 0;
		int deckcards = rand() % MAX_DECK;
		int k;
		for (k=0;k<deckcards; k++){
			after.deck[player][after.deckCount[player]] = (rand() % (treasure_map + 1));
			after.deckCount[player]++;
		}
		
		//add random type and number of cards to discard
		after.discardCount[player] = 0;
		int discardcards = rand() % MAX_DECK;
		int h;
		for (h=0;h<discardcards; h++){
			after.discard[player][after.discardCount[player]] = (rand() % (treasure_map + 1));
			after.discardCount[player]++;
		}

		memcpy (&before, &after, sizeof(struct gameState));  //source = after, destination = before
		cardEffect(smithy, 0, 0, 0, &after, handpos, &bonus);
		
		//Edge case detection for too few cards in deck and discard
		int additionalCards;
		switch(before.deckCount[player] + before.discardCount[player]){
			case 0 :
				additionalCards = 0;
				break;
			case 1 :
				additionalCards = 1;
				break;
			case 2 :
				additionalCards = 2;
				break;
			default :
				additionalCards = 3;
				break;			
		}
		
		oracle(after.handCount[player], before.handCount[player]+additionalCards-1, &goodTests, before);
		
	} 
	printf("Tested +3 cards for player 1: %d passed out of %d\n", goodTests, i);
	
	return 0;
}


void oracle(int observed, int expected, int *goodTests, struct gameState state){
	//printf("Observed = %d, Expected = %d \n", observed, expected);
	if(observed == expected){
		printf("Observed = %d, Expected = %d \n", observed, expected);
		printf("Deck Count: %d, Discard Count: %d, Hand Count: %d\n", state.deckCount[0], state.discardCount[0], state.handCount[0]);
		printf("\t\t+ TEST SUCCESSFUL +\n");
		(*goodTests)++;
	}
	else{
		//printf("\t\t-TEST FAILED- \n");
	}
	
}
