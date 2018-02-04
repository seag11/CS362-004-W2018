
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	printf("********************************************\n");
	printf("*           unittest1.c: getCost          *\n");
	printf("********************************************\n");
	
	int cost;
	//test independently researched card values
	int cardCost[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
	
	int i;
	for (i=0; i<27; i++){
		cost = getCost(i);
		if (cost == cardCost[i]){
			printf("TEST SUCCESSFUL- CARD NO: %d \n", i); 
		}
		else{
			printf("TEST FAILED - CARD NO: %d \n", i);
		}
	}
	
	//test edge case for max integer
	cost = getCost(2147483647);
	if (cost == -1){
	printf("TEST SUCCESSFUL- MAX INT\n"); 
	}
	else{
		printf("TEST FAILED - MAX INT\n");
	}
	
	//test edge case for min integer
	cost = getCost(-2147483648);
	if (cost == -1){
	printf("TEST SUCCESSFUL- MIN INT\n"); 
	}
	else{
		printf("TEST FAILED - MIN INT\n");
	}
	
	//test edge case for nonexistant card
	cost = getCost(28);
	if (cost == -1){
	printf("TEST SUCCESSFUL- CARD NO: 28\n"); 
	}
	else{
		printf("TEST FAILED - CARD NO: 28\n");
	}
	
	return 0;
}

