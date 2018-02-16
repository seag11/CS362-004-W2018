#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

void oracle(int observed, int expected, int *goodTests, struct gameState state);
int treasureCounter(int arr[], int size);
double get_ms();

int main(int argc, char **argv)
{
	printf("********************************************\n");
	printf("*   randomtestadventurer.c: adventurer     *\n");
	printf("********************************************\n");
	int seed = 99;
	int goodTests = 0;
    int numPlayers = 4;
    int expected, observed;
    int handpos = 0, bonus = 0;
    int player = 0;
	struct gameState after, before;
	double begin, end;
	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
    
    srand(seed);
    
    begin = get_ms();
    int i;
    for (i=0; i<10000; i++){
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
		cardEffect(adventurer, 0, 0, 0, &after, handpos, &bonus);
		
		//Edge case detection for too few treasure cards in deck and discard
		int treasureCards;
		switch(treasureCounter(before.deck[player], before.deckCount[player]) + treasureCounter(before.discard[player],before.discardCount[player])){
			case 0 :
				treasureCards = 0;
				//printf("case 0\n");
				break;
			case 1 :
				treasureCards = 1;
				//printf("case 1\n");
				break;
			default :
				treasureCards = 2;
				break;	
		}
		
		observed = treasureCounter(after.hand[player],after.handCount[player]);
		expected = treasureCounter(before.hand[player], before.handCount[player])+treasureCards;
		oracle(observed, expected, &goodTests, before);
		
		//Supplemental gamestate tests
		if(memcmp(&after.supplyCount, &before.supplyCount, sizeof(before.supplyCount)) == 0){
				//test passed
		}
		else{
			printf("-Supply Count Test failed-\n");
		}
		if(memcmp(&after.playedCards, &before.playedCards, sizeof(before.playedCards)) == 0){
				//test passed
		}
		else{
			printf("-Played Cards Test failed-\n");
		}
			
	} 
	printf("Tested +2 treasure cards for player 1: %d passed out of %d\n", goodTests, i);
	end = get_ms();
	double runtime = end - begin;
	printf("* Random tester runtime elapsed %lf milliseconds *\n", runtime);
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

//Function counts the number of treasure cards in array
int treasureCounter(int arr[], int size){
	int treasureCount = 0;
	int i;
	for (i=0; i<size; i++){
		if (arr[i] == copper || arr[i] == silver || arr[i] == gold){
			treasureCount++;
		}
	}
	return treasureCount;
}

// Returns time in milliseconds
// Citation: http://timmurphy.org/2009/10/18/millisecond-timer-in-c-c/
double get_ms(){
	struct timeval t;		//variable represents elapsed time
	gettimeofday(&t, NULL); //get time and store timeval variable
	return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;  //(seconds + (microseconds / 1000000)) * 1000
}
