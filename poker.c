#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
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
void getAllWinningHands(int winner, int numPlayers, int numCards,
  int winners[numPlayers], enum handRanks winningRank,
  struct Card playerHands[numPlayers][numCards]);

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

void determineWinner(int numPlayers, int numCards, struct Card playerHands[numPlayers][numCards]) {
  enum handRanks winningRank;

  int winner = 0;
  for(int i = 1; i < numPlayers; i++) {
    struct Card *compareToHand = playerHands[i];
    if ((hasStraight(numCards, playerHands[winner]) && hasFlush(numCards, playerHands[winner])) &&
            !(hasStraight(numCards, compareToHand) && hasFlush(numCards, compareToHand))) {
        winningRank = STRAIGHT_FLUSH;
        continue;
    } else if (!(hasStraight(numCards, playerHands[winner]) && hasFlush(numCards, playerHands[winner])) &&
            (hasStraight(numCards, compareToHand) && hasFlush(numCards, compareToHand))) {
        winningRank = STRAIGHT_FLUSH;
        winner = i;
    } else if (hasFourOfAKind(numCards, playerHands[winner]) && !hasFourOfAKind(numCards, compareToHand)) {
        winningRank = FOUR_OF_A_KIND;
        continue;
    } else if (!hasFourOfAKind(numCards, playerHands[winner]) && hasFourOfAKind(numCards, compareToHand)) {
        winningRank = FOUR_OF_A_KIND;
        winner = i;
    } else if (hasFullHouse(numCards, playerHands[winner]) && !hasFullHouse(numCards, compareToHand)) {
        winningRank = FULL_HOUSE;
        continue;
    } else if (!hasFullHouse(numCards, playerHands[winner]) && hasFullHouse(numCards, compareToHand)) {
        winningRank = FULL_HOUSE;
        winner = i;
    } else if (hasFlush(numCards, playerHands[winner]) && !hasFlush(numCards, compareToHand)) {
        winningRank = FLUSH;
        continue;
    } else if (!hasFlush(numCards, playerHands[winner]) && hasFlush(numCards, compareToHand)) {
        winningRank = FLUSH;
        winner = i;
    } else if (hasStraight(numCards, playerHands[winner]) && !hasStraight(numCards, compareToHand)) {
        winningRank = STRAIGHT;
        continue;
    } else if (!hasStraight(numCards, playerHands[winner]) && hasStraight(numCards, compareToHand)) {
        winningRank = STRAIGHT;
        winner = i;
    } else if (hasTriplet(numCards, playerHands[winner]) && !hasTriplet(numCards, compareToHand)) {
        winningRank = TRIPLET;
        continue;
    } else if (!hasTriplet(numCards, playerHands[winner]) && hasTriplet(numCards, compareToHand)) {
        winningRank = TRIPLET;
        winner = i;
    } else if (hasTwoPairs(numCards, playerHands[winner]) && !hasTwoPairs(numCards, compareToHand)) {
        winningRank = TWO_PAIR;
        continue;
    } else if (!hasTwoPairs(numCards, playerHands[winner]) && hasTwoPairs(numCards, compareToHand)) {
        winningRank = TWO_PAIR;
        winner = i;
    } else if (hasOnePair(numCards, playerHands[winner]) && !hasOnePair(numCards, compareToHand)) {
        winningRank = ONE_PAIR;
        continue;
    } else if (!hasOnePair(numCards, playerHands[winner]) && hasOnePair(numCards, compareToHand)) {
        winningRank = ONE_PAIR;
        winner = i;
    } else if (highestDuplicate(numCards, playerHands[winner]) > highestDuplicate(numCards, compareToHand)) {
        winningRank = ONE_PAIR;
        continue;
    } else if (highestDuplicate(numCards, playerHands[winner]) != 0 && highestDuplicate(numCards, playerHands[winner]) == highestDuplicate(numCards, compareToHand)) {
        winningRank = ONE_PAIR;
        printf("TIE ON HIGHEST DUPLICATE\n");
    } else if (highestDuplicate(numCards, playerHands[winner]) < highestDuplicate(numCards, compareToHand)) {
        winner = i;
    } else if (highestValue(numCards, playerHands[winner]) > highestValue(numCards, compareToHand)) {
        winningRank = HIGH_CARD;
        continue;
    } else if (highestValue(numCards, playerHands[winner]) < highestValue(numCards, compareToHand)) {
      winningRank = HIGH_CARD;
      winner = i;
    } else {
        winningRank = HIGH_CARD;
        printf("TIE ON HIGHEST VALUE!\n");
    }
  }

  /* Check for ties */
  int winners[numPlayers];
  getAllWinningHands(winner, numPlayers, numCards, winners, winningRank, playerHands);

  /* Winner determined, check for ties */
  rankHands(numPlayers, numCards, playerHands, winners);
}

