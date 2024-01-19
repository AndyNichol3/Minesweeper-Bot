#include "stdafx.h"

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

void triggeredAMine(int maxNumberOfRows, int maxNumberOfColumns,
                    vector<vector<bool>> &boolGameBoard,
                    vector<vector<int>> &gameBoard, int maxNumOfMines,
                    int &round, set<pair<int, int>> knownMines) {

  for (int i = 0; i < maxNumberOfRows; i++) {
    for (int j = 0; j < maxNumberOfColumns; j++) {
      if (gameBoard[i][j] == -1) {
        boolGameBoard[i][j] = true;
      }
    }
  }

  // try to open or create a knownMines.txt file
  ofstream knownMinesFile("knownMines.txt", ofstream::trunc);
  // write to the file all of the known mines
  for (auto it = knownMines.begin(); it != knownMines.end(); it++) {
    knownMinesFile << it->first << " " << it->second << endl;
  }
  knownMinesFile.close();

  knownMines.clear();
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns,
                 knownMines);
  printLose();
  exit(0);
}

bool playRoundBot(int maxNumberOfColumns, int maxNumberOfRows,
                  vector<vector<bool>> &boolGameBoard,
                  vector<vector<int>> &gameBoard, int maxNumOfMines,
                  int userRow, int userCol, int &round,

                  set<pair<int, int>> knownMines) {
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
    triggeredAMine(maxNumberOfRows, maxNumberOfColumns, boolGameBoard,
                   gameBoard, maxNumOfMines, round, knownMines);

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
    boolGameBoard[userRow][userCol] = true;
    for (int i = 0; i < maxNumberOfRows; i++) {
      for (int j = 0; j < maxNumberOfColumns; j++) {
        if (gameBoard[i][j] == -1) {
          boolGameBoard[i][j] = true;
        }
      }
    }

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
                           int maxNumberOfColumns, int maxNumOfMines,
                           int &round, set<pair<int, int>> knownMines) {
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns,
                 knownMines);
  printRoundHeader(round);
  round++;

  // cout << "Enter Starting Point (-1 to exit): " << endl;
  cout << "the bot will now start" << endl;
  srand(time(NULL));
  // int userStartCol = rand() % (maxNumberOfColumns - 1);
  int userStartCol = maxNumberOfColumns / 2;
  cout << "bot chose X: " << userStartCol << endl;
  // int userStartRow = rand() % (maxNumberOfRows - 1);
  int userStartRow = maxNumberOfRows / 2;
  cout << "bot chose Y: " << maxNumberOfRows - 1 - userStartRow << endl;

  cout << endl;

  boolGameBoard[userStartRow][userStartCol] = true;

  fillWithMines(gameBoard, userStartRow, userStartCol, maxNumOfMines,
                maxNumberOfRows, maxNumberOfColumns);
  fillWithInts(gameBoard, maxNumberOfRows, maxNumberOfColumns);
  recursiveRevealExplosion(gameBoard, boolGameBoard, userStartRow, userStartCol,
                           maxNumberOfRows, maxNumberOfColumns);
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns,
                 knownMines);
}

bool completeBotRound(int maxNumberOfColumns, int maxNumberOfRows,
                      vector<vector<bool>> &boolGameBoard,
                      vector<vector<int>> &gameBoard, int maxNumOfMines,
                      int userRow, int userCol, int &round,
                      set<pair<int, int>> knownMines) {
  // win 1
  // lose 2
  // continue 3
  int maxDisplay = maxNumberOfRows * maxNumberOfColumns;
  bool win = false;

  printRoundHeader(round);

  bool gameOver = playRoundBot(maxNumberOfColumns, maxNumberOfRows,
                               boolGameBoard, gameBoard, maxNumOfMines, userRow,
                               userCol, round, knownMines);
  if (gameOver == true) {
  }

  int revealTally = printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows,
                                   maxNumberOfColumns, knownMines);
  round++;
  if (revealTally == (maxDisplay - maxNumOfMines)) {
    gameOver = true;
    win = true;
  }

  return win;
}

