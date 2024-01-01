#include "BOT_FUNCTIONS.h"
#include "PLAY_GAME.h"
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;

bool checkCorner(int i, int j, int maxNumberOfRows, int maxNumberOfColumns,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard) {
  bool checkVert = false;
  bool checkHor = false;

  // index the above and below squares
  for (int c = i - 1; c < i + 2; c += 2) {
    // if its revealed, checkVert = true
    if (c < 0 || c > maxNumberOfRows - 1) {
      continue;
    }
    if (boolGameBoard[c][j] == true && gameBoard[c][j] != 0) {
      checkVert = true;
      break;
    }
  }

  // index the left and right squares
  for (int r = j - 1; r < j + 2; r += 2) {
    if (r < 0 || r > maxNumberOfColumns - 1) {
      continue;
    }
    if (boolGameBoard[i][r] == true && gameBoard[i][r] != 0) {
      checkHor = true;
      break;
    }
  }

  // if its revealed, checkHor = true

  // if(check vert and hor == true){
  if (checkVert == true && checkHor == true) {
    return true;
  }
  // return true;
  // }

  return false;
}

int returnCornerLocation(vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard, int i, int j,
                         int maxNumberOfRows, int maxNumberOfColumns) {

  int cornerLocation = 0;
  //  1 |  | 2
  //    |ij|
  //  3 |  | 4

  if (boolGameBoard[i + 1][j] && boolGameBoard[i][j + 1]) {
    if (!boolGameBoard[i + 1][j + 1]) {
      return 4;
    }
  }
  if (boolGameBoard[i + 1][j] && boolGameBoard[i][j - 1]) {
    if (!boolGameBoard[i + 1][j - 1]) {
      return 3;
    }
  }

  if (boolGameBoard[i - 1][j] && boolGameBoard[i][j + 1]) {
    if (!boolGameBoard[i - 1][j + 1]) {
      return 2;
    }
  }
  if (boolGameBoard[i - 1][j] && boolGameBoard[i][j - 1]) {
    if (!boolGameBoard[i - 1][j - 1]) {
      return 1;
    }
  }

  return 0;
}

bool playRoundBot(int maxNumberOfColumns, int maxNumberOfRows,
                  vector<vector<bool>> &boolGameBoard,
                  vector<vector<int>> &gameBoard, int maxNumOfMines,
                  int userRow, int userCol) {
  bool gameOver = false;
  bool revealedTile = false;
  while (!revealedTile) {

    cout << "Bot Plays: " << endl;

    cout << "bot chose X: " << userCol << endl;

    cout << "bot chose Y: " << maxNumberOfRows - 1 - userRow << endl;

    // userCol = getInputX(maxNumberOfColumns);
    // userRow = getInputY(maxNumberOfRows);

    if (boolGameBoard[userRow][userCol] == true) {
      cout << "You have already revealed this tile!\n" << endl;
    } else {
      revealedTile = true;
      break;
    }
  }

  if (gameBoard[userRow][userCol] == -1) {
    gameOver = true;
    cout << "you hit a mine!" << endl;
    boolGameBoard[userRow][userCol] = true;

  } else {
    boolGameBoard[userRow][userCol] = true;
    if (gameBoard[userRow][userCol] == 0) {
      recursiveRevealExplosion(gameBoard, boolGameBoard, userRow, userCol,
                               maxNumberOfRows, maxNumberOfColumns);
    }
  }

  return gameOver;
}

bool playRoundUser(int maxNumberOfColumns, int maxNumberOfRows,
                   vector<vector<bool>> &boolGameBoard,
                   vector<vector<int>> &gameBoard, int maxNumOfMines,
                   int userRow, int userCol) {

  bool gameOver = false;
  bool revealedTile = false;
  while (!revealedTile) {

    cout << "Enter Next Point (-1 to exit): " << endl;

    userCol = getInputX(maxNumberOfColumns);
    userRow = getInputY(maxNumberOfRows);

    if (boolGameBoard[userRow][userCol] == true) {
      cout << "You have already revealed this tile!\n" << endl;
    } else {
      revealedTile = true;
      break;
    }
  }

  if (gameBoard[userRow][userCol] == -1) {
    gameOver = true;
    cout << "you hit a mine!" << endl;
    boolGameBoard[userRow][userCol] = true;

  } else {
    boolGameBoard[userRow][userCol] = true;
    if (gameBoard[userRow][userCol] == 0) {
      recursiveRevealExplosion(gameBoard, boolGameBoard, userRow, userCol,
                               maxNumberOfRows, maxNumberOfColumns);
    }
  }

  return gameOver;
}

