#ifndef BOT_FUNCTIONS_H
#define BOT_FUNCTIONS_H

#include "stdafx.h"

bool checkCorner(int i, int j, int maxNumberOfRows, int maxNumberOfColumns,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard);
int returnCornerLocation(vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard, int i, int j,
                         int maxNumberOfRows, int maxNumberOfColumns);
bool playRoundBot(int maxNumberOfColumns, int maxNumberOfRows,
                  vector<vector<bool>> &boolGameBoard,
                  vector<vector<int>> &gameBoard, int maxNumOfMines,
                  int userRow, int userCol, int &round,

                  set<pair<int, int>> knownMines);

bool playRoundUser(int maxNumberOfColumns, int maxNumberOfRows,
                   vector<vector<bool>> &boolGameBoard,
                   vector<vector<int>> &gameBoard, int maxNumOfMines,
                   int userRow, int userCol);

pair<int, int> adjustIndex(int cornerLocation, pair<int, int> mineLocation);
void initalizeBotGameBoard(vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard, int maxNumberOfRows,
                           int maxNumberOfColumns, int maxNumOfMines,
                           int &round, set<pair<int, int>> knownMines);
bool completeBotRound(int maxNumberOfColumns, int maxNumberOfRows,
                      vector<vector<bool>> &boolGameBoard,
                      vector<vector<int>> &gameBoard, int maxNumOfMines,
                      int userRow, int userCol, int &round,

                      set<pair<int, int>> knownMines);
set<pair<int, int>>
calculateInitialKnownMines(int maxNumberOfColumns, int maxNumberOfRows,
                           vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard);

bool foundAllMines(set<pair<int, int>> knownMines, int maxNumberOfRows,
                   int maxNumberOfColumns, int &round, int maxNumOfMines,
                   vector<vector<bool>> &boolGameBoard,
                   vector<vector<int>> &gameBoard);

int printBotFlaggedMines(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumOfMines);
void triggeredAMine(int maxNumberOfRows, int maxNumberOfColumns,
                    vector<vector<bool>> &boolGameBoard,
                    vector<vector<int>> &gameBoard, int maxNumOfMines,
                    int &round, set<pair<int, int>> knownMines);
int guessCorners(int maxNumberOfRows, int maxNumberOfColumns,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard, int maxNumOfMines, int &round,
                 set<pair<int, int>> knownMines);
tuple<int, int, int> gameStart();

bool checkOutOfBounds(int row, int col, int maxNumberOfRows,
                      int maxNumberOfColumns);

int returnSorrundingMineCount(int X, int Y, int maxNumberOfRows,
                              int maxNumberOfColumns,
                              vector<vector<bool>> &boolGameBoard,
                              vector<vector<int>> &gameBoard,
                              set<pair<int, int>> knownMines);

#endif