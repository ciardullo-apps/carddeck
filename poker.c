#include "functions.h"

int highestValue(int numCards, struct Card playerCards[numCards]);
int numPairs(int numCards, struct Card playerCards[numCards]);
int hasOnePair(int numCards, struct Card playerCards[numCards]);
int hasTwoPairs(int numCards, struct Card playerCards[numCards]);
int highestDuplicate(int numCards, struct Card playerCards[numCards]);
int hasTriplet(int numCards, struct Card playerCards[numCards]);
int hasStraight(int numCards, struct Card playerCards[numCards]);
int hasFlush(int numCards, struct Card playerCards[numCards]);
int hasFullHouse(int numCards, struct Card playerCards[numCards]);
int hasFourOfAKind(int numCards, struct Card playerCards[numCards]);
void getAllWinningHands(int numPlayers, int numCards, int winners[numPlayers],
  enum handRanks winningRank, struct Card playerHands[numPlayers][numCards]);

/* Sort each player hand by rank using Bubble sort */
void sortHands(int numPlayers, int numCards, struct Card playerHands[numPlayers][numCards]) {
  for(int playerNum = 0; playerNum < numPlayers; playerNum++) {
    int swap = 0;
    do {
      swap = 0;
      for(int cardNum = 1; cardNum < numCards; cardNum++) {
        struct Card cardA = playerHands[playerNum][cardNum - 1];
        struct Card cardB = playerHands[playerNum][cardNum];
        if(cardA.rankValue > cardB.rankValue) {
          struct Card tmp = cardA;
          playerHands[playerNum][cardNum - 1] = cardB;
          playerHands[playerNum][cardNum] = tmp;
          swap = 1;
        }
      }
    } while(swap);
  }
}

void rankHands(int numPlayers, int numCards,
  struct Card playerHands[numPlayers][numCards], int *winners) {
  for(int playerNum = 0; playerNum < numPlayers; playerNum++) {
    printf("Player %d] -\t", playerNum + 1);
    for(int cardNum = 0; cardNum < numCards; cardNum++) {
      struct Card card = playerHands[playerNum][cardNum];
      printf("[%c-%s]\t", card.rank, card.suit);
    }
    if (0) {
      ;
    } else if (hasStraight(numCards, playerHands[playerNum]) && hasFlush(numCards, playerHands[playerNum])) {
      printf("- Straight Flush");
    } else if (hasFourOfAKind(numCards, playerHands[playerNum])) {
      printf("- Four Of A Kind");
    } else if (hasFullHouse(numCards, playerHands[playerNum])) {
      printf("- Full House");
    } else if (hasFlush(numCards, playerHands[playerNum])) {
      printf("- Flush");
    } else if (hasStraight(numCards, playerHands[playerNum])) {
      printf("- Straight");
    } else if (hasTriplet(numCards, playerHands[playerNum])) {
      printf("- Triplet");
    } else if (numPairs(numCards, playerHands[playerNum]) == 2) {
      printf("- Two Pairs");
    } else if (numPairs(numCards, playerHands[playerNum]) == 1) {
      printf("- One Pair");
    } else {
      printf("- High Card");
    }

    if (winners != NULL) {
      for(int i = 0; i < numPlayers; i++) {
        if (playerNum == winners[i]) {
          printf(" - Winner");
        }
      }
    }

    printf("\n");
  }
}

int highestValue(int numCards, struct Card playerCards[numCards]) {
  int highestRankValue = 0;
  for (int i = 0; i < numCards; i++) {
      if (highestRankValue < playerCards[i].rankValue) {
          highestRankValue = playerCards[i].rankValue;
      }
  }

  return highestRankValue;
}

int hasOnePair(int numCards, struct Card playerCards[numCards]) {
  return numPairs(numCards, playerCards) == 1;
}

int hasTwoPairs(int numCards, struct Card playerCards[numCards]) {
  return numPairs(numCards, playerCards) == 2;
}

int numPairs(int numCards, struct Card playerCards[numCards]) {
  int numPairs = 0;
  for(int cardNum = 0; cardNum < numCards - 1; cardNum++) {
    if(playerCards[cardNum].rankValue == playerCards[cardNum + 1].rankValue) {
      numPairs++;
      cardNum++;
    }
  }
  return numPairs;
}

int highestDuplicate(int numCards, struct Card playerCards[numCards]) {
  int highDupe = 0;
  for(int i = 0; i < numCards; i++) {
    struct Card firstCard = playerCards[i];
    for(int j = i + 1; j < numCards; j++) {
      struct Card secondCard = playerCards[j];
      if(firstCard.rank == secondCard.rank) {
        highDupe = firstCard.rankValue;
      }
    }
  }
  return highDupe;
}

int hasTriplet(int numCards, struct Card playerCards[numCards]) {
  for (int i = 0; i < numCards - 2; i++) {
      struct Card firstCard = playerCards[i];
      int numMatches = 0;
      for (int j = i+1; j < numCards; j++) {
          struct Card secondCard = playerCards[j];
          if (firstCard.rankValue == secondCard.rankValue) {
              numMatches++;
          }
      }
      if(numMatches == 2) {
          return TRUE;
      }
  }

  return FALSE;
}

