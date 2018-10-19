struct Card {
  const char* suit;
  char rank;
  int rankValue;
};

struct Params {
  int numCards;
  int numPlayers;
};

struct Params * checkUsage(int argc, char *argv[]);

void sortHands(int numPlayers, int numCards,
  struct Card playerHands[numPlayers][numCards]);

void rankHands(int numPlayers, int numCards,
  struct Card playerHands[numPlayers][numCards], int winner);

void determineWinner(int numPlayers, int numCards,
  struct Card playerHands[numPlayers][numCards]);

void testRankings(struct Card playerHands[TEST_HANDS][TEST_CARDS]);
