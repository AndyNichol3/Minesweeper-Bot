// bug fix list

// g++ main.cpp PLAY_GAME.cpp BOT_FUNCTIONS.cpp BOT_MOVES.cpp
//g++ -include stdafx.h main.cpp PLAY_GAME.cpp BOT_FUNCTIONS.cpp BOT_MOVES.cpp

#include "stdafx.h"

int main() {
  // define variable
  int round = 1;

  // <maxRows, maxColums, MaXNumOfMines>
  tuple<int, int, int> gameStartTuple = gameStart();

  int maxNumberOfRows = get<0>(gameStartTuple);
  int maxNumberOfColumns = get<1>(gameStartTuple);
  int maxNumOfMines = get<2>(gameStartTuple);

  vector<vector<int>> gameBoard(maxNumberOfRows,
                                vector<int>(maxNumberOfColumns, 0));

  vector<vector<bool>> boolGameBoard(maxNumberOfRows,
                                     vector<bool>(maxNumberOfColumns, false));
  set<pair<int, int>> knownMines;

  initalizeBotGameBoard(boolGameBoard, gameBoard, maxNumberOfRows,
                        maxNumberOfColumns, maxNumOfMines, round, knownMines);

  bool botHasHaulted =
      playFullBot(maxNumberOfRows, maxNumberOfColumns, maxNumOfMines, round,
                  knownMines, boolGameBoard, gameBoard);

  // this should not trigger any more due to bot nature
  // only here so the program doesnt unexpectedly start
  if (botHasHaulted == false) {
    bool win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                        gameBoard, maxNumOfMines, round, knownMines);
    endOfGameHeader(win);
  }
}

