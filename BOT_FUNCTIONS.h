#ifndef BOT_FUNCTIONS_H
#define BOT_FUNCTIONS_H

#include <set>
#include <tuple>
#include <vector>

using namespace std;

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
                  vector<vector<bool>> &boolFlagLocation);

bool playRoundUser(int maxNumberOfColumns, int maxNumberOfRows,
                   vector<vector<bool>> &boolGameBoard,
                   vector<vector<int>> &gameBoard, int maxNumOfMines,
                   int userRow, int userCol);

pair<int, int> adjustIndex(int cornerLocation, pair<int, int> mineLocation);
void initalizeBotGameBoard(vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard, int maxNumberOfRows,
                           int maxNumberOfColumns, int maxNumOfMines,
                           vector<vector<bool>> &boolFlagLocation, int &round);
bool completeBotRound(int maxNumberOfColumns, int maxNumberOfRows,
                      vector<vector<bool>> &boolGameBoard,
                      vector<vector<int>> &gameBoard, int maxNumOfMines,
                      int userRow, int userCol, int &round,
                      vector<vector<bool>> &boolFlagLocation);
set<pair<int, int>>
calculateInitialKnownMines(int maxNumberOfColumns, int maxNumberOfRows,
                           vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard,
                           vector<vector<bool>> &boolFlagLocation);

bool foundAllMines(set<pair<int, int>> knownMines, int maxNumberOfRows,
                   int maxNumberOfColumns, int &round, int maxNumOfMines,
                   vector<vector<bool>> &boolGameBoard,
                   vector<vector<int>> &gameBoard,
                   vector<vector<bool>> &boolFlagLocation);

int printBotFlaggedMines(set<pair<int, int>> knownMines, int maxNumberOfRows,
                         int maxNumOfMines);
void triggeredAMine(int maxNumberOfRows, int maxNumberOfColumns,
                    vector<vector<bool>> &boolGameBoard,
                    vector<vector<int>> &gameBoard, int maxNumOfMines,
                    int &round, vector<vector<bool>> &boolFlagLocation);
int guessCorners(int maxNumberOfRows, int maxNumberOfColumns,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard, int maxNumOfMines, int &round,
                 set<pair<int, int>> knownMines,
                 vector<vector<bool>> &boolFlagLocation);
tuple<int, int, int> gameStart();

bool checkOutOfBounds(int row, int col, int maxNumberOfRows,
                      int maxNumberOfColumns);

int returnSorrundingMineCount(int X, int Y, int maxNumberOfRows,
                              int maxNumberOfColumns,
                              vector<vector<bool>> &boolGameBoard,
                              vector<vector<int>> &gameBoard,
                              set<pair<int, int>> knownMines);

#endif