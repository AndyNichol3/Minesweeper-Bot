#ifndef BOT_MOVES_H
#define BOT_MOVES_H

#include "stdafx.h"

bool playFullBot(int maxNumberOfRows, int maxNumberOfColumns, int maxNumOfMines,
                 int &round, set<pair<int, int>> knownMines,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard);

bool playBotMovesMethod1(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumberOfColumns, int &round, int maxNumOfMines,
                         vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard);

bool playBotMovesMethod2(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumberOfColumns, int &round, int maxNumOfMines,
                         vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard);
set<pair<int, int>> botCheckForMines(set<pair<int, int>> knownMines,
                                     int maxNumberOfRows,
                                     int maxNumberOfColumns, int &round,
                                     int maxNumOfMines,
                                     vector<vector<bool>> &boolGameBoard,
                                     vector<vector<int>> &gameBoard);
tuple<int, int, int> mathWeightedGuess(set<pair<int, int>> knownMines,
                                       int maxNumberOfRows,
                                       int maxNumberOfColumns, int &round,
                                       int maxNumOfMines,
                                       vector<vector<bool>> &boolGameBoard,
                                       vector<vector<int>> &gameBoard);

#endif