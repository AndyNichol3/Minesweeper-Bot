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

  // while(botCanStillPlay) {
  // given the location of a mine
  // if there exists an unrevealed tile within the 8 immediade sorrunding tiles
  // that is adjacent to a revaled tile with the value of 1 play the unrevealed
  // round and restart

  //  }

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
            itterations++;
            completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                             gameBoard, maxNumOfMines, X, Y, round);
          }
        }
      }

      if (itterations == 0) {
        botCanStillPlay = false;
      }
    }
  }

  /*
  bool nextMoves = false;
  while (!nextMoves) {
    int changes = 0;
    for (const auto &mineLocation : knownMines) {
      int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
      int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
      // fix the indexing because this jumps all over the palce
      // make it go in a circle and not all around
      for (int index = -1; index < 7; index++) {
        // bool
        int x = mineLocation.first + defIndexX[index];
        int y = mineLocation.second + defIndexY[index];

        if (x < 0 || x > maxNumberOfRows - 1 || y < 0 ||
            y > maxNumberOfColumns - 1) {
          continue;
        }
        bool check = boolGameBoard[x][y];

        int x2 = mineLocation.first + defIndexX[index + 1];
        int y2 = mineLocation.second + defIndexY[index + 1];
        if (x2 < 0 || x2 > maxNumberOfRows - 1 || y2 < 0 ||
            y2 > maxNumberOfColumns - 1) {
          continue;
        }

        bool check2 = boolGameBoard[x2][y2];
        if (check && !check2) {
          cout << endl << "ENTERED" << endl;
          changes++;
          if (!check) {
            // check location is next coord

            userRow = x, userCol = y;
            round++;
            win = completeBotRound(maxNumberOfColumns, maxNumberOfRows,
                                   boolGameBoard, gameBoard, maxNumOfMines,
                                   userRow, userCol, round);
            if (win == true) {
              break;
            }
          } else {
            // check location is next coord

            userRow = x2, userCol = y2;
            round++;
            win = completeBotRound(maxNumberOfColumns, maxNumberOfRows,
                                   boolGameBoard, gameBoard, maxNumOfMines,
                                   userRow, userCol, round);
            if (win == true) {
              break;
            }
          }
        }
      }
    }
    if (changes == 0) {
      nextMoves = true;
    }
  }
  */

  win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard, gameBoard,
                 maxNumOfMines, round);

  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}
