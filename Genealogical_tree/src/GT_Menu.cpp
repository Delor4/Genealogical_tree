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


/** @brief Show menu.
  *
  *
  */
void GT_Menu::show()
{
    std::cout << "Menu:\n";
    for(auto &i: items){
        std::cout << i.label << '\n';
    }
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
