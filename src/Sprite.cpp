#include "Sprite.h"
#include "Texture.h"
#include <vector>
#include <iostream>
#include <windows.h>
using std::vector;

void Sprite::SetOrigin(int y,int x){
    origin.y = y;
    origin.x = x;
}

void Sprite::SetPosition(int y,int x){
    coords.y = y;
    coords.x = x;
}

void Sprite::SetTexture(int y,int x,int Height,int Width,Texture tex){
    texture = tex;
    rect.coordinates.y = y;
    rect.coordinates.x = x;
    rect.Width = Width;
    rect.Height = Height;
}

vector<CHAR_INFO> Sprite::Draw(){
    vector<CHAR_INFO> ch;
    int X = rect.coordinates.x;
    for(int i = 0; i < rect.Height;++i){
        for(int j = 0;j < rect.Width;++j){
            CHAR_INFO ci;
            int ind = rect.coordinates.x + rect.coordinates.y * texture.sizeX;
            ci.Char.UnicodeChar = texture.Field[ind].symbol;
            ci.Attributes = texture.Field[ind].textColor + (texture.Field[ind].bgColor << 4);
            ch.emplace_back(ci);
            rect.coordinates.x++;
            sprite_cords.push_back({rect.coordinates.y,rect.coordinates.x});
        }
        rect.coordinates.x=X;
        rect.coordinates.y++;
    }
    /*static COORD screenSize = {
        static_cast<SHORT>(rect.Width),
        static_cast<SHORT>(rect.Height)
    };
    static SMALL_RECT writeRegion = {
        coords.x + origin.x,
        coords.y + origin.y,
        //static_cast<SHORT>(texture.sizeX - 1),
        //static_cast<SHORT>(texture.sizeY - 1)
        static_cast<SHORT>(1000),
        static_cast<SHORT>(1000)
    };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleOutput(hConsole,&ch[0],screenSize,{0,0},&writeRegion);*/
    return ch;
}
