struct Card {
  const char* suit;
  char rank;
};

struct Params {
  int numCards;
  int numPlayers;
};

struct Params * checkUsage(int argc, char *argv[]);
