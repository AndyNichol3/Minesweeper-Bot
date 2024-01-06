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

pair<int, int> mathWeightedGuess(set<pair<int, int>> knownMines,
                                 int maxNumberOfRows, int maxNumberOfColumns,
                                 int round, int maxNumOfMines,
                                 vector<vector<bool>> &boolGameBoard,
                                 vector<vector<int>> &gameBoard) {
  // potential line of logic based on the number of mines needed to fufil a
  // square create a temp game board, given a revealed tile, if gameBoard -
  // number of sorruinging mines == 0; continue is not, add the absolute value
  // of difference to all of the sorrunding unrevealed tiles. store the highest
  // index and pair this index is most likely a mine, store known mines, restart
  // calcualting loop

  // weight, x, y
  tuple<int, int, int> storageTuple = {-1, -1, -1};

  for (int i = 0; i < maxNumberOfRows; ++i) {
    for (int j = 0; j < maxNumberOfColumns; ++j) {

      if (boolGameBoard[i][j] == true) {
        continue;
      }

      pair<int,int> tempPair = {i,j};
      if(knownMines.find(tempPair) != knownMines.end()){
        continue; 
      }
      // given an unrevealed tile,
      // for all of the tiles around it,
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
          // Continue the loop if newGuess is in knownMines
          if (knownMines.find(newGuess) != knownMines.end()) {
            continue;
          }
          // calculate the difference between tile int and the known mines
          // around it add the difference to the sum total for the unrevealed
          // tile
          int sorrundingMineCount = 0;
          for (int m = -1; m < 2; ++m) {
            for (int n = -1; n < 2; ++n) {
              if (m == 0 && n == 0) {
                continue;
              }
              int X2 = i + m;
              int Y2 = j + n;

              if (checkOutOfBounds(X2, Y2, maxNumberOfRows,
                                   maxNumberOfColumns)) {
                continue;
              }
              if (boolGameBoard[X2][Y2] == true) {
                continue;
              }
              pair<int, int> newGuess2 = {X2, Y2};
              if (knownMines.find(newGuess2) != knownMines.end()) {
                sorrundingMineCount++;
              }
            }
          }

          int difference = abs(sorrundingMineCount - gameBoard[i][j]);
          sumOfDifferences += difference;
          // if the sum total is higher the current highest
          // store the sum and pair of the unrevealed tile
          // loop

          // if known mine
          // cont
          // if out of bound
          // cont
          // if unrevealed
          // skip
          // if revealed
          // calculate the difference between tile int and the known mines
          // around it add the difference to the sum total for the unrevealed
          // tile

          // if the sum total is higher the current highest
          // store the sum and pair of the unrevealed tile
          // loop
        }
      }

      if (sumOfDifferences > get<0>(storageTuple)) {
        storageTuple = {sumOfDifferences, i, j};
      }
    }
  }

  return {get<1>(storageTuple), get<2>(storageTuple)};
}

// return highest pair

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
