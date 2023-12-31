// minesweeper

// g++ main.cpp PLAY_GAME.cpp
#include "PLAY_GAME.h"
#include <iostream>
#include <vector>

using namespace std;

bool checkCorner(int i, int j, int maxNumberOfRows, int maxNumberOfColumns,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard);
int returnCornerLocation(vector<vector<bool>> &boolGameBoard,
 vector<vector<int>> &gameBoard, int i, int j, int maxNumberOfRows, int maxNumberOfColumns);

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

  // handles all of the creation, and the round 1 of them game
  // since the game cannot be lost on round one and the variables
  // are not reused anywhere else

  // initalizeGameBoard(boolGameBoard, gameBoard, maxNumberOfRows,
  //             maxNumberOfColumns, maxNumOfMines);
  //{
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);
  printRoundHeader(1);

  // cout << "Enter Starting Point (-1 to exit): " << endl;
  cout << "the bot will now start" << endl;
  srand(time(NULL));
  int userStartCol = rand() % (maxNumberOfColumns - 1);
  cout << "bot chose X: " << userStartCol << endl;
  int userStartRow = rand() % (maxNumberOfRows - 1);
  cout << "bot chose Y: " << userStartRow << endl;

  cout << endl;

  boolGameBoard[userStartRow][userStartCol] = true;

  fillWithMines(gameBoard, userStartRow, userStartCol, maxNumOfMines,
                maxNumberOfRows, maxNumberOfColumns);
  fillWithInts(gameBoard, maxNumberOfRows, maxNumberOfColumns);
  recursiveRevealExplosion(gameBoard, boolGameBoard, userStartRow, userStartCol,
                           maxNumberOfRows, maxNumberOfColumns);
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);
  // }

  // bool win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
  //         gameBoard, maxNumOfMines);

  //{
  bool gameOver = false, win = false;
  // int round = 1;
  int revealTally = 0;
  int maxDisplay = maxNumberOfRows * maxNumberOfColumns;
  while (gameOver == false) {

    round++;

    printRoundHeader(round);

    bool revealedTile = false;
    int userRow = -2, userCol = -2;

    while (!revealedTile) {

      // all bot code should exist here; the entire point should be to calculate
      // the inputs for row and columns
      cout << "Bots flagged Point: " << endl;

      // calculate all of the mines
      for (int i = 0; i < maxNumberOfRows; i++) {
        for (int j = 0; j < maxNumberOfColumns; j++) {
          if (gameBoard[i][j] != 0) {
            if (boolGameBoard[i][j] == true) {
              bool isCorner =
                  checkCorner(i, j, maxNumberOfRows, maxNumberOfColumns,
                              boolGameBoard, gameBoard);
              // cout << endl << "corner found" << endl;
              if (isCorner == true && gameBoard[i][j] == 1) {
                cout << "Corner: " << j << ", " << maxNumberOfRows - 1 - i << endl;
                int cornerLocation = returnCornerLocation(boolGameBoard, gameBoard, i, j, maxNumberOfRows, maxNumberOfColumns); 
                cout << "location = " << cornerLocation << endl;
              }
            }
          }
        }
      }

      cout << "Enter Next Point (-1 to exit): " << endl;

      userCol = getInputX(maxNumberOfColumns);
      userRow = getInputY(maxNumberOfRows);

      // while loop to mark them as flags

      // find the safe moves
      // while loop to reveal them

      // check if the game is over
      // if no, then repeat

      // end bot code
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

    revealTally = printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows,
                                 maxNumberOfColumns);

    if (revealTally == (maxDisplay - maxNumOfMines)) {
      gameOver = true;
      win = true;
    }

    // }

    // remove when implement back in
    // bool win = false;
    if (win == true) {
      printWin();

    } else {
      printLose();
    }
  }
}

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

int returnCornerLocation(vector<vector<bool>> &boolGameBoard, vector<vector<int>> &gameBoard,
                          int i, int j, int maxNumberOfRows, int maxNumberOfColumns){

  int cornerLocation = 0;
  //  1 |  | 2
  //    |ij|
  //  3 |  | 4

  if(boolGameBoard[i+1][j] && boolGameBoard[i][j+1]){
    if(!boolGameBoard[i+1][j+1]){
    return 4;
    }
  }
  if(boolGameBoard[i+1][j] && boolGameBoard[i][j-1])
  {
    if(!boolGameBoard[i+1][j-1]){
    return 3;
    }
  }

  if(boolGameBoard[i-1][j] && boolGameBoard[i][j+1])
  {
    if(!boolGameBoard[i-1][j+1]){
    return 2;
    }
  }
  if(boolGameBoard[i-1][j] && boolGameBoard[i][j-1]){
    if(!boolGameBoard[i-1][j-1]){
    return 1;
    }
  }
  
  return 0; 
}