set<pair<int, int>>
calculateInitialKnownMines(int maxNumberOfColumns, int maxNumberOfRows,
                           vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard) {
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

              //[i][j] = true;
              pair<int, int> mineLocation = {i, j};
              // cout << "entered 3" << endl;
              pair<int, int> temp = adjustIndex(cornerLocation, mineLocation);
              // cout << "entered 4" << endl;
              if (knownMines.count(temp) == 0) {
                //[temp.first][temp.second] = true;
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

bool foundAllMines(set<pair<int, int>> knownMines, int maxNumberOfRows,
                   int maxNumberOfColumns, int &round, int maxNumOfMines,
                   vector<vector<bool>> &boolGameBoard,
                   vector<vector<int>> &gameBoard) {

  for (int i = 0; i < maxNumberOfRows; ++i) {
    for (int j = 0; j < maxNumberOfColumns; ++j) {
      if (boolGameBoard[i][j] == true) {
        continue;
      }
      pair<int, int> test = {i, j};
      if (knownMines.find(test) != knownMines.end()) {
        continue;
      }
      // play i,j
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, i, j, round, knownMines);
    }
  }
  printWin();
  return true;
}

int printBotFlaggedMines(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumOfMines) {
  int confirmedMineTally = 0;

  for (const auto &mineLocation : knownMines) {
    confirmedMineTally++;
    // cout << "Mine at coordinates (" << mineLocation.second << ", "
    //   << maxNumberOfRows - 1 - mineLocation.first << ")\n";
  }
  cout << "There are " << confirmedMineTally << " mines flagged" << endl;
  cout << "There are " << maxNumOfMines - confirmedMineTally << " mines left"
       << endl;

  return confirmedMineTally;
}

int guessCorners(int maxNumberOfRows, int maxNumberOfColumns,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard, int maxNumOfMines, int &round,
                 set<pair<int, int>> knownMines) {
  pair<int, int> newGuess;

  newGuess = {0, maxNumberOfColumns - 1};
  if (knownMines.find(newGuess) == knownMines.end()) {
    if (boolGameBoard[0][maxNumberOfColumns - 1] == false) {
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, 0, maxNumberOfColumns - 1,
                       round, knownMines);

      return 0;
    }
  }
  newGuess = {maxNumberOfRows - 1, 0};
  if (knownMines.find(newGuess) == knownMines.end()) {
    if (boolGameBoard[maxNumberOfRows - 1][0] == false) {
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, maxNumberOfRows - 1, 0, round,
                       knownMines);

      return 0;
    }
  }
  newGuess = {maxNumberOfRows - 1, maxNumberOfColumns - 1};
  if (knownMines.find(newGuess) == knownMines.end()) {
    if (boolGameBoard[maxNumberOfRows - 1][maxNumberOfColumns - 1] == false) {
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, maxNumberOfRows - 1,
                       maxNumberOfColumns - 1, round, knownMines);

      return 0;
    }
  }
  // newGuess = {0, 0};
  //  aroundMine.find(check) != aroundMine.end()
  /*
  if (knownMines.find(newGuess) == knownMines.end()) {
    if (boolGameBoard[0][0] == false) {
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, 0, 0, round);
      return 0;
    }
  }
  */

  cout << "No corners found" << endl;
  return 1;
}

tuple<int, int, int> gameStart() {
  printGameWelcome();

  tuple<int, int, int> returnTuple;

  int difficulty = getUserDifficulty();

  // define some constasnts based on the difficulty
  switch (difficulty) {
    // <maxRows, maxColums, MaXNumOfMines>
  case 1: {
    returnTuple = make_tuple(9, 9, 10);
    break;
  }
  case 2: {
    returnTuple = make_tuple(16, 16, 40);
    break;
  }
  case 3: {
    returnTuple = make_tuple(16, 30, 99);
    break;
  }
  }

  return returnTuple;
}

bool checkOutOfBounds(int row, int col, int maxNumberOfRows,
                      int maxNumberOfColumns) {
  if (row < 0 || row >= maxNumberOfRows || col < 0 ||
      col >= maxNumberOfColumns) {
    return true;
  }
  return false;
}
int returnSorrundingMineCount(int X, int Y, int maxNumberOfRows,
                              int maxNumberOfColumns,
                              vector<vector<bool>> &boolGameBoard,
                              vector<vector<int>> &gameBoard,
                              set<pair<int, int>> knownMines) {

  int sorrundingMineCount = 0;

  for (int m = -1; m < 2; ++m) {
    for (int n = -1; n < 2; ++n) {
      if (m == 0 && n == 0) {
        continue;
      }

      int X2 = X + m;
      int Y2 = Y + n;

      // cout << "        working with sub int" << Y2 << " " << maxNumberOfRows
      // - 1 - X2 << endl;

      if (checkOutOfBounds(X2, Y2, maxNumberOfRows, maxNumberOfColumns)) {
        // cout << "out of bounds" << endl;
        continue;
      }
      if (boolGameBoard[X2][Y2] == true) {

        continue;
      }
      pair<int, int> newGuess2 = {X2, Y2};

      if (knownMines.find(newGuess2) != knownMines.end()) {
        // cout << "        added " << Y2 << " " << maxNumberOfRows - 1 - X2 <<
        // endl;
        sorrundingMineCount++;
      }
    }
  }

  return sorrundingMineCount;
}