pair<int, int> adjustIndex(int cornerLocation, pair<int, int> mineLocation) {

  if (cornerLocation == 1) {
    mineLocation.first--;
    mineLocation.second--;
  } else if (cornerLocation == 2) {
    mineLocation.first--;
    mineLocation.second++;
  } else if (cornerLocation == 3) {
    mineLocation.first++;
    mineLocation.second--;
  } else if (cornerLocation == 4) {
    mineLocation.first++;
    mineLocation.second++;
  }

  return mineLocation;
}

void initalizeBotGameBoard(vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard, int maxNumberOfRows,
                           int maxNumberOfColumns, int maxNumOfMines) {
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);
  printRoundHeader(1);

  // cout << "Enter Starting Point (-1 to exit): " << endl;
  cout << "the bot will now start" << endl;
  srand(time(NULL));
  int userStartCol = rand() % (maxNumberOfColumns - 1);
  cout << "bot chose X: " << userStartCol << endl;
  int userStartRow = rand() % (maxNumberOfRows - 1);
  cout << "bot chose Y: " << maxNumberOfRows - 1 - userStartRow << endl;

  cout << endl;

  boolGameBoard[userStartRow][userStartCol] = true;

  fillWithMines(gameBoard, userStartRow, userStartCol, maxNumOfMines,
                maxNumberOfRows, maxNumberOfColumns);
  fillWithInts(gameBoard, maxNumberOfRows, maxNumberOfColumns);
  recursiveRevealExplosion(gameBoard, boolGameBoard, userStartRow, userStartCol,
                           maxNumberOfRows, maxNumberOfColumns);
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);
}

bool completeBotRound(int maxNumberOfColumns, int maxNumberOfRows,
                      vector<vector<bool>> &boolGameBoard,
                      vector<vector<int>> &gameBoard, int maxNumOfMines,
                      int userRow, int userCol, int round) {
  int maxDisplay = maxNumberOfRows * maxNumberOfColumns;
  bool win = false;
  // round++;
  printRoundHeader(round);

  bool gameOver =
      playRoundBot(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                   gameBoard, maxNumOfMines, userRow, userCol);

  int revealTally = printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows,
                                   maxNumberOfColumns);

  if (revealTally == (maxDisplay - maxNumOfMines)) {
    gameOver = true;
    win = true;
  }

  return win;
}

set<pair<int, int>>
calculateInitialKnownMines(int maxNumberOfColumns, int maxNumberOfRows,
                           vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard,
                           vector<vector<bool>> &boolFlagLocation) {
  set<pair<int, int>> knownMines;
  for (int i = 0; i < maxNumberOfRows; i++) {
    for (int j = 0; j < maxNumberOfColumns; j++) {
      if (gameBoard[i][j] != 0) {
        if (boolGameBoard[i][j] == true) {
          bool isCorner = checkCorner(i, j, maxNumberOfRows, maxNumberOfColumns,
                                      boolGameBoard, gameBoard);
          // cout << endl << "corner found" << endl;
          if (isCorner == true && gameBoard[i][j] == 1) {

            int cornerLocation =
                returnCornerLocation(boolGameBoard, gameBoard, i, j,
                                     maxNumberOfRows, maxNumberOfColumns);
            // cout << "location = " << cornerLocation << endl;
            if (cornerLocation != 0) {
              // cout << "Corner: " << j << ", " << maxNumberOfRows - 1 - i <<
              // endl;

              boolFlagLocation[i][j] = true;
              pair<int, int> mineLocation = {i, j};
              pair<int, int> temp = adjustIndex(cornerLocation, mineLocation);
              if (knownMines.count(temp) == 0) {
                knownMines.insert(temp);
              }
              // knownMines.push({i, j});
            }
          }
        }
      }
    }
  }

  return knownMines;
}