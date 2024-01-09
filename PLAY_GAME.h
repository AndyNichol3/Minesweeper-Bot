#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#include <set>
#include <vector>

using namespace std;

// play game functions
bool playGame(int maxNumberOfColumns, int maxNumberOfRows,
              std::vector<std::vector<bool>> &boolGameBoard,
              std::vector<std::vector<int>> &gameBoard, int maxNumOfMines,
              int &round, set<pair<int, int>> knownMines);

void recursiveRevealExplosion(std::vector<std::vector<int>> &gameBoard,
                              std::vector<std::vector<bool>> &boolGameBoard,
                              int X, int Y, int maxNumberOfRows,
                              int maxNumberOfColumns);

// setup and initialization functions
void initalizeGameBoard(std::vector<std::vector<bool>> &boolGameBoard,
                        std::vector<std::vector<int>> &gameBoard,
                        int maxNumberOfRows, int maxNumberOfColumns,
                        int maxNumOfMines, set<pair<int, int>> knownMines);
void fillWithMines(std::vector<std::vector<int>> &gameBoard, int userStartRow,
                   int userStartCol, int maxNumOfMines, int maxNumberOfRows,
                   int maxNumberOfColumns);
void fillWithInts(std::vector<std::vector<int>> &gameBoard, int maxNumberOfRows,
                  int maxNumberOfColumns);
void calcGameBoardInts(std::vector<std::vector<int>> &gameBoard, int x, int y,
                       int maxNumberOfRows, int maxNumberOfColumns);

// obtain user input functions
int getInputX(int maxNumberOfColumns);
int getInputY(int maxNumberOfRows);
int getUserDifficulty();

// print and header functions
void printRoundHeader(int &round);
void printGameRules();
void printGameWelcome();
void printWin();
void printLose();
int printBoolBoard(const std::vector<std::vector<bool>> &boolGameBoard,
                   const std::vector<std::vector<int>> &gameBoard,
                   int maxNumberOfRows, int maxNumberOfColumns,
                   set<pair<int, int>> knownMines);
void endOfGameHeader(bool win); 

#endif