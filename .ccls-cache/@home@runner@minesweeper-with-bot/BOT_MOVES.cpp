#include "stdafx.h"

bool playFullBot(int maxNumberOfRows, int maxNumberOfColumns, int maxNumOfMines,
                 int &round, set<pair<int, int>> knownMines,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard) {
  bool botHasHaulted = false;
  bool continueGame = true;
  bool cornersLeftToGuess = true;

  int revealTally = 0, maxDisplay = maxNumberOfRows * maxNumberOfColumns,
      userRow = -2, userCol = -2;

  while (continueGame) {
    int confirmedMineTally = 0;

    knownMines =
        botCheckForMines(knownMines, maxNumberOfRows, maxNumberOfColumns, round,
                         maxNumOfMines, boolGameBoard, gameBoard);

    confirmedMineTally =
        printBotFlaggedMines(knownMines, maxNumberOfRows, maxNumOfMines);

    if (confirmedMineTally == maxNumOfMines) {
      cout << endl << "All Mines Found" << endl;
      botHasHaulted =
          foundAllMines(knownMines, maxNumberOfRows, maxNumberOfColumns, round,
                        maxNumOfMines, boolGameBoard, gameBoard);
      continueGame = false;
      break;
    }
    if (confirmedMineTally == 0) {
      cout << endl << "No Mines Found" << endl;
    }

    bool changesMadeMethod2 =
        playBotMovesMethod2(knownMines, maxNumberOfRows, maxNumberOfColumns,
                            round, maxNumOfMines, boolGameBoard, gameBoard);

    bool changesMadeMethod1 =
        playBotMovesMethod1(knownMines, maxNumberOfRows, maxNumberOfColumns,
                            round, maxNumOfMines, boolGameBoard, gameBoard);

    if (changesMadeMethod1 || changesMadeMethod2) {
      continue;
    }

    cout << endl << "No Further Confident Moves" << endl;
    cout << "Bot will guess" << endl;
    // this_thread::sleep_for(chrono::milliseconds(2000));

    if (cornersLeftToGuess) {
      cout << endl << "Guessing The Corners" << endl;
      int returnedError =
          guessCorners(maxNumberOfRows, maxNumberOfColumns, boolGameBoard,
                       gameBoard, maxNumOfMines, round, knownMines);
      // 1 is the error value that indicated no corners left
      if (returnedError == 1) {
        cornersLeftToGuess = false;
      }
      continue;
    }

    cout << endl << "Doing A Math Weighted Guess" << endl;
    // sleep function so if this decides to infinate loop it doesnt overflow
    // my terminal
    // this_thread::sleep_for(chrono::milliseconds(2000));

    // try to add another
    // prompt user to ask if it wants to make one guess or let the bot guess
    // (warning: chance of failure)
    tuple<int, int, int> bestGuess;
    bestGuess =
        mathWeightedGuess(knownMines, maxNumberOfRows, maxNumberOfColumns,
                          round, maxNumOfMines, boolGameBoard, gameBoard);
    if (get<1>(bestGuess) == -1) {
      cout << "No Guess Can Be Made" << endl;
      break;
    }
    cout << "Best Guess: " << get<2>(bestGuess) << " "
         << maxNumberOfRows - 1 - get<1>(bestGuess) << " with weight "
         << get<0>(bestGuess) << endl;

    knownMines.insert({get<1>(bestGuess), get<2>(bestGuess)});
    confirmedMineTally =
        printBotFlaggedMines(knownMines, maxNumberOfRows, maxNumOfMines);

    continue;
  }

  return botHasHaulted;
}

