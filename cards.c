#include "functions.h"

struct Card * initializeDeck() {
  static struct Card cards[NUM_CARDS_IN_DECK];
  int count = 0;

  enum ranks { ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
  char rankSymbols[] = { ACE_SYMBOL, '2', '3', '4', '5', '6', '7', '8', '9', TEN_SYMBOL, JACK_SYMBOL, QUEEN_SYMBOL, KING_SYMBOL };
  int rankValues[] = { 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

  enum suits { HEARTS, DIAMONDS, CLUBS, SPADES };
  char* suitSymbols[] = { HEART_SYMBOL, DIAMOND_SYMBOL, CLUB_SYMBOL, SPADE_SYMBOL };

  for(int rankNum = ACE; rankNum <= KING; rankNum++ ) {
    for(int suitNum = HEARTS; suitNum <= SPADES; suitNum++) {
      struct Card card;
      card.rank = rankSymbols[rankNum - 1];
      card.rankValue = rankValues[rankNum - 1];
      card.suit = suitSymbols[suitNum];

      cards[count++] = card;
    }
  }

  return cards;
}

void shuffleDeck(struct Card * cards) {
  /* To shuffle an array a of n elements (indices 0..n-1): */
  srand(time(NULL));
  for (int i = 51; i >= 1; i--) {
     int j  = rand() % i; /* random integer such that 0 ≤ j ≤ i */
     /* exchange a[j] and a[i] */
     struct Card temp = cards[i];
     cards[i] = cards[j];
     cards[j] = temp;
   }
}

void printDeck(struct Card * cards) {
  for(int m = 0; m < 52; m++ ) {
    struct Card card = cards[m];
    if (m != 0 && m % 13 == 0) {
      printf("\n");
    }
    printf("[%c-%s]\t", card.rank, card.suit);
  }
  printf("\n");
}

/*
 * Uses variable length array for the hands containing the dealt cardes
 */
void dealCards(int numPlayers, int numCards, struct Card * deck,
  struct Card playerHands[numPlayers][numCards]) {

  /* Initialize a hand for each player */
  for(int playerNum = 0; playerNum < numPlayers; playerNum++) {
    struct Card * nextCard = deck + playerNum;
    for(int cardNum = 0; cardNum < numCards; cardNum++) {
      playerHands[playerNum][cardNum] = *nextCard;
      nextCard += numPlayers;
    }
  }
}

void printPlayerHands(int numPlayers, int numCards, struct Card playerHands[numPlayers][numCards]) {
  for(int playerNum = 0; playerNum < numPlayers; playerNum++) {
    printf("Player %d] -\t", playerNum + 1);
    for(int cardNum = 0; cardNum < numCards; cardNum++) {
      struct Card card = playerHands[playerNum][cardNum];
      printf("[%c-%s]\t", card.rank, card.suit);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  struct Params *params = checkUsage(argc, argv);
  if(params == NULL) {
    return -1;
  }

  struct Card * cards = initializeDeck();

  printf("Original Ordered Deck:\n");
  printDeck(cards);

  shuffleDeck(cards);
  printf("\nRandom Shuffled Deck:\n");
  printDeck(cards);

  struct Card playerHands[params->numPlayers][params->numCards];
  dealCards(params->numPlayers, params->numCards, cards, playerHands);
  printf("\nPlayer Hands: (dealt from top/front of deck)\n");
  printPlayerHands(params->numPlayers, params->numCards, playerHands);

  printf("\nPlayer Hands: sorted\n");
  sortHands(params->numPlayers, params->numCards, playerHands);
  printPlayerHands(params->numPlayers, params->numCards, playerHands);

  printf("\nPlayer Hands: ranked\n");
  rankHands(params->numPlayers, params->numCards, playerHands);

  printf("\nPlayer Hands: winner(s)\n");
  enum handRanks winningHandRank =
      determineWinningHand(params->numPlayers, params->numCards, playerHands);
  getAllWinningHands(params->numPlayers, params->numCards, winningHandRank, playerHands);

  printf("\nPoker Hands: test\n");
  rankHands(TEST_HANDS, TEST_CARDS, testHands);
}
