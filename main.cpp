#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <iostream>
#include "Console.h"
#include "Snake.h"
#include "Texture.h"
using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::string;

int main()
{
    Console console;
    console.consoleSize(Snake::sX,(Snake::sY));
    console.sqrSymbols();
    Snake snake;
    while(!snake.lose){
        console.print(snake);
        snake.getKey();
    }
    system("cls");
    system("color F0");
    printf("You lost!\nYour score is %d!", snake.length * 15);
    /*ifstream highscores("Highscores.txt");
    string line;
    while(getline(highscores,line)){
        string name;
    }*/
    return EXIT_SUCCESS;
}
