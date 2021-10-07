# CS220 HW7
# Shaopeng Zeng szeng10
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

all: tTrieTest wordHunt cTrieTest

tTrieTest: TTrieTest.o
	g++ -o tTrieTest TTrieTest.o

TTrieTest.o: TTrieTest.cpp TTrie.h TTrie.inc
	g++ -c TTrieTest.cpp $(CFLAGS)

wordHunt: wordHuntMain.o CTrie.o WordHunt.o
	g++ -o wordHunt wordHuntMain.o CTrie.o WordHunt.o

wordHuntMain.o: wordHuntMain.cpp WordHunt.h
	g++ -c wordHuntMain.cpp $(CFLAGS)

WordHunt.o: WordHunt.cpp WordHunt.h
	g++ -c WordHunt.cpp $(CFLAGS)

cTrieTest: CTrieTest.o CTrie.o
	g++ -o cTrieTest CTrieTest.o CTrie.o

CTrieTest.o: CTrieTest.cpp CTrie.h
	g++ -c CTrieTest.cpp $(CFLAGS)

CTrie.o: CTrie.cpp CTrie.h
	g++ -c CTrie.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o *~ *.gch tTrieTest wordHunt cTrieTest
