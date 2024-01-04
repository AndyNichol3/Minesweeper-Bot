// minesweeper

// g++ main.cpp PLAY_GAME.cpp BOT_FUNCTIONS.cpp
#include "BOT_FUNCTIONS.h"
#include "PLAY_GAME.h"
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int guessCorners(int maxNumberOfRows, int maxNumberOfColumns,
                  vector<vector<bool>> &boolGameBoard,
                  vector<vector<int>> &gameBoard, int maxNumOfMines, int round,
                  set<pair<int, int>> knownMines, vector<vector<bool>> &boolFlagLocation);

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
                        maxNumberOfColumns, maxNumOfMines, boolFlagLocation);

  bool gameOver = false, win = false;
  int revealTally = 0, maxDisplay = maxNumberOfRows * maxNumberOfColumns,
      userRow = -2, userCol = -2;
  set<pair<int, int>> knownMines;

  cout << "Bots flagged Point: " << endl;

  bool continueGame = true;
  int catchInfinateLoop = 0;
  while (continueGame) {
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
      continueGame = false;
      break;
    }
    if (confirmedMineTally == 0) {
      cout << endl << "No Mines Found" << endl;
      // continueGame = false;
      //  eventally, add function to make a random guess
      // break;
    }

    cout << endl << "METHOD 1" << endl;

    bool changesMadeMethod1 = playBotMovesMethod1(
        knownMines, maxNumberOfRows, maxNumberOfColumns, round, maxNumOfMines,
        boolGameBoard, gameBoard, boolFlagLocation);

    cout << endl << "METHOD 2" << endl;
    bool changesMadeMethod2 = playBotMovesMethod2(
        knownMines, maxNumberOfRows, maxNumberOfColumns, round, maxNumOfMines,
        boolGameBoard, gameBoard, boolFlagLocation);

    if (changesMadeMethod1 == false && changesMadeMethod2 == false) {
      cout << endl << "No Further Moves" << endl;
      cout << "Initalize the first guess" << endl;
      if (catchInfinateLoop >= 4) {
        cout << "Infinate Loop" << endl;
        break;
      }
      // pair<int,int> guessMine = mathWeightedGuess();
      int error = guessCorners(maxNumberOfRows, maxNumberOfColumns, boolGameBoard,
                   gameBoard, maxNumOfMines, round, knownMines, boolFlagLocation);
      if (error == 1) {
        break; 
      }
      catchInfinateLoop++;

      // continueGame = false;
      // break;
    }
  }

  if (win == false) {
    win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                   gameBoard, maxNumOfMines, round, boolFlagLocation);
  }

  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}

int guessCorners(int maxNumberOfRows, int maxNumberOfColumns,
                  vector<vector<bool>> &boolGameBoard,
                  vector<vector<int>> &gameBoard, int maxNumOfMines, int round,
                  set<pair<int, int>> knownMines, vector<vector<bool>> &boolFlagLocation) {
  pair<int, int> newGuess;
  newGuess = {0, 0};
  // aroundMine.find(check) != aroundMine.end()
  if (knownMines.find(newGuess) == knownMines.end()) {
    if (boolGameBoard[0][0] == false) {
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, 0, 0, round, boolFlagLocation);
      return 0;
    }
  }
  newGuess = {0, maxNumberOfColumns - 1};
  if (knownMines.find(newGuess) == knownMines.end()) {

    if (boolGameBoard[0][maxNumberOfColumns - 1] == false) {
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, 0, maxNumberOfColumns - 1,
                       round, boolFlagLocation);
      return 0;
    }
  }
  newGuess = {maxNumberOfRows - 1, 0};
  if (knownMines.find(newGuess) == knownMines.end()) {
    if (boolGameBoard[maxNumberOfRows - 1][0] == false) {
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, maxNumberOfRows - 1, 0, round, boolFlagLocation);
      return 0;
    }
  }
  newGuess = {maxNumberOfRows - 1, maxNumberOfColumns - 1};
  if (knownMines.find(newGuess) == knownMines.end()) {
    if (boolGameBoard[maxNumberOfRows - 1][maxNumberOfColumns - 1] == false) {
      completeBotRound(maxNumberOfColumns, maxNumberOfRows, boolGameBoard,
                       gameBoard, maxNumOfMines, maxNumberOfRows - 1,
                       maxNumberOfColumns - 1, round, boolFlagLocation);
      return 0;
    }
  }
  cout << "No corners found" << endl;
  return 1;
}
// pair<int,int> mathWeightedGuess(){}
