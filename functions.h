struct Card {
  const char* suit;
  char rank;
  int rankValue;
};

struct Params {
  int numCards;
  int numPlayers;
};

static struct Card testHands[TEST_HANDS][TEST_CARDS] = {
  { {DIAMOND_SYMBOL, '2', 2}, {DIAMOND_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '4', 4}, {DIAMOND_SYMBOL, '5', 5}, {SPADE_SYMBOL, '7', 7} },
  { {DIAMOND_SYMBOL, '2', 2}, {DIAMOND_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '4', 4}, {DIAMOND_SYMBOL, '5', 5}, {SPADE_SYMBOL, '5', 5} },
  { {SPADE_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '4', 4}, {DIAMOND_SYMBOL, '7', 7}, {SPADE_SYMBOL, '7', 7} },
  { {DIAMOND_SYMBOL, '3', 3}, {SPADE_SYMBOL, '3', 3}, {CLUB_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '5', 5}, {SPADE_SYMBOL, '7', 7} },
  { {DIAMOND_SYMBOL, '2', 2}, {DIAMOND_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '4', 4}, {DIAMOND_SYMBOL, '5', 5}, {SPADE_SYMBOL, '6', 6} },
  { {DIAMOND_SYMBOL, '2', 2}, {DIAMOND_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '4', 4}, {DIAMOND_SYMBOL, '5', 5}, {DIAMOND_SYMBOL, '7', 7} },
  { {DIAMOND_SYMBOL, '3', 3}, {SPADE_SYMBOL, '3', 3}, {CLUB_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '5', 5}, {SPADE_SYMBOL, '5', 5} },
  { {DIAMOND_SYMBOL, '3', 3}, {SPADE_SYMBOL, '3', 3}, {CLUB_SYMBOL, '3', 3}, {HEART_SYMBOL, '3', 3}, {SPADE_SYMBOL, '7', 7} },
  { {DIAMOND_SYMBOL, '2', 2}, {DIAMOND_SYMBOL, '3', 3}, {DIAMOND_SYMBOL, '4', 4}, {DIAMOND_SYMBOL, '5', 5}, {DIAMOND_SYMBOL, '6', 6} },
};

struct Params * checkUsage(int argc, char *argv[]);

void sortHands(int numPlayers, int numCards,
  struct Card playerHands[numPlayers][numCards]);

void rankHands(int numPlayers, int numCards,
  struct Card playerHands[numPlayers][numCards], int* winner);

void determineWinningHand(int numPlayers, int numCards,
  struct Card playerHands[numPlayers][numCards]);

void testRankings(struct Card playerHands[TEST_HANDS][TEST_CARDS]);
