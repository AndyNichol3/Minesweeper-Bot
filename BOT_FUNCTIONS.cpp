#include "BOT_FUNCTIONS.h"
#include "PLAY_GAME.h"
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

bool checkCorner(int i, int j, int maxNumberOfRows, int maxNumberOfColumns,
                 vector<vector<bool>> &boolGameBoard,
                 vector<vector<int>> &gameBoard) {
  bool checkVert = false;
  bool checkHor = false;

  // index the above and below squares
  for (int c = i - 1; c < i + 2; c += 2) {
    // if its revealed, checkVert = true
    if (c < 0 || c > maxNumberOfRows - 1) {
      continue;
    }
    if (boolGameBoard[c][j] == true && gameBoard[c][j] != 0) {
      checkVert = true;
      break;
    }
  }

  // index the left and right squares
  for (int r = j - 1; r < j + 2; r += 2) {
    if (r < 0 || r > maxNumberOfColumns - 1) {
      continue;
    }
    if (boolGameBoard[i][r] == true && gameBoard[i][r] != 0) {
      checkHor = true;
      break;
    }
  }

  // if its revealed, checkHor = true

  // if(check vert and hor == true){
  if (checkVert == true && checkHor == true) {
    return true;
  }
  // return true;
  // }

  return false;
}

int returnCornerLocation(vector<vector<bool>> &boolGameBoard,
                         vector<vector<int>> &gameBoard, int i, int j,
                         int maxNumberOfRows, int maxNumberOfColumns) {

  int cornerLocation = 0;
  //  1 |  | 2
  //    |ij|
  //  3 |  | 4

  if (boolGameBoard[i + 1][j] && boolGameBoard[i][j + 1]) {
    if (!boolGameBoard[i + 1][j + 1]) {
      return 4;
    }
  }
  if (boolGameBoard[i + 1][j] && boolGameBoard[i][j - 1]) {
    if (!boolGameBoard[i + 1][j - 1]) {
      return 3;
    }
  }

  if (boolGameBoard[i - 1][j] && boolGameBoard[i][j + 1]) {
    if (!boolGameBoard[i - 1][j + 1]) {
      return 2;
    }
  }
  if (boolGameBoard[i - 1][j] && boolGameBoard[i][j - 1]) {
    if (!boolGameBoard[i - 1][j - 1]) {
      return 1;
    }
  }

  return 0;
}
