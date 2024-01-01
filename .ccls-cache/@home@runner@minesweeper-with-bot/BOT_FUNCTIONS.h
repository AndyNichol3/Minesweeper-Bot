#ifndef BOT_FUNCTIONS_H
#define BOT_FUNCTIONS_H

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
vector<vector<int>> &gameBoard, int maxNumOfMines, int userRow, int userCol); 

bool playRoundUser(int maxNumberOfColumns, int maxNumberOfRows,
vector<vector<bool>> &boolGameBoard,
vector<vector<int>> &gameBoard, int maxNumOfMines, int userRow, int userCol); 


#endif