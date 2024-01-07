#include "BOT_MOVES.h"
#include "BOT_FUNCTIONS.h"
#include "PLAY_GAME.h"

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

bool playBotMovesMethod1(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumberOfColumns, int &round, int maxNumOfMines,
                         vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard,
                         vector<vector<bool>> &boolFlagLocation) {
  int movesMade = 0;

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
        // X < 0 || X >= maxNumberOfRows || Y < 0 || Y >= maxNumberOfColumns
        if (checkOutOfBounds(X, Y, maxNumberOfRows, maxNumberOfColumns)) {
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
          // X2 < 0 || X2 >= maxNumberOfRows || Y2 < 0 ||Y2 >=
          // maxNumberOfColumns
          if (checkOutOfBounds(X2, Y2, maxNumberOfRows, maxNumberOfColumns)) {
            continue;
          }
          if (boolGameBoard[X2][Y2] == false) {
            continue;
          }
          if (gameBoard[X2][Y2] != 1) {
            continue;
          }

          pair<int, int> check = {X2, Y2};
          if ((knownMines.find(check) != knownMines.end())) {
            // cout << "flag" << endl;
            continue;
          }

          // if here then youve found a revealed tile
          // create a set of the tiles aroud the mine

          // if the check is not in the set, continue

          set<pair<int, int>> aroundMine;
          for (int ind = 0; ind < 8; ind++) {
            int checkX = mineLocation.first + defIndexX[ind];
            int checkY = mineLocation.second + defIndexY[ind];

            if (checkOutOfBounds(checkX, checkY, maxNumberOfRows,
                                 maxNumberOfColumns)) {
              continue;
            }

            pair<int, int> checkAround = {checkX, checkY};
            aroundMine.insert(checkAround);
          }
          // if the check is not in the set, continue
          if (aroundMine.find(check) == aroundMine.end()) {
            continue;
          }

          bool caseOne = (abs(X - X2) == 0 && abs(Y - Y2) <= 1);
          bool caseTwo = (abs(Y - Y2) == 0 && abs(X - X2) <= 1);
          if (caseTwo || caseOne) {
            if (!boolGameBoard[X][Y] && !boolFlagLocation[X][Y]) {
              itterations++;
              movesMade++;
              // cout << endl <<"INDEX 2 " << endl;
              completeBotRound(maxNumberOfColumns, maxNumberOfRows,
                               boolGameBoard, gameBoard, maxNumOfMines, X, Y,
                               round, boolFlagLocation);
              round++;
            }
          }
        }
      }

      if (itterations == 0) {
        botCanStillPlay = false;
      }
    }
  }

  if (movesMade == 0) {
    // no alterations were made
    return false;
  }
  return true;
}

bool playBotMovesMethod2(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumberOfColumns, int &round, int maxNumOfMines,
                         vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard,
                         vector<vector<bool>> &boolFlagLocation) {
  int continueBot = 1;
  int squaresPlayed = 0;
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

            if (checkOutOfBounds(X2, Y2, maxNumberOfRows, maxNumberOfColumns)) {
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
            squaresPlayed++;
            completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                             gameBoard, maxNumOfMines, X2, Y2, round,
                             boolFlagLocation);
            round++;
          }
        }
      }
    }
    if (continueBot == 0) {
      break;
    }
  }
  if (squaresPlayed == 0) {
    return false;
  }
  return true;
}

