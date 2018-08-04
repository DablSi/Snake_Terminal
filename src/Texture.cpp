#include "Texture.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <windows.h>
using std::string;
using std::stringstream;
using std::vector;

Texture::Texture()
{
    sizeY = 4;
    sizeX = 3;
    std::ifstream texture("Texture.txt");
    string line = "";
    while(getline(texture,line)){
        stringstream pixel;
        pixel<<line;
        char symbol;
        pixel>>symbol;
        pixel.ignore(1);
        int textColor = 0;
        pixel>>textColor;
        int bgColor = 0;
        pixel>>bgColor;
        TextureData data = {symbol,textColor,bgColor};
        Field.push_back(data);
    }
}

void Texture::print(){
    const int sY = sizeY,sX = sizeX;
    vector<CHAR_INFO> ch;
    for(int i = 0; i < Field.size();++i){
        CHAR_INFO ci;
        ci.Char.UnicodeChar = Field[i].symbol;
        ci.Attributes = Field[i].textColor + (Field[i].bgColor << 4);
        ch.emplace_back(ci);
    }
    /*static COORD screenSize = {
        static_cast<SHORT>(sX),
        static_cast<SHORT>(sY)
    };
    static SMALL_RECT writeRegion = {
        10,
        10,
        static_cast<SHORT>(100),
        static_cast<SHORT>(100)
    };*/
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //std::cout<<"\n\n\n";
    //WriteConsoleOutput(hConsole,&ch[0],screenSize,{0,0},&writeRegion);
}
