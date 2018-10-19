#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "functions.h"

int highestValue(int numCards, struct Card playerCards[numCards]);
int numPairs(int numCards, struct Card playerCards[numCards]);
int highestDuplicate(int numCards, struct Card playerCards[numCards]);
int hasTriplet(int numCards, struct Card playerCards[numCards]);
int hasStraight(int numCards, struct Card playerCards[numCards]);
int hasFlush(int numCards, struct Card playerCards[numCards]);
int hasFullHouse(int numCards, struct Card playerCards[numCards]);
int hasFourOfAKind(int numCards, struct Card playerCards[numCards]);

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
  struct Card playerHands[numPlayers][numCards], int winner) {
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

    if (playerNum == winner) {
      printf(" - Winner");
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
  int winner = 0;
  for(int i = 1; i < numPlayers; i++) {
    struct Card *compareToHand = playerHands[i];
    if ((hasStraight(numCards, playerHands[winner]) && hasFlush(numCards, playerHands[winner])) &&
            !(hasStraight(numCards, compareToHand) && hasFlush(numCards, compareToHand))) {
        continue;
    } else if (!(hasStraight(numCards, playerHands[winner]) && hasFlush(numCards, playerHands[winner])) &&
            (hasStraight(numCards, compareToHand) && hasFlush(numCards, compareToHand))) {
        winner = i;
    } else if (hasFourOfAKind(numCards, playerHands[winner]) && !hasFourOfAKind(numCards, compareToHand)) {
        continue;
    } else if (!hasFourOfAKind(numCards, playerHands[winner]) && hasFourOfAKind(numCards, compareToHand)) {
        winner = i;
    } else if (hasFullHouse(numCards, playerHands[winner]) && !hasFullHouse(numCards, compareToHand)) {
        continue;
    } else if (!hasFullHouse(numCards, playerHands[winner]) && hasFullHouse(numCards, compareToHand)) {
        winner = i;
    } else if (hasFlush(numCards, playerHands[winner]) && !hasFlush(numCards, compareToHand)) {
        continue;
    } else if (!hasFlush(numCards, playerHands[winner]) && hasFlush(numCards, compareToHand)) {
        winner = i;
    } else if (hasStraight(numCards, playerHands[winner]) && !hasStraight(numCards, compareToHand)) {
        continue;
    } else if (!hasStraight(numCards, playerHands[winner]) && hasStraight(numCards, compareToHand)) {
        winner = i;
    } else if (hasTriplet(numCards, playerHands[winner]) && !hasTriplet(numCards, compareToHand)) {
        continue;
    } else if (!hasTriplet(numCards, playerHands[winner]) && hasTriplet(numCards, compareToHand)) {
        winner = i;
    } else if (numPairs(numCards, playerHands[winner]) > numPairs(numCards, compareToHand)) {
        continue;
    } else if (numPairs(numCards, playerHands[winner]) < numPairs(numCards, compareToHand)) {
        winner = i;
    } else if (highestDuplicate(numCards, playerHands[winner]) > highestDuplicate(numCards, compareToHand)) {
        continue;
    } else if (highestDuplicate(numCards, playerHands[winner]) == highestDuplicate(numCards, compareToHand)) {
        printf("TIE ON HIGHEST DUPLICATE\n");
    } else if (highestDuplicate(numCards, playerHands[winner]) < highestDuplicate(numCards, compareToHand)) {
        winner = i;
    } else if (highestValue(numCards, compareToHand) > highestValue(numCards, compareToHand)) {
        continue;
    } else if (highestValue(numCards, compareToHand) < highestValue(numCards, compareToHand)) {
        winner = i;
    } else {
        printf("BOH!\n");
    }
  }

  /* Winner determined, check for ties */
  rankHands(numPlayers, numCards, playerHands, winner);

}

void generateTestHand(struct Card playerHand[5]) {
  for(int i = 0; i < 5; i++) {
    struct Card card = { .suit = DIAMOND_SYMBOL, .rank = (i + 2) + '0', .rankValue = i + 2 };
    playerHand[i] = card;
  }
}

void testRankings(struct Card playerHands[TEST_HANDS][TEST_CARDS]) {
  /* High Card */
  generateTestHand(playerHands[0]);
  playerHands[0][4].rank++;
  playerHands[0][4].rankValue++;
  playerHands[0][4].suit = SPADE_SYMBOL;

  /* One Pair */
  generateTestHand(playerHands[1]);
  playerHands[1][4].rank--;
  playerHands[1][4].rankValue--;
  playerHands[1][4].suit = SPADE_SYMBOL;

  /* Two Pairs */
  generateTestHand(playerHands[2]);
  playerHands[2][0].rank++;
  playerHands[2][0].rankValue++;
  playerHands[2][0].suit = SPADE_SYMBOL;

  playerHands[2][4].rank--;
  playerHands[2][4].rankValue--;
  playerHands[2][4].suit = SPADE_SYMBOL;

  /* Triplet */
  generateTestHand(playerHands[3]);
  playerHands[3][0].rank++;
  playerHands[3][0].rankValue++;
  playerHands[3][0].suit = SPADE_SYMBOL;

  playerHands[3][2].rank--;
  playerHands[3][2].rankValue--;
  playerHands[3][2].suit = HEART_SYMBOL;

  /* Straight */
  generateTestHand(playerHands[4]);
  playerHands[4][4].suit = SPADE_SYMBOL;

  /* Flush */
  generateTestHand(playerHands[5]);
  playerHands[5][4].rankValue++;
  playerHands[5][4].rank++;

  /* Full House */
  generateTestHand(playerHands[6]);
  playerHands[6][0].rank++;
  playerHands[6][0].rankValue++;
  playerHands[6][0].suit = SPADE_SYMBOL;

  playerHands[6][2].rank--;
  playerHands[6][2].rankValue--;
  playerHands[6][2].suit = HEART_SYMBOL;

  playerHands[6][4].rank--;
  playerHands[6][4].rankValue--;
  playerHands[6][4].suit = HEART_SYMBOL;

  /* Four of a Kind */
  generateTestHand(playerHands[7]);
  playerHands[7][0].rank++;
  playerHands[7][0].rankValue++;
  playerHands[7][0].suit = SPADE_SYMBOL;

  playerHands[7][2].rank--;
  playerHands[7][2].rankValue--;
  playerHands[7][2].suit = HEART_SYMBOL;

  playerHands[7][3].rank = playerHands[7][2].rank;
  playerHands[7][3].rankValue = playerHands[7][2].rankValue;
  playerHands[7][3].suit = CLUB_SYMBOL;

  /* Straight Flush */
  generateTestHand(playerHands[8]);
}
