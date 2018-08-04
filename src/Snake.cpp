#include "Snake.h"
#include "Texture.h"
#include "Sprite.h"
#include "Points.h"
#include <queue>
#include <string>
#include <ctime>
#include <vector>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
using std::queue;
using std::string;
using std::vector;

int btw = 2;

static Points food,tail, head;

Snake::Snake()
{
    for(int i = 0;i<sY;++i){
        for(int j = 0;j<sX;++j){
            field[i][j].Char.UnicodeChar = ' ';
            field[i][j].Attributes = 0x00020;
        }
    }
    /*for(int i = 0;i<sY;++i)
        field[i][0].Char.UnicodeChar = '|',
        field[i][sX-1].Char.UnicodeChar = '|';*/
    for(int i = 0;i<sX;++i)
        field[0][i].Char.UnicodeChar = '-',
        field[sY-1][i].Char.UnicodeChar = '-';
    /*for(int i = 0;i<sY;++i){
        for(int j = 0;j<sX;++j){
            field[i][j].Char.UnicodeChar = ((i == 0 || i == (sY-1)) &&
                         (j == 0 || j == (sX-1)) ?
                         '+' : field[i][j].Char.UnicodeChar);
        }
    }*/
    field[sY/2 + btw][sX/2 + btw].Char.UnicodeChar = '*';
    food.y = sY/2 + btw;
    food.x = sX/2 + btw;
    head = {sY/2,sX/2};
    //head.push_back({sY/2,sX/2+1});
    tail = {sY/2,sX/2};
    //tail.push_back({sY/2,sX/2+1});
}

/*void Snake::print()
{
    system("cls");
        sprite.Draw();
    string out = "";
    for(int i = 0;i<sY;++i){
        for(int j = 0;j<sX;++j){
            out += field[i][j];
        }
        out+="\nmoves";
    }
    std::cout<<out;
}*/

void Snake::getKey()
{
    Texture tex;
    Sprite spr;
    spr.SetOrigin(0,0);
    spr.SetTexture(0,0,btw,btw,tex);
    vector<CHAR_INFO> ch = spr.Draw();
    if(length < 3)
        Sleep(50*btw);
    else
        Sleep(length * 10 * btw);
    if(kbhit())
    {
        switch(getch())
        {
            case 'w':
                key = 'w';
                break;
            case 'a':
                key = 'a';
                break;
            case 's':
                key = 's';
                break;
            case 'd':
                key = 'd';
                break;
            default:
                break;
        }
    }
    switch(key)
    {
        case 'w':
            head.y-=btw;
            break;
        case 'a':
            head.x-=btw;
            break;
        case 's':
            head.y+=btw;
            break;
        case 'd':
            head.x+=btw;
            break;
        default:
            break;
    }
    moves.push(key);
    bool ate = 0;
    if(field[food.y][food.x].Char.UnicodeChar != '*' && !ate){
        srand(time(NULL));
        food.y = 2 + (rand() % 19);
        food.x = 1 + (rand() % 39);
        while(field[food.y][food.x].Char.UnicodeChar != ' '){
            food.y = 2 + (rand() % 19);
            food.x = 1 + (rand() % 39);
        }
        ++length;
        field[food.y][food.x].Char.UnicodeChar = '*';
        ate = 1;
    }
    if(!ate){
        if(field[head.y][head.x].Char.UnicodeChar == ' ' ||
           field[head.y][head.x].Char.UnicodeChar == '*' ||
           (key == 'd' && field[head.y][head.x].Char.UnicodeChar != '-')){
            for(int i = 0;i<spr.sprite_cords.size();++i){
                field[spr.sprite_cords[i].y + tail.y][spr.sprite_cords[i].x + tail.x].Char.UnicodeChar = ' ';
                field[spr.sprite_cords[i].y + tail.y][spr.sprite_cords[i].x + tail.x].Attributes = 0x00020;
            }
            switch(moves.front()){
                case 'w':
                    tail.y-=btw;
                    break;
                case 's':
                    tail.y+=btw;
                    break;
                case 'a':
                    tail.x-=btw;
                    break;
                case 'd':
                    tail.x+=btw;
                    break;
                default:
                    break;
            }
            moves.pop();
        }
        else{
            lose = true;
        }
    }
    for(int i = 0;i<sY;++i){
        for(int j = 0;j<sX;++j){
            if(field[i][j].Char.UnicodeChar == ' ')
                field[i][j].Attributes = 0x00020;
        }
    }
    for(int i = 0;i<spr.sprite_cords.size();++i){
        field[spr.sprite_cords[i].y + head.y][spr.sprite_cords[i].x + head.x].Char.UnicodeChar = ch[i].Char.UnicodeChar;
        field[spr.sprite_cords[i].y + head.y][spr.sprite_cords[i].x + head.x].Attributes = ch[i].Attributes;
    }
}

