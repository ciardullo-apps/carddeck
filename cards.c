#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* needed for random seed */
#include "defs.h"
#include "functions.h"

struct Card * initializeDeck() {
  static struct Card cards[NUM_CARDS_IN_DECK];
  int count = 0;
  enum ranks { ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
  for(int rankNum = ACE; rankNum <= KING; rankNum++ ) {
    char rank;
    switch (rankNum) {
      case ACE:
        rank = ACE_SYMBOL;
        break;
      case TEN:
        rank = TEN_SYMBOL;
        break;
      case JACK:
        rank = JACK_SYMBOL;
        break;
      case QUEEN:
        rank = QUEEN_SYMBOL;
        break;
      case KING:
        rank = KING_SYMBOL;
        break;
      default:
        rank = rankNum + 48;
    }

    enum suits { HEARTS, DIAMONDS, CLUBS, SPADES };

    for(int suitNum = HEARTS; suitNum <= SPADES; suitNum++) {
      struct Card card;
      card.rank = rank;

      // Escape sequences for suits
      switch (suitNum) {
        case HEARTS:
          card.suit = HEART_SYMBOL;
          break;
        case DIAMONDS:
          card.suit = DIAMOND_SYMBOL;
          break;
        case CLUBS:
          card.suit = CLUB_SYMBOL;
          break;
        case SPADES:
          card.suit = SPADE_SYMBOL;
          break;
      }

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
  struct Card * playerHands[numPlayers][numCards]) {

  /* Initialize a hand for each player */
  for(int playerNum = 0; playerNum < numPlayers; playerNum++) {
    struct Card * nextCard = deck + playerNum;
    for(int cardNum = 0; cardNum < numCards; cardNum++) {
      playerHands[playerNum][cardNum] = nextCard;
      nextCard += numPlayers;
    }
  }
}

void printPlayerHands(int numPlayers, int numCards, struct Card* playerHands[numPlayers][numCards]) {
  for(int playerNum = 0; playerNum < numPlayers; playerNum++) {
    printf("Player %d] -\t", playerNum + 1);
    for(int cardNum = 0; cardNum < numCards; cardNum++) {
      struct Card * card = playerHands[playerNum][cardNum];
      printf("[%c-%s]\t", card->rank, card->suit);
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

  struct Card* playerHands[params->numPlayers][params->numCards];
  dealCards(params->numPlayers, params->numCards, cards, playerHands);
  printf("\nPlayer Hands: (dealt from top/front of deck)\n");
  printPlayerHands(params->numPlayers, params->numCards, playerHands);
}
