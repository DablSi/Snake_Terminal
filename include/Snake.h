#ifndef SNAKE_H
#define SNAKE_H
#include <windows.h>
#include <queue>
#include "Points.h"

class Snake
{
    public:
        static constexpr int sY=50,sX=60;
        int length = 0;
        bool lose = false;
        CHAR_INFO field[sY][sX];
        Snake();
        void getKey();
    private:
        std::queue<char> moves;
        //std::queue<Points> sprite_queue;
    	char key = 'w';
};

#endif // SNAKE_H