int hasStraight(int numCards, struct Card playerCards[numCards]) {
  for(int cardNum = 0; cardNum < numCards - 1; cardNum++) {
    if((playerCards[cardNum].rankValue + 1) != playerCards[cardNum + 1].rankValue) {
      return FALSE;
    }
  }
  return TRUE;
}

int hasFlush(int numCards, struct Card playerCards[numCards]) {
  for(int cardNum = 0; cardNum < numCards - 1; cardNum++) {
    if(playerCards[cardNum].suit != playerCards[cardNum + 1].suit) {
      return FALSE;
    }
  }
  return TRUE;
}

int hasFullHouse(int numCards, struct Card playerCards[numCards]) {
  int result = numPairs(numCards, playerCards) == 2 &&
    hasTriplet(numCards, playerCards) &&
    !hasFourOfAKind(numCards, playerCards);
}

int hasFourOfAKind(int numCards, struct Card playerCards[numCards]) {
  for (int i = 0; i < numCards - 3; i++) {
            struct Card first = playerCards[i];
            int numMatches = 0;
            for (int j = i + 1; j < numCards; j++) {
                struct Card second = playerCards[j];
                if (first.rankValue == second.rankValue) {
                    numMatches++;
                }
            }
            if (numMatches == 3) {
                return TRUE;
            }
        }

        return FALSE;
}

void determineWinningHand(int numPlayers, int numCards, struct Card playerHands[numPlayers][numCards]) {
  enum handRanks winningRank = HIGH_CARD;

  for(int i = 0; i < numPlayers; i++) {
    struct Card *hand = playerHands[i];
    if (winningRank < STRAIGHT_FLUSH && hasStraight(numCards, hand) && hasFlush(numCards, hand)) {
        winningRank = STRAIGHT_FLUSH;
    } else if(winningRank < FOUR_OF_A_KIND && hasFourOfAKind(numCards, hand)) {
        winningRank = FOUR_OF_A_KIND;
    } else if(winningRank < FULL_HOUSE && hasFullHouse(numCards, hand)) {
          winningRank = FULL_HOUSE;
    } else if(winningRank < FLUSH && hasFlush(numCards, hand)) {
          winningRank = FLUSH;
    } else if(winningRank < STRAIGHT && hasStraight(numCards, hand)) {
          winningRank = STRAIGHT;
    } else if(winningRank < TRIPLET && hasTriplet(numCards, hand)) {
          winningRank = TRIPLET;
    } else if(winningRank < TWO_PAIR && hasTwoPairs(numCards, hand)) {
          winningRank = TWO_PAIR;
    } else if(winningRank < ONE_PAIR && hasOnePair(numCards, hand)) {
          winningRank = ONE_PAIR;
    }
  }

  /* Check for ties */
  int winners[numPlayers];
  getAllWinningHands(numPlayers, numCards, winners, winningRank, playerHands);

  /* Winner determined, display all hands indicating all winning hands */
  rankHands(numPlayers, numCards, playerHands, winners);
}

void getAllWinningHands(int numPlayers, int numCards, int winners[numPlayers],
  enum handRanks winningRank, struct Card playerHands[numPlayers][numCards]) {
  int winnerCount = 0;
  for(int hand = 0; hand < numPlayers; hand++) {
    if(winningRank == STRAIGHT_FLUSH) {
      if (hasStraight(numCards, playerHands[hand]) && hasFlush(numCards, playerHands[hand])) {
        winners[winnerCount++] = hand;
      }
    } else if(winningRank == FOUR_OF_A_KIND) {
      if (hasFourOfAKind(numCards, playerHands[hand])) {
        winners[winnerCount++] = hand;
      }
    } else if(winningRank == FULL_HOUSE) {
      if (hasFullHouse(numCards, playerHands[hand])) {
        winners[winnerCount++] = hand;
      }
    } else if(winningRank == FLUSH) {
      if (hasFlush(numCards, playerHands[hand])) {
        winners[winnerCount++] = hand;
      }
    } else if(winningRank == STRAIGHT) {
      if (hasStraight(numCards, playerHands[hand])) {
        winners[winnerCount++] = hand;
      }
    } else if(winningRank == TRIPLET) {
      if (hasTriplet(numCards, playerHands[hand])) {
        winners[winnerCount++] = hand;
      }
    } else if(winningRank == TWO_PAIR) {
      if (hasTwoPairs(numCards, playerHands[hand])) {
        winners[winnerCount++] = hand;
      }
    } else if(winningRank == ONE_PAIR) {
      if (hasOnePair(numCards, playerHands[hand])) {
        winners[winnerCount++] = hand;
      }
    } else {
      winners[winnerCount++] = hand;
    }
  }

  // Replace the remaining winners with -1
  for(; winnerCount < numPlayers; winnerCount++) {
    winners[winnerCount] = -1;
  }

}
