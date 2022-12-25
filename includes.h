#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#include <random>

// *************************WINDOWS-API************************* //
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
enum Keys { UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80, ENTER = 13, ESC = 27, SPACE = 32, R = 114 };
enum Color
{
    BLACK, BLUE, GREEN, CYAN, RED,
    MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
    LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

void setColor(Color text, Color background)
{
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void setCursor(short x, short y)
{
    COORD myCoords = { x, y };//инициализируем передаваемыми значениями объект координат
    SetConsoleCursorPosition(hStdOut, myCoords);
}
// *************************WINDOWS-API************************* //

#include "Ship.h"
#include "Field.h"

#endif
