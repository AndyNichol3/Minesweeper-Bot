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
    } else {
      if (boolGameBoard[c][j] == true && gameBoard[c][j] != 0) {
        checkVert = true;
        break;
      }
    }
  }

  // index the left and right squares
  for (int r = j - 1; r < j + 2; r += 2) {
    if (r < 0 || r > maxNumberOfColumns - 1) {
      continue;
    } else {
      if (boolGameBoard[i][r] == true && gameBoard[i][r] != 0) {
        checkHor = true;
        break;
      }
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
  // rows, colums
  if (i != maxNumberOfRows - 1 && j != maxNumberOfColumns - 1) {
    if (boolGameBoard[i + 1][j] && boolGameBoard[i][j + 1]) {
      if (!boolGameBoard[i + 1][j + 1]) {
        return 4;
      }
    }
  }

  if (i != maxNumberOfRows - 1 && j != 0) {
    if (boolGameBoard[i + 1][j] && boolGameBoard[i][j - 1]) {
      if (!boolGameBoard[i + 1][j - 1]) {
        return 3;
      }
    }
  }
  if (i != 0 && j != maxNumberOfColumns - 1) {
    if (boolGameBoard[i - 1][j] && boolGameBoard[i][j + 1]) {
      if (!boolGameBoard[i - 1][j + 1]) {
        return 2;
      }
    }
  }
  if (i != 0 && j != 0) {
    if (boolGameBoard[i - 1][j] && boolGameBoard[i][j - 1]) {
      if (!boolGameBoard[i - 1][j - 1]) {
        return 1;
      }
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
  userStartCol = 5;
  cout << "bot chose X: " << userStartCol << endl;
  int userStartRow = rand() % (maxNumberOfRows - 1);
  userStartRow = 5;
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
      if (boolGameBoard[i][j] == true) {
        //
        if (gameBoard[i][j] != 0) {
          // cout << endl << j << ", " << maxNumberOfRows - 1 - i << endl;
          bool isCorner = checkCorner(i, j, maxNumberOfRows, maxNumberOfColumns,
                                      boolGameBoard, gameBoard);
          // cout << "entered 1" << endl;
          //  cout << endl << "corner found" << endl;
          if (isCorner == true && gameBoard[i][j] == 1) {
            // cout << "entered 2: input " << i << " "<< j << endl;
            int cornerLocation =
                returnCornerLocation(boolGameBoard, gameBoard, i, j,
                                     maxNumberOfRows, maxNumberOfColumns);
            // cout << "location = " << cornerLocation << endl;
            if (cornerLocation != 0) {
              // cout << "Corner: " << j << ", " << maxNumberOfRows - 1 - i <<
              // endl;

              boolFlagLocation[i][j] = true;
              pair<int, int> mineLocation = {i, j};
              // cout << "entered 3" << endl;
              pair<int, int> temp = adjustIndex(cornerLocation, mineLocation);
              // cout << "entered 4" << endl;
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
  // cout << "comeplete" <<endl;
  return knownMines;
}

void playBotMoves(set<pair<int, int>> knownMines, int maxNumberOfRows,
                  int maxNumberOfColumns, int round, int maxNumOfMines,
                  vector<vector<bool>> &boolGameBoard,
                  vector<vector<int>> &gameBoard,
                  vector<vector<bool>> &boolFlagLocation) {

  for (const auto &mineLocation : knownMines) {
    // std::cout << "working with (" << mineLocation.second << ", "
    //<< maxNumberOfRows - 1 - mineLocation.first << ")\n";
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
        if ((knownMines.find(currentLoc) != knownMines.end())) {
          continue;
        }

        if (X < 0 || X >= maxNumberOfRows || Y < 0 || Y >= maxNumberOfColumns) {
          continue;
        }

        if (boolGameBoard[X][Y]) {
          continue;
        }
        // if here, then youve found an unrevealed tile
        // cout << "\nINDEX " << index << endl;
        for (int index2 = 0; index2 < 8; index2++) {
          int X2 = X + defIndexX[index2];
          int Y2 = Y + defIndexY[index2];

          if (X2 < 0 || X2 >= maxNumberOfRows || Y2 < 0 ||
              Y2 >= maxNumberOfColumns) {
            continue;
          }
          pair<int, int> check = {X2, Y2};
          if ((knownMines.find(check) != knownMines.end())) {
            // cout << "flag" << endl;
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
              // cout << endl <<"INDEX 2 " << endl;
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
}

void playBotMovesMethod2(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumberOfColumns, int round, int maxNumOfMines,
                         vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard,
                         vector<vector<bool>> &boolFlagLocation) {
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
}