set<pair<int, int>> botCheckForMines(
    set<pair<int, int>> knownMines, int maxNumberOfRows, int maxNumberOfColumns,
    int &round, int maxNumOfMines, vector<vector<bool>> &boolGameBoard,
    vector<vector<int>> &gameBoard, vector<vector<bool>> &boolFlagLocation) {

  for (int i = 0; i < maxNumberOfRows; ++i) {
    for (int j = 0; j < maxNumberOfColumns; ++j) {
      if (boolGameBoard[i][j] == false) {
        continue;
      }

      int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
      int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
      int unrevTiles = 0;
      // int knownTally = 0;
      set<pair<int, int>> potentialMines;

      for (int index = 0; index < 8; index++) {
        int X = i + defIndexX[index];
        int Y = j + defIndexY[index];

        if (checkOutOfBounds(X, Y, maxNumberOfRows, maxNumberOfColumns)) {
          // knownTally++;
          continue;
        }

        if (boolGameBoard[X][Y] == false) {
          unrevTiles++;
          potentialMines.insert({X, Y});
        }
      }

      if (unrevTiles != gameBoard[i][j]) {
        continue;
      }

      for (const auto &mine : potentialMines) {
        if (knownMines.find(mine) != knownMines.end()) {
          continue;
        }
        boolFlagLocation[mine.first][mine.second] = true;
        knownMines.insert(mine);
      }
    }
  }

  return knownMines;
}

tuple<int, int, int> mathWeightedGuess(set<pair<int, int>> knownMines,
                                       int maxNumberOfRows,
                                       int maxNumberOfColumns, int &round,
                                       int maxNumOfMines,
                                       vector<vector<bool>> &boolGameBoard,
                                       vector<vector<int>> &gameBoard) {
  // potential line of logic based on the number of mines needed to fufil a
  // square create a temp game board, given a revealed tile, if gameBoard -
  // number of sorruinging mines == 0; continue is not, add the absolute value
  // of difference to all of the sorrunding unrevealed tiles. store the highest
  // index and pair this index is most likely a mine, store known mines, restart
  // calcualting loop

  // weight, x, y
  tuple<int, int, int> storageTuple = {0, -1, -1};

  for (int i = 0; i < maxNumberOfRows; ++i) {
    for (int j = 0; j < maxNumberOfColumns; ++j) {

      if (boolGameBoard[i][j] == true) {
        continue;
      }

      pair<int, int> tempPair = {i, j};
      if (knownMines.find(tempPair) != knownMines.end()) {
        continue;
      }
      // given an unrevealed tile,
      // for all of the tiles around it,

      // cout << "working with: " << get<2>(bestGuess) << " "
      //<< maxNumberOfRows - 1 - get<1>(bestGuess) <<" with weight "<<
      //get<0>(bestGuess) <<endl;
      
      //cout<< endl << "working with " << j << " " << maxNumberOfRows - 1 - i << endl; 

      int sumOfDifferences = 0;

      for (int k = -1; k < 2; ++k) {
        for (int l = -1; l < 2; ++l) {
          if (k == 0 && l == 0) {
            continue;
          }
          int X = i + k;
          int Y = j + l;

          if (checkOutOfBounds(X, Y, maxNumberOfRows, maxNumberOfColumns)) {
            continue;
          }
          if (boolGameBoard[X][Y] == false) {
            continue;
          }
          
          pair<int, int> newGuess = {X, Y};
          if (knownMines.find(newGuess) != knownMines.end()) {
            continue;
          }
          // cout << "   working with sub int" << Y << " " << maxNumberOfRows - 1 - X << endl; 
          // calculate the difference between tile int and the known mines
          // around it add the difference to the sum total for the unrevealed
          // tile
         // if (gameBoard[i][j] == true) {
            int sorrundingMineCount = 0;
          
            for (int m = -1; m < 2; ++m) {
              for (int n = -1; n < 2; ++n) {
                if (m == 0 && n == 0) {
                  continue;
                }
                
                int X2 = i + m;
                int Y2 = j + n;

                // cout << "        working with sub int" << Y2 << " " << maxNumberOfRows - 1 - X2 << endl; 

                if (checkOutOfBounds(X2, Y2, maxNumberOfRows,
                                     maxNumberOfColumns)) {
                 // cout << "out of bounds" << endl;
                  continue;
                }
                if (boolGameBoard[X2][Y2] == true) {
                  
                  continue;
                }
                pair<int, int> newGuess2 = {X2, Y2};
                
                if (knownMines.find(newGuess2) != knownMines.end()) {
                 // cout << "        added " << Y2 << " " << maxNumberOfRows - 1 - X2 << endl;              
                  sorrundingMineCount++;
                }
              }
            }

            cout << sorrundingMineCount << " mines counted for tile " << Y<< maxNumberOfRows - 1 - X<<endl;

            int difference = abs(sorrundingMineCount - gameBoard[X][Y]);
            sumOfDifferences += difference;
            sorrundingMineCount = 0;
          //}
        }
     }

      if (sumOfDifferences > get<0>(storageTuple)) {
        cout << "new best guess: " << j << " " << maxNumberOfRows - 1 - i << " weight " << sumOfDifferences << endl;
        cout << " replaces " << get<2>(storageTuple) << " " <<  maxNumberOfRows - 1 - get<1>(storageTuple) << " weight " << get<0>(storageTuple) << endl;
        storageTuple = {sumOfDifferences, i, j};
      }
    }
  }

  return {storageTuple};
}

