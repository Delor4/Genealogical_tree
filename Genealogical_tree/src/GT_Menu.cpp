#include "GT_Menu.h"

#include <iostream>
#include <Windows.h>

GT_Menu::GT_Menu()
{

}

GT_Menu::~GT_Menu()
{
    //dtor
}

void GT_Menu::show()
{
    //std::cout << "Menu:\n";
    bool first = true;
    for(auto &i: items){
        if(!first) std::cout << ", ";
        std::cout << i.label;
        first = false;
    }
    std::cout << "\n";
}

MENU_ITEMS GT_Menu::get_option()
{
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD events;
    INPUT_RECORD buffer;

    while(true){
        ReadConsoleInput(handle, &buffer, 1, &events);
        if(!buffer.Event.KeyEvent.bKeyDown){
            char c = buffer.Event.KeyEvent.uChar.AsciiChar;
            for(auto &i: items){
                for(auto k: i.short_keys){
                    if(k==c) return i.ID;
                }
            }
        }
    }
};

void GT_Menu::gotoxy(int x, int y) {
        COORD cur;
        cur.X = x;
        cur.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

}
void GT_Menu::cls(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ',
       dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
       dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}