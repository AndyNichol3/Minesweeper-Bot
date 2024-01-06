#ifndef BOT_MOVES_H
#define BOT_MOVES_H

#include <set>
#include <vector>
using namespace std;

bool playBotMovesMethod1(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumberOfColumns, int round, int maxNumOfMines,
                         vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard,
                         vector<vector<bool>> &boolFlagLocation);

bool playBotMovesMethod2(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumberOfColumns, int round, int maxNumOfMines,
                         vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard,
                         vector<vector<bool>> &boolFlagLocation);
set<pair<int, int>> botCheckForMines(
    set<pair<int, int>> knownMines, int maxNumberOfRows, int maxNumberOfColumns,
    int round, int maxNumOfMines, vector<vector<bool>> &boolGameBoard,
    vector<vector<int>> &gameBoard, vector<vector<bool>> &boolFlagLocation);
pair<int, int> mathWeightedGuess(set<pair<int, int>> knownMines,
                                 int maxNumberOfRows, int maxNumberOfColumns,
                                 int round, int maxNumOfMines,
                                 vector<vector<bool>> &boolGameBoard,
                                 vector<vector<int>> &gameBoard);

bool playBotMovesMethod1andahalf(set<pair<int, int>> knownMines,
                                 int maxNumberOfRows, int maxNumberOfColumns,
                                 int round, int maxNumOfMines,
                                 vector<vector<bool>> &boolGameBoard,
                                 vector<vector<int>> &gameBoard,
                                 vector<vector<bool>> &boolFlagLocation);

#endif