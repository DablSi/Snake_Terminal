#include "Console.h"
#include "Texture.h"
#include "Points.h"
#include "Sprite.h"
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template<typename pfn_t>
    inline bool LoadFunc(HMODULE hmod,const char* name, pfn_t &fn){
        fn = (pfn_t)GetProcAddress(hmod,name);
        return fn != 0;
    }

    typedef struct _CONSOLE_FONT_INFOEX{
        ULONG cbSize;
        DWORD nFont;
        COORD dwFontSize;
        UINT FontFamily;
        UINT FontWeight;
        WCHAR FaceName[LF_FACESIZE];
    } CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

    BOOL(WINAPI *SetCurrentConsoleFontEx)(HANDLE hConsoleOutput,BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
    //для работы винапи(Да,это - костыцли, но компилятор код блокс по-друггому не хочет)

Console::Console()
{
    //SetConsoleTextAttribute(hConsole,(WORD) ((2<<4) | 14));
    //меняет фон на светлозеленый и шрифт на светложелтый
    SetConsoleTitleA("Snake");
    //меняет название программы
}

void Console::consoleSize(int y, int x){
    COORD crd = {y,x};
    SMALL_RECT src = {0,0,crd.X-1,crd.Y-1};
    SetConsoleScreenBufferSize(hConsole,crd);
    SetConsoleWindowInfo(hConsole,true,&src);
    //меняет размер окна
}

void Console::sqrSymbols(){
    if(LoadFunc(GetModuleHandle("kernel32.dll"),"SetCurrentConsoleFontEx",SetCurrentConsoleFontEx)){
            CONSOLE_FONT_INFOEX cfi;
            cfi.cbSize = sizeof(cfi);
            cfi.nFont = 0;
            cfi.dwFontSize = {10,10};
            cfi.FontFamily = FF_DONTCARE;
            cfi.FontWeight = FW_NORMAL;
            wcscpy(cfi.FaceName, L"Consolas");
            SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
    }
    //делает символы квадратными
}

void Console::print(Snake snake){
    CHAR_INFO ch[snake.sY * snake.sX];
    vector<Points> spr;
    int k = 0;
    for(int i = 0;i<snake.sY;++i){
        for(int j = 0;j<snake.sX;++j){
            ch[k] = snake.field[i][j];
            ++k;
        }
    }
    static COORD screenSize = {
        static_cast<SHORT>(snake.sX),
        static_cast<SHORT>(snake.sY)
    };
    static SMALL_RECT writeRegion = {
        0,
        0,
        static_cast<SHORT>(snake.sX - 1),
        static_cast<SHORT>(snake.sY - 1)
    };
    WriteConsoleOutput(hConsole,&ch[0],screenSize,{0,0},&writeRegion);
}
