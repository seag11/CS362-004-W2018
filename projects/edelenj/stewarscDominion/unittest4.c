
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void oracle(int arr[], int len);
void printDeck(struct gameState *state, int player);
void printDistribution(int arr[], int len);

int main(int argc, char **argv){
	printf("********************************************\n");
	printf("*           unittest4.c: shuffle           *\n");
	printf("********************************************\n");
	
	int seed = 1044;
	int numPlayer = 4;

	int k[10] = {smithy, adventurer, remodel, village, gardens,
                great_hall, tribute, outpost, ambassador, feast};
	
	struct gameState state;
	
	int y,z;
	for (y=0; y<numPlayer; y++){
		for (z=1; z<=20; z++){
			printf("Testing Player %d using %d cards in deck\n", y+1, z);
			memset(&state, '\0', sizeof(struct gameState));   // clear the game state
			initializeGame(numPlayer, k, seed, &state);  //initialize game
			
			state.deckCount[y] = 0;         
			
			//add z cards to deck
			int a = 0;
			int r;
			for(a=0; a<z; a++){
				r = rand() % treasure_map;
				//printf("Adding card %d to deck at position %d\n", r, a);
				state.deck[y][state.deckCount[y]] = r;
				state.deckCount[y]++;				
				//gainCard(r, &state, 1, y);  //this doesn't work intermittently
			}
			
			int distribution[MAX_DECK];
			memset(distribution, 0, sizeof(distribution));		//zero out array
			int i;
			for (i=0; i<state.deckCount[y]; i++){
				distribution[state.deck[y][i]]++;
			}
			int res = shuffle(y, &state);
			for (i=0; i<state.deckCount[y]; i++){
				distribution[state.deck[y][i]]--;
			}
			oracle(distribution, state.deckCount[y]);
		}
	}
	
	//Test frequency of distribution
	int frequency[10] = {0,0,0,0,0,0,0,0,0,0};
	int b,c, d;
	for (b=0;b<100000;b++){
		memset(&state, '\0', sizeof(struct gameState));   // clear the game state
		for(c=0; c<10; c++){
				state.deck[0][state.deckCount[0]] = c;
				state.deckCount[0]++;				
			}
		shuffle(0, &state);
		for (d=0; d<10; d++){
			if(state.deck[0][d] == 9){
				frequency[d]++;
			}		
		}
	}
	printf("Testing frequency of distribution for card 9 at 100,000 shuffles\n");
	printDistribution(frequency, 10);  //stdev = 61.70
		
	return 0;
}


void oracle(int arr[], int len){
	printf("Testing deck count of length %d  ", len);
	int i;
	int flag = 0;
	for (i=0;i<len;i++){
		if (arr[i] != 0){
			flag = 1;
			break;
		}
	}
	if(flag == 0){
		printf("+ TEST SUCCESSFUL +\n");
	}
	else{
		printf("-TEST FAILED-\n");
	}
	
}

void printDeck(struct gameState *state, int player){
	int i;
	for (i=0; i<state->deckCount[player]; i++){
		printf("%d ", state->deck[player][i]);
	}
	printf("\n");
}

void printDistribution(int arr[], int len){
	printf("Distribution: ");
	int i;
	for(i=0; i<len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}


