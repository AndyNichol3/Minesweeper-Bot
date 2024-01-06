// minesweeper

// g++ main.cpp PLAY_GAME.cpp BOT_FUNCTIONS.cpp BOT_MOVES.cpp
#include "BOT_FUNCTIONS.h"
#include "BOT_MOVES.h"
#include "PLAY_GAME.h"

#include <chrono>
#include <iostream>
#include <set>
#include <thread>
#include <tuple>
#include <vector>

using namespace std;

int main() {
  // define variable
  int round = 1;

  // <maxRows, maxColums, MaXNumOfMines>
  tuple<int, int, int> gameStartTuple = gameStart();

  int maxNumberOfRows = get<0>(gameStartTuple),
      maxNumberOfColumns = get<1>(gameStartTuple),
      maxNumOfMines = get<2>(gameStartTuple);

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

  // cout << "Bots flagged Point: " << endl;

  bool continueGame = true;
  // int catchInfinateLoop = 0;
  int totalGuessTally = 0;
  while (continueGame) {
    int confirmedMineTally = 0;

    knownMines = botCheckForMines(knownMines, maxNumberOfRows,
                                  maxNumberOfColumns, round, maxNumOfMines,
                                  boolGameBoard, gameBoard, boolFlagLocation);

    confirmedMineTally =
        printBotFlaggedMines(knownMines, maxNumberOfRows, maxNumOfMines);

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

    bool changesMadeMethod2 = playBotMovesMethod2(
        knownMines, maxNumberOfRows, maxNumberOfColumns, round, maxNumOfMines,
        boolGameBoard, gameBoard, boolFlagLocation);

    bool changesMadeMethod1 = playBotMovesMethod1(
        knownMines, maxNumberOfRows, maxNumberOfColumns, round, maxNumOfMines,
        boolGameBoard, gameBoard, boolFlagLocation);

    if (!changesMadeMethod1 && !changesMadeMethod2) {
      cout << endl << "No Further Moves" << endl;
      cout << "Initalize the first guess" << endl;
      // if(catach inf loop >= 4)

      int returnedError = guessCorners(maxNumberOfRows, maxNumberOfColumns,
                                       boolGameBoard, gameBoard, maxNumOfMines,
                                       round, knownMines, boolFlagLocation);
      if (returnedError != 1) {
        continue;
      }

      if (totalGuessTally == 2) {
        break;
      }

      cout << endl << "doing the first real guess" << endl;
      // sleep function so if this decides to infinate loop it doesnt overflow
      // my terminal
      this_thread::sleep_for(chrono::milliseconds(3000));

      // try to add another
      // prompt user to ask if it wants to make one guess or let the bot guess
      // (warning: chance of failure)
      pair<int, int> bestGuess =
          mathWeightedGuess(knownMines, maxNumberOfRows, maxNumberOfColumns,
                            round, maxNumOfMines, boolGameBoard, gameBoard);
      if (bestGuess.first == -1) {
        cout << "Entered Flag" << endl;
        break;
      }
      cout << "Best Guess: " << bestGuess.second << " " <<  maxNumberOfRows - 1 - bestGuess.first << endl; 
      knownMines.insert(bestGuess);
      confirmedMineTally =
          printBotFlaggedMines(knownMines, maxNumberOfRows, maxNumOfMines);
      
      totalGuessTally++;

      continue;
    }
  }

  // potentially line of logic here, if the bot has no more moves, which ever
  // tile has the highest total of mines around it, it will assume that tile
  // is a mine. run a potential program. may only work with very few tiles
  // left to be revealed.

  // new line of logic, its less likely that a given x or y value will
  // generate in a line so if you need to guess,

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
