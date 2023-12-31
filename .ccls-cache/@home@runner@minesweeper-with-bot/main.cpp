// minesweeper

// g++ main.cpp PLAY_GAME.cpp
#include "PLAY_GAME.h"
#include <vector>
#include <iostream>

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
  vector<vector<bool>> boolFlagLocation(maxNumberOfRows,
                                        vector<bool>(maxNumberOfColumns, false));
  

  // handles all of the creation, and the round 1 of them game
  // since the game cannot be lost on round one and the variables
  // are not reused anywhere else
  
 // initalizeGameBoard(boolGameBoard, gameBoard, maxNumberOfRows,
        //             maxNumberOfColumns, maxNumOfMines);
//{
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);
  printRoundHeader(1);

  //cout << "Enter Starting Point (-1 to exit): " << endl;
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
  bool win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                      gameBoard, maxNumOfMines);

  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}
