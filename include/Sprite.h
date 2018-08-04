#ifndef SPRITE_H
#define SPRITE_H
#include <vector>
#include "Points.h"
#include <windows.h>
#include "Texture.h"
using std::vector;

struct rectangle{
    Points coordinates;
    int Width;
    int Height;
};

class Sprite
{
    public:
        vector<Points> sprite_cords;
        rectangle rect;
        void SetOrigin(int y,int x);
        void SetPosition(int y,int x);
        void SetTexture(int y,int x,int Height,int Width,Texture tex);
        vector<CHAR_INFO> Draw();
    private:
        Points origin;
        Points coords;
        Texture texture;
};

#endif // SPRITE_H
