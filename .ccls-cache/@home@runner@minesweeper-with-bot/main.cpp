// minesweeper

// g++ main.cpp PLAY_GAME.cpp BOT_FUNCTIONS.cpp
#include "BOT_FUNCTIONS.h"
#include "PLAY_GAME.h"
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
  // define variable
  int maxNumberOfRows = 0, maxNumberOfColumns = 0, maxNumOfMines = 0,
      displaySubtract = 0;
  int round = 1;

  // print the game header,
  // also includes rule menu which keeps user until decides to start
  printGameWelcome();

  // get the user difficulty
  // 1 easy 2 meduim 3 hard
  int difficulty = getUserDifficulty();

  // define some constasnts based on the difficulty
  switch (difficulty) {
  case 1: {
    maxNumberOfRows = 9;
    maxNumberOfColumns = 9;
    maxNumOfMines = 10;
    break;
  }
  case 2: {
    maxNumberOfRows = 16;
    maxNumberOfColumns = 16;
    maxNumOfMines = 40;
    break;
  }
  case 3: {
    maxNumberOfRows = 16;
    maxNumberOfColumns = 30;
    maxNumOfMines = 99;
    break;
  }
  }

  // create the definition for some display variables
  displaySubtract = maxNumberOfRows - 1;

  // creates the game baords
  // one to hold the ints and one to hold the bools
  vector<vector<int>> gameBoard(maxNumberOfRows,
                                vector<int>(maxNumberOfColumns, 0));
  vector<vector<bool>> boolGameBoard(maxNumberOfRows,
                                     vector<bool>(maxNumberOfColumns, false));
  vector<vector<bool>> boolFlagLocation(
      maxNumberOfRows, vector<bool>(maxNumberOfColumns, false));

  // initalizeGameBoard
  initalizeBotGameBoard(boolGameBoard, gameBoard, maxNumberOfRows,
                        maxNumberOfColumns, maxNumOfMines);

  // OG
  // bool win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
  //         gameBoard, maxNumOfMines);

  //{

  bool gameOver = false, win = false;
  // int round = 1;
  int revealTally = 0;
  int maxDisplay = maxNumberOfRows * maxNumberOfColumns;
  int userRow = -2, userCol = -2;

  cout << "Bots flagged Point: " << endl;
  set<pair<int, int>> knownMines;
  for (int i = 0; i <= 15; i++) {
    knownMines = botCheckForMines(knownMines, maxNumberOfRows,
                                  maxNumberOfColumns, round, maxNumOfMines,
                                  boolGameBoard, gameBoard, boolFlagLocation);
    // calculateInitialKnownMines(maxNumberOfColumns, maxNumberOfRows,
    //                          boolGameBoard, gameBoard, boolFlagLocation);
    int confirmedMineTally = 0;
    for (const auto &mineLocation : knownMines) {
      confirmedMineTally++;
      std::cout << "Mine at coordinates (" << mineLocation.second << ", "
                << maxNumberOfRows - 1 - mineLocation.first << ")\n";
    }
    if (confirmedMineTally == maxNumOfMines) {
      cout << endl << "Trigger The Special Case" << endl;
      win = foundAllMines(knownMines, maxNumberOfRows, maxNumberOfColumns,
                          round, maxNumOfMines, boolGameBoard, gameBoard,
                          boolFlagLocation);
      break;
    }

    cout << endl << "TEST SET 1" << endl;

    playBotMoves(knownMines, maxNumberOfRows, maxNumberOfColumns, round,
                 maxNumOfMines, boolGameBoard, gameBoard, boolFlagLocation);

    cout << endl << "TEST SET 2" << endl;
    playBotMovesMethod2(knownMines, maxNumberOfRows, maxNumberOfColumns, round,
                        maxNumOfMines, boolGameBoard, gameBoard,
                        boolFlagLocation);
  }
  if (win == false) {
    win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                   gameBoard, maxNumOfMines, round);
  }

  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}
