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
  set<pair<int, int>> knownMines =
      calculateInitialKnownMines(maxNumberOfColumns, maxNumberOfRows,
                                 boolGameBoard, gameBoard, boolFlagLocation);

  for (const auto &mineLocation : knownMines) {
    std::cout << "Mine at coordinates (" << mineLocation.second << ", "
              << maxNumberOfRows - 1 - mineLocation.first << ")\n";
  }

  cout << endl << "TEST SET 1" << endl;

  playBotMoves(knownMines, maxNumberOfRows, maxNumberOfColumns, round,
               maxNumOfMines, boolGameBoard, gameBoard, boolFlagLocation);

  // given a tile
  // if the tile is not revealed continue
  // if the tile == 0 continue
  // give the tile
  // check all 8 tiles around it,
  // tally the number of know mines in those 8
  // if tally == value of the tile
  // anything adjacent shoudl be valid to click
  // cycle through 8 adjacent tiles
  // if the tile is not revealed and is in bounds, reveal

  cout << endl << "TEST SET 2" << endl;
  int continueBot = 1;
  while (continueBot != 0) {
    continueBot = 0;
    for (int i = 0; i < maxNumberOfRows; ++i) {
      for (int j = 0; j < maxNumberOfColumns; ++j) {
        if (boolGameBoard[i][j] == false) {
          continue;
        }
        if (gameBoard[i][j] == 0) {
          continue;
        }

        int knownMineTally = 0;
        int knownRevealedTally = 0;
        int totalKnownTally = 0;
        int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int index = 0; index < 8; index++) {
          int X = i + defIndexX[index];
          int Y = j + defIndexY[index];

          if (boolGameBoard[X][Y] == true) {
            knownRevealedTally++;
          }

          pair<int, int> currentLoc = {X, Y};
          if (knownMines.find(currentLoc) != knownMines.end()) {
            knownMineTally++;
          }
        }

        // totalKnownTally = knownMineTally + knownRevealedTally;

        if (knownMineTally == gameBoard[i][j]) {
          for (int index2 = 0; index2 < 8; index2++) {
            int X2 = i + defIndexX[index2];
            int Y2 = j + defIndexY[index2];

            if (X2 < 0 || X2 >= maxNumberOfRows || Y2 < 0 ||
                Y2 >= maxNumberOfColumns) {
              continue;
            }
            if (boolGameBoard[X2][Y2] || boolFlagLocation[X2][Y2]) {
              continue;
            }
            pair<int, int> newLoc = {X2, Y2};
            if (knownMines.find(newLoc) != knownMines.end()) {
              continue;
            }
            continueBot++;
            completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                             gameBoard, maxNumOfMines, X2, Y2, round);
          }
        }
      }
    }
    if (continueBot == 0) {
      break;
    }
  }

  //
  // loop here

  win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard, gameBoard,
                 maxNumOfMines, round);

  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}

