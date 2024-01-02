#ifndef BOT_FUNCTIONS_H
#define BOT_FUNCTIONS_H

#include <set>
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
                  int userRow, int userCol);

bool playRoundUser(int maxNumberOfColumns, int maxNumberOfRows,
                   vector<vector<bool>> &boolGameBoard,
                   vector<vector<int>> &gameBoard, int maxNumOfMines,
                   int userRow, int userCol);

pair<int, int> adjustIndex(int cornerLocation, pair<int, int> mineLocation);
void initalizeBotGameBoard(vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard, int maxNumberOfRows,
                           int maxNumberOfColumns, int maxNumOfMines);
bool completeBotRound(int maxNumberOfColumns, int maxNumberOfRows,
                      vector<vector<bool>> &boolGameBoard,
                      vector<vector<int>> &gameBoard, int maxNumOfMines,
                      int userRow, int userCol, int round);
set<pair<int, int>>
calculateInitialKnownMines(int maxNumberOfColumns, int maxNumberOfRows,
                           vector<vector<bool>> &boolGameBoard,
                           vector<vector<int>> &gameBoard,
                           vector<vector<bool>> &boolFlagLocation);

void playBotMoves(set<pair<int, int>> knownMines, int maxNumberOfRows,
                  int maxNumberOfColumns, int round, int maxNumOfMines,
                  vector<vector<bool>> &boolGameBoard,
                  vector<vector<int>> &gameBoard,
                  vector<vector<bool>> &boolFlagLocation);

#endif