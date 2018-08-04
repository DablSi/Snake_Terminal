#ifndef CONSOLE_H
#define CONSOLE_H
#include "Snake.h"


class Console
{
    public:
        Console();
        void print(Snake snake);
        void consoleSize(int y, int x);
        void sqrSymbols();
};

#endif // CONSOLE_H