bool playBotMovesMethod1(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumberOfColumns, int &round, int maxNumOfMines,
                         vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard) {
  int movesMade = 0;

  for (const auto &mineLocation : knownMines) {

    bool botCanStillPlay = true;
    while (botCanStillPlay) {
      int itterations = 0;
      // given the location of a mine
      // if there exists an unrevealed tile within the 8 immediade sorrunding
      // tiles that is adjacent to a revaled tile with the value of 1 play the
      // unrevealed round and restart

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
            //! boolGameBoard[X][Y] && !boolFlagLocation[X][Y]
            if (!boolGameBoard[X][Y]) {
              itterations++;
              movesMade++;
              // cout << endl <<"INDEX 2 " << endl;
              completeBotRound(maxNumberOfColumns, maxNumberOfRows,
                               boolGameBoard, gameBoard, maxNumOfMines, X, Y,
                               round, knownMines);
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
                         vector<vector<int>> &gameBoard) {
  int changesMade = 1;
  int squaresPlayed = 0;
  // while changes are still being made
  // denoted wirh continueBot
  while (changesMade != 0) {
    changesMade = 0;
    for (int rowIndex = 0; rowIndex < maxNumberOfRows; rowIndex++) {
      for (int colIndex = 0; colIndex < maxNumberOfColumns; colIndex++) {

        if (boolGameBoard[rowIndex][colIndex] == false) {
          continue;
        }
        if (gameBoard[rowIndex][colIndex] == 0) {
          continue;
        }
        pair<int, int> check = {rowIndex, colIndex};
        if ((knownMines.find(check) != knownMines.end())) {
          // cout << "flag" << endl;
          continue;
        }

        int knownMineTally = 0;
        int knownRevealedTally = 0;
        int totalKnownTally = 0;

        // calculate the number of known mines around the target point
        for (int subRowItterator1 = -1; subRowItterator1 <= 1;
             subRowItterator1++) {
          for (int subColItterator1 = -1; subColItterator1 <= 1;
               subColItterator1++) {

            if (subRowItterator1 == 0 && subColItterator1 == 0) {
              continue;
            }

            int rowAroundTarget = rowIndex + subRowItterator1;
            int colAroundTarget = colIndex + subColItterator1;

            if (boolGameBoard[rowAroundTarget][colAroundTarget] == true) {
              knownRevealedTally++;
            }

            pair<int, int> currentLoc = {rowAroundTarget, colAroundTarget};
            // calculate number of known mines around the current location
            if (knownMines.find(currentLoc) != knownMines.end()) {
              knownMineTally++;
            }
          }
        }

        // if the number of known mines is equal to the revealed number 
        // on the tile were working with
        if (knownMineTally == gameBoard[rowIndex][colIndex]) {
          for (int subRowItterator2 = -1; subRowItterator2 <= 1;
               subRowItterator2++) {
            for (int subColItterator2 = -1; subColItterator2 <= 1;
                 subColItterator2++) {

              if (subRowItterator2 == 0 && subColItterator2 == 0) {
                continue;
              }

              int X2 = rowIndex + subRowItterator2;
              int Y2 = colIndex + subColItterator2;

              if (checkOutOfBounds(X2, Y2, maxNumberOfRows,
                                   maxNumberOfColumns)) {
                continue;
              }

              // || boolFlagLocation[X2][Y2]
              if (boolGameBoard[X2][Y2]) {
                continue;
              }
              pair<int, int> newLoc = {X2, Y2};
              if (knownMines.find(newLoc) != knownMines.end()) {
                continue;
              }
              changesMade++;
              squaresPlayed++;
              completeBotRound(maxNumberOfColumns, maxNumberOfRows,
                               boolGameBoard, gameBoard, maxNumOfMines, X2, Y2,
                               round, knownMines);
            }
          }
        }
      }
    }
    if (changesMade == 0) {
      break;
    }
  }
  if (squaresPlayed == 0) {
    return false;
  }
  return true;
}

set<pair<int, int>> botCheckForMines(set<pair<int, int>> knownMines,
                                     int maxNumberOfRows,
                                     int maxNumberOfColumns, int &round,
                                     int maxNumOfMines,
                                     vector<vector<bool>> &boolGameBoard,
                                     vector<vector<int>> &gameBoard) {

  for (int rowIndex = 0; rowIndex < maxNumberOfRows; rowIndex++) {
    for (int colIndex = 0; colIndex < maxNumberOfColumns; colIndex++) {
      if (boolGameBoard[rowIndex][colIndex] == false) {
        continue;
      }
      int unrevTiles = 0;
      set<pair<int, int>> potentialMines;

      for (int subRowItterator = -1; subRowItterator <= 1; subRowItterator++) {
        for (int subColItterator = -1; subColItterator <= 1;
             subColItterator++) {

          if (subRowItterator == 0 && subColItterator == 0) {
            continue;
          }
          int workingRow = rowIndex + subRowItterator;
          int workingCol = colIndex + subColItterator;

          if (checkOutOfBounds(workingRow, workingCol, maxNumberOfRows,
                               maxNumberOfColumns)) {
            continue;
          }
          if (boolGameBoard[workingRow][workingCol] == false) {
            unrevTiles++;
            potentialMines.insert({workingRow, workingCol});
          }
        }
      }
      if (unrevTiles != gameBoard[rowIndex][colIndex]) {
        continue;
      }
      for (const auto &curMine : potentialMines) {
        if (knownMines.find(curMine) != knownMines.end()) {
          continue;
        }
        knownMines.insert(curMine);
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

  for (int rowIndex = 0; rowIndex < maxNumberOfRows; ++rowIndex) {
    for (int colIndex = 0; colIndex < maxNumberOfColumns; ++colIndex) {

      if (boolGameBoard[rowIndex][colIndex] == true) {
        continue;
      }

      pair<int, int> tempPair = {rowIndex, colIndex};

      // if temp pair is found in, continue
      if (knownMines.find(tempPair) != knownMines.end()) {
        continue;
      }

      int sumOfDifferences = 0;

      for (int subRowItterator = -1; subRowItterator <= 1; subRowItterator++) {
        for (int subColItterator = -1; subColItterator <= 1;
             subColItterator++) {
          // skip current tile
          if (subRowItterator == 0 && subColItterator == 0) {
            continue;
          }

          int workingRow = rowIndex + subRowItterator;
          int workingCol = colIndex + subColItterator;
          // if currrent tile out of bounds skip
          if (checkOutOfBounds(workingRow, workingCol, maxNumberOfRows,
                               maxNumberOfColumns)) {
            continue;
          }
          // if the tile is unrevealed, skip
          if (boolGameBoard[workingRow][workingCol] == false) {
            continue;
          }

          pair<int, int> newGuess = {workingRow, workingCol};
          // if new guess is found in, continue
          if (knownMines.find(newGuess) != knownMines.end()) {
            continue;
          }
          // known mines around it add the difference to the sum total for the
          // unrevealed tile
          int sorrundingMineCount = returnSorrundingMineCount(
              workingRow, workingCol, maxNumberOfRows, maxNumberOfColumns,
              boolGameBoard, gameBoard, knownMines);

          // cout << sorrundingMineCount << " mines counted for tile " << Y<<
          // maxNumberOfRows - 1 - X<<endl;

          int difference =
              abs(sorrundingMineCount - gameBoard[workingRow][workingCol]);
          sumOfDifferences += difference;
          sorrundingMineCount = 0;
        }
      }

      if (sumOfDifferences > get<0>(storageTuple)) {
        cout << "new best guess: " << colIndex << " "
             << maxNumberOfRows - 1 - rowIndex << " weight " << sumOfDifferences
             << endl;
        cout << " replaces " << get<2>(storageTuple) << " "
             << maxNumberOfRows - 1 - get<1>(storageTuple) << " weight "
             << get<0>(storageTuple) << endl;
        storageTuple = {sumOfDifferences, rowIndex, colIndex};
      }
    }
  }

  return {storageTuple};
}
