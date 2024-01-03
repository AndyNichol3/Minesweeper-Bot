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
      displaySubtract = 0, round = 1;

  printGameWelcome();

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

  bool gameOver = false, win = false;
  int revealTally = 0, maxDisplay = maxNumberOfRows * maxNumberOfColumns,
      userRow = -2, userCol = -2;
  set<pair<int, int>> knownMines;

  cout << "Bots flagged Point: " << endl;

  

  for (int i = 0; i <= 15; i++) {
    int confirmedMineTally = 0;

    knownMines = botCheckForMines(knownMines, maxNumberOfRows,
                                  maxNumberOfColumns, round, maxNumOfMines,
                                  boolGameBoard, gameBoard, boolFlagLocation);
    
    confirmedMineTally = printBotFlaggedMines(knownMines, maxNumberOfRows); 
    
    if (confirmedMineTally == maxNumOfMines) {
      cout << endl << "All Mines Found" << endl;
      win = foundAllMines(knownMines, maxNumberOfRows, maxNumberOfColumns,
                          round, maxNumOfMines, boolGameBoard, gameBoard,
                          boolFlagLocation);
      break;
    }
    if(confirmedMineTally == 0){
      cout << endl << "No Mines Found" << endl;
      // eventally, add function to make a random guess
      break;
    }

    cout << endl << "METHOD 1" << endl;

   bool changesMadeMethod1 = playBotMoves(knownMines, maxNumberOfRows, maxNumberOfColumns, round,
                 maxNumOfMines, boolGameBoard, gameBoard, boolFlagLocation);

    cout << endl << "METHOD 2" << endl;
    playBotMovesMethod2(knownMines, maxNumberOfRows, maxNumberOfColumns, round,
                        maxNumOfMines, boolGameBoard, gameBoard,
                        boolFlagLocation);
  }

  
  
  if (win == false) {
    win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                   gameBoard, maxNumOfMines, round);
  }

  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}

