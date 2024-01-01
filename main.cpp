// minesweeper

// g++ main.cpp PLAY_GAME.cpp BOT_FUNCTIONS.cpp
#include "BOT_FUNCTIONS.h"
#include "PLAY_GAME.h"
#include <iostream>
#include <queue>
#include <set>

#include <vector>

using namespace std;

pair<int,int> adjustIndex(int cornerLocation, pair<int,int> mineLocation);

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
  cout << "Bots flagged Point: " << endl;

  set<pair<int, int>> knownMines;
  //  knownMines.push({2, 3});
  //  knownMines.pop();

  // calculate all of the mines
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
              pair<int,int> mineLocation = {i,j};
              pair<int,int> temp = adjustIndex(cornerLocation, mineLocation); 
              if(knownMines.count(temp) == 0){
                knownMines.insert(temp); 
              }
             // knownMines.push({i, j});
            }
          }
        }
      }
    }
  }
  // adjust i and j
  int userRow = -2, userCol = -2;

  /*
  while (!knownMines.empty()) {

    auto mineLocation = knownMines.front();
    std::cout << "Mine at coordinates (" << mineLocation.second << ", "
              << maxNumberOfRows - 1 - mineLocation.first << ")\n";
    knownMines.pop();
  }
  */
  for (const auto& mineLocation : knownMines) {
      std::cout << "Mine at coordinates (" << mineLocation.second << ", "
                << maxNumberOfRows - 1 - mineLocation.first << ")\n";
  }
  
  // until games over
  // calculate squares to input
  // run through inputs until out

  while (gameOver == false) {

    round++;
    printRoundHeader(round);

    userRow = -2, userCol = -2;

    gameOver = playRoundUser(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                             gameBoard, maxNumOfMines, userRow, userCol);

    revealTally = printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows,
                                 maxNumberOfColumns);

    if (revealTally == (maxDisplay - maxNumOfMines)) {
      gameOver = true;
      win = true;
    }
  }
  // all bot code should exist here; the entire point should be to calculate
  // the inputs for row and columns

  // store a map of saved moves
  // while loop to mark them as flags

  // find the safe moves
  // while loop to reveal them

  // check if the game is over
  // if no, then repeat

  // end bot code

  // }

  // remove when implement back in
  // bool win = false;
  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}


pair<int,int> adjustIndex(int cornerLocation, pair<int,int> mineLocation){
  
  if (cornerLocation == 1) {
    mineLocation.first --; 
    mineLocation.second --;
  }
  else if (cornerLocation == 2) {
    mineLocation.first --;
    mineLocation.second ++; 
  }
  else if (cornerLocation == 3) {
    mineLocation.first ++;
    mineLocation.second --;
  }
  else if (cornerLocation == 4) {
    mineLocation.first ++;
    mineLocation.second ++;
  }
  
  return mineLocation;
  
}