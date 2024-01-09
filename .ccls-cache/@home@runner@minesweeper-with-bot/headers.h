#ifndef HEADERS_H
#define HEADERS_H

//g++ -x c++-header headers.h -o headers.pch

#include "BOT_FUNCTIONS.h"
#include "BOT_MOVES.h"
#include "PLAY_GAME.h"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <tuple>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

// custom color codes
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\e[0;36m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"
#define FLAG "\U0001f4cd"

#endif