bool playBotMovesMethod1andahalf(set<pair<int, int>> knownMines,
                                 int maxNumberOfRows, int maxNumberOfColumns,
                                 int &round, int maxNumOfMines,
                                 vector<vector<bool>> &boolGameBoard,
                                 vector<vector<int>> &gameBoard,
                                 vector<vector<bool>> &boolFlagLocation) {
  int movesMade = 0;

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

      for (int indexX = -1; indexX <= 1; indexX++) {
        for (int indexY = -1; indexY <= 1; indexY++) {
          int X = mineLocation.first + indexX;
          int Y = mineLocation.second + indexY;

          pair<int, int> currentLoc = {X, Y};
          if ((knownMines.find(currentLoc) != knownMines.end())) {
            continue;
          }
          // X < 0 || X >= maxNumberOfRows || Y < 0 || Y >= maxNumberOfColumns
          if (checkOutOfBounds(X, Y, maxNumberOfRows, maxNumberOfColumns)) {
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
            // X2 < 0 || X2 >= maxNumberOfRows || Y2 < 0 ||Y2 >=
            // maxNumberOfColumns
            if (checkOutOfBounds(X2, Y2, maxNumberOfRows, maxNumberOfColumns)) {
              continue;
            }
            if (boolGameBoard[X2][Y2] == false) {
              continue;
            }
            if (gameBoard[X2][Y2] != 1) {
              continue;
            }

            pair<int, int> check = {X2, Y2};
            if ((knownMines.find(check) != knownMines.end())) {
              // cout << "flag" << endl;
              continue;
            }

            // if here then youve found a revealed tile
            // create a set of the tiles aroud the mine

            // if the check is not in the set, continue

            set<pair<int, int>> aroundMine;
            for (int ind = 0; ind < 8; ind++) {
              int checkX = mineLocation.first + defIndexX[ind];
              int checkY = mineLocation.second + defIndexY[ind];

              if (checkOutOfBounds(checkX, checkY, maxNumberOfRows,
                                   maxNumberOfColumns)) {
                continue;
              }

              pair<int, int> checkAround = {checkX, checkY};
              aroundMine.insert(checkAround);
            }
            // if the check is not in the set, continue
            if (aroundMine.find(check) == aroundMine.end()) {
              continue;
            }

            bool caseOne = (abs(X - X2) == 0 && abs(Y - Y2) <= 1);
            bool caseTwo = (abs(Y - Y2) == 0 && abs(X - X2) <= 1);
            if (caseTwo || caseOne) {
              if (!boolGameBoard[X][Y] && !boolFlagLocation[X][Y]) {
                itterations++;
                movesMade++;
                // cout << endl <<"INDEX 2 " << endl;
                completeBotRound(maxNumberOfColumns, maxNumberOfRows,
                                 boolGameBoard, gameBoard, maxNumOfMines, X, Y,
                                 round, boolFlagLocation);
                round++;
              }
            }
          }
        }
      }

      // for (int index = 0; index < 8; index++) {}

      if (itterations == 0) {
        botCanStillPlay = false;
      }
    }
  }

  if (movesMade == 0) {
    // no alterations were made
    return false;
  }
  return true;
}