CFLAGS = -Wall -fpic -coverage -lm -g
	
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
runtests2: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer
	./unittest1 > unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	rm dominion.gcda
	./unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	rm dominion.gcda
	./unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	rm dominion.gcda
	./unittest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	rm dominion.gcda
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	rm dominion.gcda
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	rm dominion.gcda
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	rm dominion.gcda
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest1 >> /dev/null
	./unittest2 >> /dev/null
	./unittest3 >> /dev/null
	./unittest4 >> /dev/null
	./cardtest1 >> /dev/null
	./cardtest2 >> /dev/null
	./cardtest3 >> /dev/null
	./randomtestcard1 > randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out
	rm dominion.gcda
	./randomtestcard2 > randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out
	rm dominion.gcda
	./randomtestadventurer > randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	./randomtestcard1 >> /dev/null
	./randomtestcard2 >> /dev/null

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard1 randomtestcard2 randomtestadventurer unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 runtests2 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard randomtestcard1 randomtestcard2 randomtestadventurer unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
