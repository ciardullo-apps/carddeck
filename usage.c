#include "functions.h"

const int MIN_CARDS = 5;
const int MAX_CARDS = 5;
const int MIN_PLAYERS = 1;
const int MAX_PLAYERS = 10;

void printUsage(char* programName) {
  printf("Usage %s %s %s\n", programName, "<number of cards>", "<number of players>");
}

int getNumCards(char *_numCards) {
  int numCards = atoi(_numCards);
  if(numCards < MIN_CARDS || numCards > MAX_CARDS) {
    printf("Number of cards value must be between %d and %d\n", MIN_CARDS, MAX_CARDS);
    return -1;
  }
  return numCards;
}

int getNumPlayers(char *_numPlayers) {
  int numPlayers = atoi(_numPlayers);
  if(numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS) {
    printf("Number of players must be between %d and %d\n", MIN_PLAYERS, MAX_PLAYERS);
    return -1;
  }
  return numPlayers;
}

int getNumCardsRequired(int numCards, int numPlayers) {
  int numCardsRequired = numCards * numPlayers;
  if(numCardsRequired < 0 || numCardsRequired > NUM_CARDS_IN_DECK) {
    printf("There are only %d cards in the deck, that would require %d cards!\n", 52, numCardsRequired);
    return -1;
  }
  return numCardsRequired;
}

struct Params * checkUsage(int argc, char *argv[]) {
  if(argc != 3) {
    printUsage(argv[0]);
    return NULL;
  }

  int numCards = getNumCards(argv[1]);
  if(numCards <= 0) {
    printUsage(argv[0]);
    return NULL;
  }

  int numPlayers = getNumPlayers(argv[2]);
  if(numPlayers <= 0) {
    printUsage(argv[0]);
    return NULL;
  }

  int numCardsRequired = getNumCardsRequired(numCards, numPlayers);
  if(numCardsRequired <= 0) {
    printUsage(argv[0]);
    return NULL;
  }

  static struct Params params;
  params.numCards= numCards;
  params.numPlayers = numPlayers;

  return &params;
}
