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
  cout << "Bots flagged Point: " << endl;

  set<pair<int, int>> knownMines =
      calculateInitialKnownMines(maxNumberOfColumns, maxNumberOfRows,
                                 boolGameBoard, gameBoard, boolFlagLocation);

  // adjust i and j
  int userRow = -2, userCol = -2;

  for (const auto &mineLocation : knownMines) {
    std::cout << "Mine at coordinates (" << mineLocation.second << ", "
              << maxNumberOfRows - 1 - mineLocation.first << ")\n";
  }

  cout << endl << "TEST SET 1" << endl;

  for (const auto &mineLocation : knownMines) {
    bool botCanStillPlay = true;
    while (botCanStillPlay) {
      int itterations = 0;
      // given the location of a mine
      // if there exists an unrevealed tile within the 8 immediade sorrunding
      // tiles that is adjacent to a revaled tile with the value of 1 play the
      // unrevealed round and restart

      // bool mineAdjHasUnrevealed = checkAdjForEmptySpace()
      // if(!mineAdjHasUnrevealed){
      // break;
      // }
      int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
      int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

      for (int index = 0; index < 8; index++) {
        int X = mineLocation.first + defIndexX[index];
        int Y = mineLocation.second + defIndexY[index];
        pair<int, int> currentLoc = {X, Y};
        // if(!(knownMines.find(currentLoc) != knownMines.end())){
        // continue;
        // }

        if (X < 0 || X >= maxNumberOfRows || Y < 0 || Y >= maxNumberOfColumns) {
          continue;
        }

        if (boolGameBoard[X][Y]) {
          continue;
        }
        // if here, then youve found an unrevealed tile
        for (int index2 = 0; index2 < 8; index2++) {
          int X2 = X + defIndexX[index2];
          int Y2 = Y + defIndexY[index2];

          if (X2 < 0 || X2 >= maxNumberOfRows || Y2 < 0 ||
              Y2 >= maxNumberOfColumns) {
            continue;
          }

          if (!boolGameBoard[X2][Y2]) {
            continue;
          }
          // if here then youve found a revealed tile
          if (!boolGameBoard[X2][Y2] || gameBoard[X2][Y2] != 1) {
            continue;
          }
          bool xCriteria = (abs(X - X2) == 0 && abs(Y - Y2) <= 1);
          bool yCriteria = (abs(Y - Y2) == 0 && abs(X - X2) <= 1);
          if (yCriteria || xCriteria) {
            if (!boolGameBoard[X][Y] && !boolFlagLocation[X][Y]) {
              itterations++;

              completeBotRound(maxNumberOfColumns, maxNumberOfRows,
                               boolGameBoard, gameBoard, maxNumOfMines, X, Y,
                               round);
            }
          }
        }
      }

      if (itterations == 0) {
        botCanStillPlay = false;
      }
    }
  }

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
  for (int i = 0; i < maxNumberOfRows; ++i) {
    for (int j = 0; j < maxNumberOfColumns; ++j) {
      if (boolGameBoard[i][j] == false) {
        continue;
      }
      if (gameBoard[i][j] == 0) {
        continue;
      }

      int knownMineTally = 0;
      int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
      int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

      for (int index = 0; index < 8; index++) {
        int X = i + defIndexX[index];
        int Y = j + defIndexY[index];

        pair<int, int> currentLoc = {X, Y};
        if (knownMines.find(currentLoc) != knownMines.end()) {
          knownMineTally++;
        }
      }

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
          completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                           gameBoard, maxNumOfMines, X2, Y2, round);
        }
      }
    }
  }

  
  

  win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard, gameBoard,
                 maxNumOfMines, round);

  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}