void getAllWinningHands(int winner, int numPlayers, int numCards,
  int winners[numPlayers], enum handRanks winningRank,
  struct Card playerHands[numPlayers][numCards]) {
  int winnerCount = 0;
  winners[winnerCount++] = winner;

  if(winningRank == STRAIGHT_FLUSH) {
    for(int compareToHand = 0; compareToHand < numPlayers; compareToHand++) {
      if (winner == compareToHand) {
        continue;
      }
      if (hasStraight(numCards, playerHands[compareToHand]) && hasFlush(numCards, playerHands[compareToHand])) {
        winners[winnerCount++] = compareToHand;
      }
    }
  } else if(winningRank == FOUR_OF_A_KIND) {
    for(int compareToHand = 0; compareToHand < numPlayers; compareToHand++) {
      if (winner == compareToHand) {
        continue;
      }
      if (hasFourOfAKind(numCards, playerHands[compareToHand])) {
        winners[winnerCount++] = compareToHand;
      }
    }
  } else if(winningRank == FULL_HOUSE) {
    for(int compareToHand = 0; compareToHand < numPlayers; compareToHand++) {
      if (winner == compareToHand) {
        continue;
      }
      if (hasFullHouse(numCards, playerHands[compareToHand])) {
        winners[winnerCount++] = compareToHand;
      }
    }
  } else if(winningRank == FLUSH) {
    for(int compareToHand = 0; compareToHand < numPlayers; compareToHand++) {
      if (winner == compareToHand) {
        continue;
      }
      if (hasFlush(numCards, playerHands[compareToHand])) {
        winners[winnerCount++] = compareToHand;
      }
    }
  } else if(winningRank == STRAIGHT) {
    for(int compareToHand = 0; compareToHand < numPlayers; compareToHand++) {
      if (winner == compareToHand) {
        continue;
      }
      if (hasStraight(numCards, playerHands[compareToHand])) {
        winners[winnerCount++] = compareToHand;
      }
    }
  } else if(winningRank == TRIPLET) {
    for(int compareToHand = 0; compareToHand < numPlayers; compareToHand++) {
      if (winner == compareToHand) {
        continue;
      }
      if (hasTriplet(numCards, playerHands[compareToHand])) {
        winners[winnerCount++] = compareToHand;
      }
    }
  } else if(winningRank == TWO_PAIR) {
    for(int compareToHand = 0; compareToHand < numPlayers; compareToHand++) {
      if (winner == compareToHand) {
        continue;
      }
      if (hasTwoPairs(numCards, playerHands[compareToHand])) {
        winners[winnerCount++] = compareToHand;
      }
    }
  } else if(winningRank == ONE_PAIR) {
    for(int compareToHand = 0; compareToHand < numPlayers; compareToHand++) {
      if (winner == compareToHand) {
        continue;
      }
      if (hasOnePair(numCards, playerHands[compareToHand])) {
        winners[winnerCount++] = compareToHand;
      }
    }
  }

  // Replace the remaining winners with -1
  for(int i = winnerCount; i < numPlayers; i++) {
    winners[i] = -1;
  }

}
